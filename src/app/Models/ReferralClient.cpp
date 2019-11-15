// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ReferralClient.hpp"

namespace app
{
ReferralClient::ReferralClient(const QString &id,
                               const QString &email,
                               const QString &userName,
                               int level,
                               double profit,
                               const QDateTime &createdAt)
    : m_id{id}
    , m_email{email}
    , m_userName{userName}
    , m_level{level}
    , m_profit{profit}
    , m_createdAt{createdAt}
{
}


const QString &ReferralClient::id() const
{
    return m_id;
}


const QString &ReferralClient::email() const
{
    return m_email;
}


const QString &ReferralClient::userName() const
{
    return m_userName;
}


int ReferralClient::level() const
{
    return m_level;
}


double ReferralClient::profit() const
{
    return m_profit;
}


const QDateTime &ReferralClient::createdAt() const
{
    return m_createdAt;
}

}  // namespace app
