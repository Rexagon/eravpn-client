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

public:
    struct Data
    {
        QString id;
        QString userName;
        QString email;
    };

    explicit Profile();

    void signIn();
    void signOut();

    bool authorized() const;

    void setData(const Data &data);

    QString id() const;
    QString userName() const;
    QString email() const;

signals:
    void signInErrorOccured();

    void signUpErrorOccured();
    void emailVerificationRequested();
    void authKeyCopyRequested(const QString &authKey);

    void authorizedChanged();
    void dataChanged();

private:
    bool m_authorized{};

    std::optional<Data> m_data{};
};

}  // namespace app
