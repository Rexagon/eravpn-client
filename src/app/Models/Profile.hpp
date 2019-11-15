#pragma once

#include <optional>

#include <QDateTime>
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

    Q_PROPERTY(bool isTariffPurchased READ isTariffPurchased NOTIFY dataChanged)
    Q_PROPERTY(QString tariffId READ tariffId NOTIFY dataChanged)
    Q_PROPERTY(QDateTime tariffExpiredAt READ tariffExpiredAt NOTIFY dataChanged)

public:
    enum class Status
    {
        Unknown,
        New,
        Active
    };
    Q_ENUM(Status)

    struct TariffData
    {
        QString id;
        QDateTime expiredAt;
    };

    struct Data
    {
        QString id;
        QString userName;
        QString email;
        QString ovpnConfigPassword;
        Status status;
        std::optional<TariffData> tariffData;
    };

    explicit Profile();

    void signIn();
    void signOut();

    bool authorized() const;

    void setData(const Data &data);
    void setEmail(const QString &email);

    QString id() const;
    QString userName() const;
    QString email() const;
    QString ovpnConfigPassword() const;
    Status status() const;

    bool isTariffPurchased() const;
    QString tariffId() const;
    QDateTime tariffExpiredAt() const;

signals:
    void authorizedChanged();
    void dataChanged();

private:
    bool m_authorized{};

    std::optional<Data> m_data{};
};

}  // namespace app
