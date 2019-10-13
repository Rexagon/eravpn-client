#pragma once

#include <QtQml/qqmlengine.h>
#include <QObject>

#include "Connection.hpp"

namespace app
{
Q_NAMESPACE

class BackEnd : public QObject
{
    Q_OBJECT

public:
    static QObject *singletonProvider(QQmlEngine *qmlEngine, QJSEngine *scriptEngine);

    explicit BackEnd(QObject *parent = nullptr);

    Q_INVOKABLE void sendQuery();

signals:
    void serverListReceived(const QString &data);

private:
    Connection m_connection;
};

}  // namespace app
