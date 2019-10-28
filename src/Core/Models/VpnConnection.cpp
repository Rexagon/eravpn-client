// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "VpnConnection.hpp"

#include "../../Vpn/Client.hpp"

namespace app
{
VpnConnection::VpnConnection()
    : QObject{nullptr}
{
    m_statisticsTimer.setInterval(1000);
    m_statisticsTimer.setSingleShot(false);

    connect(&m_statisticsTimer, &QTimer::timeout, this, &VpnConnection::updateStatistics);
    connect(this, &VpnConnection::connectedChanged, this, &VpnConnection::updateStatisticsTimer);
}


VpnConnection::~VpnConnection()
{
    m_statisticsTimer.stop();
    reset();
}

void VpnConnection::start(const QString &config, const QString &password)
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
    ovpnConfig.privateKeyPassword = password.toStdString();

    openvpn::ClientAPI::EvalConfig eval = client->eval_config(ovpnConfig);

    if (eval.error)
    {
        std::cerr << "Eval error: " << eval.message << std::endl;
        emit connectionErrorOccurred();
        return;
    }

    m_isRunning = true;
    m_isConnected = false;

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
            emit runtimeErrorOccurred();
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
    emit busyChanged();
}


void VpnConnection::stop()
{
    if (m_client == nullptr)
    {
        return;
    }

    m_disconnectRequested = true;
    emit busyChanged();

    m_client->stop();
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


quint64 VpnConnection::bytesIn() const
{
    return m_statistics.bytesIn;
}


quint64 VpnConnection::bytesInDelta() const
{
    return m_deltaStatistics.bytesIn;
}


quint64 VpnConnection::bytesOut() const
{
    return m_statistics.bytesOut;
}


quint64 VpnConnection::bytesOutDelta() const
{
    return m_deltaStatistics.bytesOut;
}


void VpnConnection::updateStatisticsTimer()
{
    if (connected())
    {
        m_statisticsTimer.start();
    }
    else
    {
        m_statisticsTimer.stop();
    }
}


void VpnConnection::handleEvent(const vpn::Event &event)
{
    std::unique_lock<std::mutex> lock{m_connectionMutex};

    if (event.fatal)
    {
        emit runtimeErrorOccurred();
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
            m_statistics = Statistics{};
            m_deltaStatistics = Statistics{};

            m_isConnected = false;
            emit connectedChanged();
            emit statisticsChanged();
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


void VpnConnection::updateStatistics()
{
    if (!connected() || m_client == nullptr)
    {
        return;
    }

    const auto info = m_client->transport_stats();
    const auto &in = static_cast<quint64>(info.bytesIn);
    const auto &out = static_cast<quint64>(info.bytesOut);

    m_deltaStatistics = Statistics{in - m_statistics.bytesIn, out - m_statistics.bytesOut};
    m_statistics = Statistics{in, out};

    emit statisticsChanged();
}

}  // namespace app
