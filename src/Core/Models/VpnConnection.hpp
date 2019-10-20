#pragma once

#include <memory>
#include <thread>

#include <QObject>

namespace app
{
namespace vpn
{
class Client;
}

class VpnConnection : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)

public:
    explicit VpnConnection();

    Q_INVOKABLE void connectUsingConfig(const QString &config);
    Q_INVOKABLE void disconnect();

    bool connected() const;

signals:
    void connectedChanged(bool);
    void connectionError();

private:
    std::shared_ptr<vpn::Client> m_client{};
    std::unique_ptr<std::thread> m_vpnThread{};
};

}  // namespace app
