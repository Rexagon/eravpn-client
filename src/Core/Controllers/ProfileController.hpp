#pragma once

#include "../Connection.hpp"
#include "../Models/Profile.hpp"

namespace app
{
class ProfileController : public QObject
{
    Q_OBJECT

public:
    explicit ProfileController(Connection &connection, Profile &profile);

    Q_INVOKABLE void signInRemembered();

    Q_INVOKABLE void signIn(const QString &login, const QString &password);

    Q_INVOKABLE void signUp(bool isAnonymous,
                            const QString &identifier,
                            const QString &password,
                            const QString &referrerKey);

    Q_INVOKABLE void signOut();

private:
    void fillProfile(const QJsonObject &clientData, const QString &accessToken, const QString &refreshToken);

    Connection &m_connection;
    Profile &m_profile;
};

}  // namespace app
