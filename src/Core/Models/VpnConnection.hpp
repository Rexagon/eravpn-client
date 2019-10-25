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

class VpnConnection final : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)

public:
    explicit VpnConnection();
    ~VpnConnection() final;

    Q_INVOKABLE void connectUsingConfig(const QString &config);
    Q_INVOKABLE void disconnect();

    bool connected() const;

signals:
    void connectedChanged();
    void connectionError();

private:
    std::unique_ptr<vpn::Client> m_client{};
    std::unique_ptr<std::thread> m_vpnThread{};
    bool m_isRunning;
};

}  // namespace app
