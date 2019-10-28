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
    Q_PROPERTY(Status status READ status NOTIFY dataChanged)

public:
    enum class Status
    {
        Unknown,
        New,
        Active
    };
    Q_ENUM(Status)

    struct Data
    {
        QString id;
        QString userName;
        QString email;
        QString ovpnConfigPassword;
        Status status;
    };

    explicit Profile();

    void signIn();
    void signOut();

    bool authorized() const;

    void setData(const Data &data);

    QString id() const;
    QString userName() const;
    QString email() const;
    QString ovpnConfigPassword() const;
    Status status() const;

signals:
    void signInErrorOccurred();

    void signUpErrorOccurred();
    void authKeyCopyRequested(const QString &authKey);

    void authorizedChanged();
    void dataChanged();

private:
    bool m_authorized{};

    std::optional<Data> m_data{};
};

}  // namespace app
