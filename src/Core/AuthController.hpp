#pragma once

#include "Connection.hpp"

namespace app
{
class AuthController : public QObject
{
    Q_OBJECT

public:
    explicit AuthController(Connection &connection);

    Q_INVOKABLE void auth(const QString &login, const QString &password);

signals:
    void authorized(const QString &accessToken, const QString &refreshToken);

private:
    Connection &m_connection;
};

}  // namespace app
