// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Tariff.hpp"

namespace app
{
Tariff::Tariff(const QString &id, const QString &title, double price, double profitInPercent, int monthCount)
    : m_id{id}
    , m_title{title}
    , m_price{price}
    , m_profitInPercent{profitInPercent}
    , m_monthCount{monthCount}
{
}


const QString &Tariff::id() const
{
    return m_id;
}


const QString &Tariff::title() const
{
    return m_title;
}


double Tariff::price() const
{
    return m_price;
}


double Tariff::profitInPercent() const
{
    return m_profitInPercent;
}


int Tariff::monthCount() const
{
    return m_monthCount;
}

}  // namespace app
