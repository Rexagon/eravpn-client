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

    Q_INVOKABLE void refreshProfile();

    Q_INVOKABLE void changeEmail(const QString &newEmail);

    Q_INVOKABLE void changePassword(const QString &oldPassword, const QString &newPassword);

signals:
    void profileUpdateError();
    void passwordChangeError();
    void emailChangeError();

    void passwordChanged();
    void emailChanged();

private:
    void setAuthData(const QString &accessToken, const QString &refreshToken);
    void setProfileData(const QJsonObject &profileData);

    Connection &m_connection;
    Profile &m_profile;
};

}  // namespace app
