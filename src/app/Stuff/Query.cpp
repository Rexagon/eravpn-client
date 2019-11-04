// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Query.hpp"

namespace app
{
Query::Query(const QString &string, const std::vector<int> &arguments)
    : m_string{string}
    , m_arguments{arguments}
{
}

}  // namespace app
