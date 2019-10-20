#pragma once

#include <QString>

namespace app
{
class Country
{
public:
    explicit Country(const QString &id,
                     const QString &title,
                     const QString &description,
                     const QString &code,
                     int serversCount);

    const QString &id() const;
    const QString &title() const;
    const QString &description() const;
    const QString &code() const;
    int serversCount() const;

private:
    QString m_id{};
    QString m_title{};
    QString m_description{};
    QString m_code{};
    int m_serversCount{};
};

}  // namespace app
