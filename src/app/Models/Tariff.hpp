#pragma once

#include <QObject>
#include <QString>

namespace app
{
class Tariff : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(double price READ price CONSTANT)
    Q_PROPERTY(double profitInPercent READ profitInPercent CONSTANT)
    Q_PROPERTY(int monthCount READ monthCount CONSTANT)

public:
    explicit Tariff();
    explicit Tariff(const QString &id, const QString &title, double price, double profitInPercent, int monthCount);

    const QString &id() const;
    const QString &title() const;
    double price() const;
    double profitInPercent() const;
    int monthCount() const;

private:
    QString m_id{};
    QString m_title{};
    double m_price{};
    double m_profitInPercent{};
    int m_monthCount{};
};

}  // namespace app
