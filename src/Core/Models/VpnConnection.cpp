// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "VpnConnection.hpp"

#include "../../Vpn/Client.hpp"

namespace app
{
VpnConnection::VpnConnection()
    : QObject{nullptr}
{
}


VpnConnection::~VpnConnection()
{
    reset();
}

void VpnConnection::start(const QString &config)
{
    std::unique_lock<std::mutex> lock{m_connectionMutex};
    if (m_isRunning)
    {
        return;
    }

    reset();

    auto client = std::make_unique<vpn::Client>([this](const vpn::Event &event) { handleEvent(event); });

    openvpn::ClientAPI::Config ovpnConfig;
    ovpnConfig.content = config.toUtf8().data();

    openvpn::ClientAPI::EvalConfig eval = client->eval_config(ovpnConfig);

    if (eval.error)
    {
        std::cerr << "Eval error: " << eval.message << std::endl;
        emit connectionError();
        return;
    }

    m_isRunning = true;

    m_client = std::move(client);
    m_connectionThread = std::make_unique<std::thread>([this] {
        try
        {
            std::cout << "Thread starting..." << std::endl;
            auto connect_status = m_client->connect();

            if (connect_status.error)
            {
                std::cout << "connect error: ";

                if (!connect_status.status.empty())
                    std::cout << connect_status.status << ": ";

                std::cout << connect_status.message << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "Connect thread exception: " << e.what() << std::endl;
            emit runtimeError();
        }

        std::unique_lock<std::mutex> lock{m_connectionMutex};
        m_isRunning = false;
        m_disconnectRequested = false;
        m_client.reset();

        std::cout << "Thread finished" << std::endl;
        emit busyChanged();
        emit runningChanged();
    });

    emit runningChanged();
}


void VpnConnection::stop()
{
    if (m_client != nullptr)
    {
        m_disconnectRequested = true;
        emit busyChanged();

        m_client->stop();
    }
}


bool VpnConnection::running() const
{
    return m_isRunning;
}


bool VpnConnection::connected() const
{
    return m_isConnected;
}


bool VpnConnection::busy() const
{
    return m_isRunning != m_isConnected || m_disconnectRequested;
}


void VpnConnection::handleEvent(const vpn::Event &event)
{
    std::unique_lock<std::mutex> lock{m_connectionMutex};

    if (event.fatal)
    {
        emit runtimeError();
        stop();
        return;
    }

    const auto type = vpn::parse(event.name);
    switch (type)
    {
        case vpn::Event::Type::Connected:
            m_isConnected = true;
            emit connectedChanged();
            emit busyChanged();
            return;

        case vpn::Event::Type::Disconnected:
            m_isConnected = false;
            emit connectedChanged();
            return;

        default:
            return;
    }
}


void VpnConnection::reset()
{
    stop();

    if (m_connectionThread != nullptr && m_connectionThread->joinable())
    {
        m_connectionThread->join();
    }
}

}  // namespace app
