// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Certificate.hpp"

namespace app
{
Certificate::Certificate(const QString &id, const QString &comment, const QDateTime &createdAt, const QString &link)
    : m_id{id}
    , m_comment{comment}
    , m_createdAt{createdAt}
    , m_link{link}
{
}


const QString &Certificate::id() const
{
    return m_id;
}


const QString &Certificate::comment() const
{
    return m_comment;
}


const QDateTime &Certificate::createdAt() const
{
    return m_createdAt;
}


const QString &Certificate::link() const
{
    return m_link;
}

}  // namespace app
