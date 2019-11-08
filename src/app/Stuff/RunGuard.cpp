// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "RunGuard.hpp"

#include <optional>

#include <QCryptographicHash>
#include <QEventLoop>
#include <QLocalSocket>

namespace
{
QString generateKeyHash(const QString &key, const QString &salt)
{
    QByteArray data;

    data.append(key.toUtf8());
    data.append(salt.toUtf8());
    data = QCryptographicHash::hash(data, QCryptographicHash::Sha1).toHex();

    return data;
}

}  // namespace

namespace app
{
RunGuard::RunGuard(const QString &key)
    : QObject{nullptr}
    , m_key{key}
    , m_memLockKey{generateKeyHash(key, "_memLockKey")}
    , m_sharedMemoryKey{generateKeyHash(key, "_sharedMemoryKey")}
    , m_localServerKey{generateKeyHash(key, "_localServer")}
    , m_sharedMemory{m_sharedMemoryKey}
    , m_systemSemaphore{m_memLockKey, 1}
{
    m_systemSemaphore.acquire();
    {
        QSharedMemory fix{m_sharedMemoryKey};
        fix.attach();
    }
    m_systemSemaphore.release();
}


RunGuard::~RunGuard()
{
    release();
}


bool RunGuard::tryToRun()
{
    if (m_localServer != nullptr || isAnotherRunning())
    {
        return false;
    }

    m_systemSemaphore.acquire();
    const bool result = m_sharedMemory.create(sizeof(quint64));
    m_systemSemaphore.release();

    if (!result)
    {
        release();
        return false;
    }

    m_localServer = std::make_unique<QLocalServer>();
    connect(m_localServer.get(), &QLocalServer::newConnection, this, &RunGuard::showRequested);
    m_localServer->listen(m_localServerKey);

    return true;
}


void RunGuard::notifyAnother()
{
    QLocalSocket socket{};
    socket.connectToServer(m_localServerKey);

    if (socket.isOpen())
    {
        socket.close();
    }

    socket.deleteLater();
}


bool RunGuard::isAnotherRunning()
{
    if (m_sharedMemory.isAttached())
    {
        return false;
    }

    m_systemSemaphore.acquire();
    const bool isRunning = m_sharedMemory.attach();

    if (isRunning)
    {
        m_sharedMemory.detach();
    }

    m_systemSemaphore.release();
    return isRunning;
}


void RunGuard::release()
{
    m_systemSemaphore.acquire();

    if (m_sharedMemory.isAttached())
    {
        m_sharedMemory.detach();
    }

    m_systemSemaphore.release();
}

}  // namespace app
