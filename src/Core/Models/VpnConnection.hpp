#pragma once

#include <memory>
#include <mutex>
#include <thread>

#include <QObject>

#include "../../Vpn/Event.hpp"

namespace app
{
namespace vpn
{
class Client;
}

class VpnConnection final : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool running READ running NOTIFY runningChanged)
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)

public:
    explicit VpnConnection();
    ~VpnConnection() final;

    Q_INVOKABLE void start(const QString &config);
    Q_INVOKABLE void stop();

    bool running() const;
    bool connected() const;
    bool busy() const;

signals:
    void runningChanged();
    void connectedChanged();
    void busyChanged();

    void connectionError();
    void runtimeError();

private:
    void handleEvent(const vpn::Event &event);
    void reset();

    std::unique_ptr<vpn::Client> m_client{};
    std::unique_ptr<std::thread> m_connectionThread{};

    std::mutex m_connectionMutex{};
    bool m_isRunning{};
    bool m_isConnected{};

    bool m_disconnectRequested{};
};

}  // namespace app
