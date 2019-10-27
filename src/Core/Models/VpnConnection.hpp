#pragma once

#include <memory>
#include <mutex>
#include <thread>

#include <QObject>
#include <QTimer>

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

    Q_PROPERTY(quint64 bytesIn READ bytesIn NOTIFY statisticsChanged)
    Q_PROPERTY(quint64 bytesInDelta READ bytesInDelta NOTIFY statisticsChanged)
    Q_PROPERTY(quint64 bytesOut READ bytesOut NOTIFY statisticsChanged)
    Q_PROPERTY(quint64 bytesOutDelta READ bytesOutDelta NOTIFY statisticsChanged)

public:
    struct Statistics
    {
        quint64 bytesIn{};
        quint64 bytesOut{};
    };

    explicit VpnConnection();
    ~VpnConnection() final;

    void start(const QString &config);
    void stop();

    bool running() const;
    bool connected() const;
    bool busy() const;

    quint64 bytesIn() const;
    quint64 bytesInDelta() const;
    quint64 bytesOut() const;
    quint64 bytesOutDelta() const;

signals:
    void runningChanged();
    void connectedChanged();
    void busyChanged();

    void statisticsChanged();

    void connectionErrorOccurred();
    void runtimeErrorOccurred();

private slots:
    void updateStatisticsTimer();

private:
    void handleEvent(const vpn::Event &event);
    void reset();

    void updateStatistics();

    std::unique_ptr<vpn::Client> m_client{};
    std::unique_ptr<std::thread> m_connectionThread{};

    std::mutex m_connectionMutex{};
    bool m_isRunning{};
    bool m_isConnected{};

    bool m_disconnectRequested{};

    Statistics m_statistics{};
    Statistics m_deltaStatistics{};
    QTimer m_statisticsTimer{};
};

}  // namespace app
