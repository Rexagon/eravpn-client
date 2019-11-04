#pragma once

#include <list>
#include <optional>
#include <vector>

#include <QString>

#include "Helpers.hpp"

namespace app
{
namespace details::query
{
enum class DataType
{
    Bool,
    Number,
    String,
    Union,
    UnionVariant,
    Object,
    Array
};

struct Argument
{
    QString name;
    std::optional<QString> defaultValue;
};

struct Node
{
    explicit Node(const QString &name, DataType type)
        : name(name)
        , type(type)
    {
    }

    QString name;
    DataType type;
    std::list<Argument> arguments{};

    std::vector<Node *> children{};
};


template <typename T>
QString stringifyArgument(const T &value)
{
    static_assert(is_any_of_v<T, bool, int, double, const char *, std::string, QString>,
                  "Argument constant type is invalid");

    if constexpr (std::is_same_v<T, bool>)
    {
        return value ? "true" : "false";
    }
    if constexpr (is_any_of_v<T, int, double>)
    {
        return QString::number(value);
    }
    if constexpr (is_any_of_v<T, const char *, std::string, QString>)
    {
        return "\"" + escaped(value) + "\"";
    }

    return QString{};
}


constexpr bool isPlain(DataType type);

}  // namespace details::query

class Query
{
public:
    explicit Query(const QString &string, const std::vector<int> &arguments);

    template <typename... Args>
    QString prepare(const Args &... args) const;

private:
    template <typename T>
    void appendParameter(QString &result, const T &value, size_t &index) const;

    QString m_string;
    std::vector<int> m_arguments;
};


template <typename... Args>
QString Query::prepare(const Args &... args) const
{
    assert(sizeof...(args) == m_arguments.size());

    if (m_arguments.empty())
    {
        return m_string;
    }

    QString result{};

    size_t index = 0;
    result += m_string.left(m_arguments[index]);

    using dummy = int[];
    static_cast<void>(dummy{(appendParameter(result, args, index), 0)..., 0});

    return result;
}


template <typename T>
void Query::appendParameter(QString &result, const T &value, size_t &index) const
{
    const auto argumentPosition = m_arguments[index++];

    result += details::query::stringifyArgument(value);

    if (index == m_arguments.size())
    {
        result += m_string.mid(argumentPosition);
    }
    else
    {
        result += m_string.mid(argumentPosition, m_arguments[index] - argumentPosition);
    }
}

}  // namespace app
