#pragma once

#include <QString>

namespace app
{
class Tariff
{
public:
    explicit Tariff(const QString &id, const QString &title, double price, double profitInPercent, int monthCount);

    const QString &id() const;
    const QString &title() const;
    double price() const;
    double profitInPercent() const;
    int monthCount() const;

private:
    QString m_id;
    QString m_title;
    double m_price;
    double m_profitInPercent;
    int m_monthCount;
};

}  // namespace app
