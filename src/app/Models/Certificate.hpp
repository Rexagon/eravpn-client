#pragma once

#include <QDateTime>
#include <QString>

namespace app
{
class Certificate
{
public:
    explicit Certificate(const QString &id, const QString &comment, const QDateTime &createdAt, const QString &link);

    const QString &id() const;
    const QString &comment() const;
    const QDateTime &createdAt() const;

    const QString &link() const;

private:
    QString m_id;
    QString m_link;
    QString m_comment;
    QDateTime m_createdAt;
};
}  // namespace app
