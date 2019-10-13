#pragma once

#include <QtQml/qqmlengine.h>
#include <QObject>

#include "AuthController.hpp"
#include "Connection.hpp"

namespace app
{
Q_NAMESPACE

class BackEnd : public QObject
{
    Q_OBJECT

    Q_PROPERTY(AuthController *authController READ authController)

public:
    static QObject *singletonProvider(QQmlEngine *qmlEngine, QJSEngine *scriptEngine);

    explicit BackEnd(QObject *parent = nullptr);

    AuthController *authController();

private:
    Connection m_connection;
    AuthController m_authController;
};

}  // namespace app
