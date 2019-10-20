// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "VpnConnection.hpp"

#include <QFile>

#include "../../Vpn/Vpn.hpp"

namespace
{
QString readConfig(const QString &path)
{
    QFile file{path};

    file.open(QIODevice::ReadOnly | QIODevice::ExistingOnly);

    const auto result = file.readAll();

    std::cout << result.toStdString() << std::endl;

    return result;
}

}  // namespace

namespace app
{
VpnConnection::VpnConnection()
    : QObject{nullptr}
{
}


void VpnConnection::connectUsingConfig(const QString &config)
{
    if (connected())
    {
        return;
    }

    // TEMP


    ClientAPI::Config ovpnConfig;
    ovpnConfig.content = readConfig(config).toUtf8().data();

    m_client = std::make_shared<vpn::Client>();
    std::cout << "ASD" << std::endl;

    openvpn::ClientAPI::EvalConfig eval = m_client->eval_config(ovpnConfig);

    if (eval.error)
    {
        std::cerr << "Eval error: " << eval.message << std::endl;
        emit connectionError();
        return;
    }

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

    emit connectedChanged(true);
}


void VpnConnection::disconnect()
{
    if (!connected())
    {
        return;
    }

    m_client->stop();
    m_vpnThread->join();

    m_client.reset();
    m_vpnThread.reset();
}


bool VpnConnection::connected() const
{
    return m_vpnThread != nullptr && m_client != nullptr;
}

}  // namespace app
