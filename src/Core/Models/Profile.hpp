#pragma once

#include <optional>

#include <QObject>
#include <QString>

namespace app
{
class Profile : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool authorized READ authorized NOTIFY authorizedChanged)

    Q_PROPERTY(QString id READ id NOTIFY dataChanged)
    Q_PROPERTY(QString userName READ userName NOTIFY dataChanged)
    Q_PROPERTY(QString email READ email NOTIFY dataChanged)

    Q_PROPERTY(QString currentIp READ currentIp NOTIFY currentIpChanged)

public:
    struct ClientData
    {
        QString id;
        QString userName;
        QString email;
    };

    explicit Profile();

    void signIn();
    void signOut();

    bool authorized() const;

    void setData(const ClientData &clientData);

    QString id() const;
    QString userName() const;
    QString email() const;

    void setCurrentIp(const QString &ip);
    QString currentIp() const;

signals:
    void signInErrorOccured();

    void signUpErrorOccured();
    void emailVerificationRequested();
    void authKeyCopyRequested(const QString &authKey);

    void authorizedChanged();
    void dataChanged();
    void currentIpChanged();

private:
    bool m_authorized{};

    std::optional<ClientData> m_clientData{};

    QString m_currentIp{};
};

}  // namespace app
