#pragma once

#include <QString>

#include "Query.hpp"
#include "StringHelpers.hpp"

namespace app
{
class QueryBuilder
{
    explicit QueryBuilder(bool isMutation);

public:
    static QueryBuilder createQuery();
    static QueryBuilder createMutation();

    Query build();

    QueryBuilder &withArgument(const QString &name);

    template <typename T>
    QueryBuilder &withArgument(const QString &name, const T &value);

    template <typename T>
    QueryBuilder &addItem(const QString &name);

    QueryBuilder &addObject(const QString &name);
    QueryBuilder &endObject();

    QueryBuilder &addArray(const QString &name);
    QueryBuilder &endArray();

    QueryBuilder &addUnion(const QString &name);
    QueryBuilder &endUnion();

    QueryBuilder &addUnionVariant(const QString &name);
    QueryBuilder &endUnionVariant();

private:
    QueryBuilder &addBlock(const QString &name, details::query::DataType type);
    QueryBuilder &endBlock(details::query::DataType type);

    bool canAdd(details::query::DataType type) const;
    bool canAdd(details::query::DataType child, details::query::DataType parent) const;
    bool canEnd(details::query::DataType type) const;

    bool m_isMutation;

    std::list<details::query::Node> m_nodes{};
    std::vector<details::query::Node *> m_nodeStack{};
};


template <typename T>
QueryBuilder &QueryBuilder::withArgument(const QString &name, const T &value)
{
    static_assert(is_any_of_v<T, bool, int, double, QString>, "Argument type is invalid");
    assert(!m_nodeStack.empty() && m_nodeStack.back()->type != details::query::DataType::UnionVariant);

    m_nodeStack.back()->arguments.emplace_back(
        details::query::Argument{name, details::query::stringifyArgument<T>(value)});

    return *this;
}


template <typename T>
QueryBuilder &QueryBuilder::addItem(const QString &name)
{
    static_assert(is_any_of_v<T, bool, int, double, QString>, "Item type is invalid");

    details::query::DataType type;
    if constexpr (std::is_same_v<T, bool>)
    {
        type = details::query::DataType::Bool;
    }
    else if constexpr (is_any_of_v<T, int, double>)
    {
        type = details::query::DataType::Number;
    }
    else
    {
        type = details::query::DataType::String;
    }

    auto &node = m_nodes.emplace_back(name, type);

    if (!m_nodeStack.empty() && details::query::isPlain(m_nodeStack.back()->type))
    {
        m_nodeStack.pop_back();
    }

	assert(canAdd(type));

    if (!m_nodeStack.empty())
    {
        m_nodeStack.back()->children.emplace_back(&node);
    }

    m_nodeStack.emplace_back(&node);

    return *this;
}

}  // namespace app
