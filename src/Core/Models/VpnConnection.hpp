#pragma once

#include <memory>
#include <mutex>
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

    Q_INVOKABLE void start(const QString &config);
    Q_INVOKABLE void stop();

    bool connected() const;

signals:
    void connectedChanged();
    void connectionError();

private:
    void reset();

    std::unique_ptr<vpn::Client> m_client{};
    std::unique_ptr<std::thread> m_connectionThread{};

    std::mutex m_connectionMutex{};
    bool m_isConnected{};
};

}  // namespace app
