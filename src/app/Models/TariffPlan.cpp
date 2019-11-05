// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "TariffPlan.hpp"

namespace app
{
TariffPlan::TariffPlan(const QString &id, const QString &title, int price, int monthCount)
    : m_id{id}
    , m_title{title}
    , m_price{price}
    , m_monthCount{monthCount}
{
}


const QString &TariffPlan::id() const
{
    return m_id;
}


const QString &TariffPlan::title() const
{
    return m_title;
}


int TariffPlan::price() const
{
    return m_price;
}


int TariffPlan::monthCount() const
{
    return m_monthCount;
}

}  // namespace app
