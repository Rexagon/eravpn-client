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
    disconnect();
}

void VpnConnection::connectUsingConfig(const QString &config)
{
    if (connected())
    {
        return;
    }

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

    m_client = std::move(client);
    m_vpnThread = std::make_unique<std::thread>([this]() {
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

        std::cout << "Thread finished" << std::endl;
    });

    emit connectedChanged();
}


void VpnConnection::disconnect()
{
    if (!connected())
    {
        return;
    }

    m_client->stop();

    if (m_vpnThread->joinable())
    {
        m_vpnThread->join();
    }

    m_client.reset();
    m_vpnThread.reset();

    emit connectedChanged();
}


bool VpnConnection::connected() const
{
    return m_client != nullptr && m_vpnThread != nullptr;
}

}  // namespace app
