// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Country.hpp"

namespace app
{
Country::Country(const QString &id,
                 const QString &title,
                 const QString &description,
                 const QString &code,
                 int serversCount)
    : m_id{id}
    , m_title{title}
    , m_description{description}
    , m_code{code}
    , m_serversCount{serversCount}
{
}


const QString &Country::id() const
{
    return m_id;
}


const QString &Country::title() const
{
    return m_title;
}


const QString &Country::description() const
{
    return m_description;
}


const QString &Country::code() const
{
    return m_code;
}


int Country::serversCount() const
{
    return m_serversCount;
}

}  // namespace app
