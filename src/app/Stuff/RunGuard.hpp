#pragma once

#include <memory>

#include <QLocalServer>
#include <QObject>
#include <QSharedMemory>
#include <QSystemSemaphore>

namespace app
{
class RunGuard final : public QObject
{
    Q_OBJECT

public:
    explicit RunGuard(const QString &key);
    ~RunGuard() final;

    bool tryToRun();
    void notifyAnother();

signals:
    void showRequested();

private:
    bool isAnotherRunning();
    void release();

    const QString m_key;
    const QString m_memLockKey;
    const QString m_sharedMemoryKey;
    const QString m_localServerKey;

    QSharedMemory m_sharedMemory;
    QSystemSemaphore m_systemSemaphore;
    std::unique_ptr<QLocalServer> m_localServer{};
};

}  // namespace app
