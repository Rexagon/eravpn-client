#pragma once

#include "../Connection.hpp"

namespace app
{
class AuthController : public QObject
{
    Q_OBJECT

public:
    explicit AuthController(Connection &connection);

    Q_INVOKABLE void authorize(const QString &login, const QString &password);

    Q_INVOKABLE void createUser(bool isAnonymous,
                                const QString &identifier,
                                const QString &password,
                                const QString &referrerKey);

    Q_INVOKABLE void logout();

signals:
    void authorized();
    void authorizationError();

    void registeredWithEmail();
    void registeredWithLogin(const QString &authKey);
    void registrationError();

    void loggedOut();

private:
    Connection &m_connection;
};

}  // namespace app
