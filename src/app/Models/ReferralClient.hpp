#pragma once

#include <QDateTime>
#include <QString>

namespace app
{
class ReferralClient
{
public:
    explicit ReferralClient(const QString &id,
                            const QString &email,
                            const QString &userName,
                            int level,
                            double profit,
                            const QDateTime &createdAt);

    const QString &id() const;
    const QString &email() const;
    const QString &userName() const;
    int level() const;
    double profit() const;
    const QDateTime &createdAt() const;

private:
    QString m_id;
    QString m_email;
    QString m_userName;
    int m_level;
    double m_profit;
    QDateTime m_createdAt;
};

}  // namespace app
