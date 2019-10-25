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
    if (m_isConnected)
    {
        return;
    }

    reset();

    auto client = std::make_unique<vpn::Client>();

    openvpn::ClientAPI::Config ovpnConfig;
    ovpnConfig.content = config.toUtf8().data();

    openvpn::ClientAPI::EvalConfig eval = client->eval_config(ovpnConfig);

    if (eval.error)
    {
        std::cerr << "Eval error: " << eval.message << std::endl;
        emit connectionError();
        return;
    }

    m_isConnected = true;

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
        }

        std::unique_lock<std::mutex> lock{m_connectionMutex};
        m_isConnected = false;
        m_client.reset();

        std::cout << "Thread finished" << std::endl;
        emit connectedChanged();
    });

    emit connectedChanged();
}


void VpnConnection::stop()
{
    if (m_client != nullptr)
    {
        m_client->stop();
    }
}


bool VpnConnection::connected() const
{
    return m_isConnected;
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
