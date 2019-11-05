#pragma once

#include <QString>

namespace app
{
class TariffPlan
{
public:
    explicit TariffPlan(const QString &id, const QString &title, int price, int monthCount);

    const QString &id() const;
    const QString &title() const;
    int price() const;
    int monthCount() const;

private:
    QString m_id;
    QString m_title;
    int m_price;
    int m_monthCount;
};

}  // namespace app
