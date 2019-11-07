#pragma once

#include <QObject>
#include <QSharedMemory>
#include <QSystemSemaphore>

namespace app
{
class RunGuard
{
    Q_DISABLE_COPY(RunGuard)

public:
    explicit RunGuard(const QString &key);
    ~RunGuard();

    bool isAnotherRunning();
    bool tryToRun();
    void release();

private:
    const QString m_key;
    const QString m_memLockKey;
    const QString m_sharedMemoryKey;

    QSharedMemory m_sharedMemory;
    QSystemSemaphore m_systemSemaphore;
};

}  // namespace app
