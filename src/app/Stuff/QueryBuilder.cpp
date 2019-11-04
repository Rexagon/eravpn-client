// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QueryBuilder.hpp"

#include <iostream>
#include <stack>

#include <QStringList>

namespace app::details::query
{
constexpr bool isPlain(DataType type)
{
    switch (type)
    {
        case DataType::Bool:
        case DataType::Number:
        case DataType::String:
            return true;

        default:
            return false;
    }
}


void appendNodeName(QString &query, const Node &node, std::vector<int> &arguments)
{
    // Special case for UnionVariant
    if (node.type == DataType::UnionVariant)
    {
        query += "... on " + node.name;
        return;
    }

    query += node.name;

    if (node.arguments.empty())
    {
        return;
    }

    query += "(";

    for (auto it = node.arguments.begin(); it != node.arguments.end();)
    {
        const auto &item = *it;

        query += item.name + ":";

        if (item.defaultValue.has_value())
        {
            query += *item.defaultValue;
        }
        else
        {
            arguments.emplace_back(query.size());
        }

        ++it;
        if (it != node.arguments.end())
        {
            query += ",";
        }
    }

    query += ")";
}

}  // namespace app::details::query

namespace app
{
using namespace details::query;

QueryBuilder::QueryBuilder(bool isMutation)
    : m_isMutation{isMutation}
{
}


Query QueryBuilder::build()
{
    assert(!m_nodes.empty());

    std::stack<std::pair<Node *, bool>> stack{};

    QString result{m_isMutation ? "mutation{" : "query{"};
    std::vector<int> resultArguments{};

    stack.emplace(&m_nodes.front(), false);
    while (!stack.empty())
    {
        auto &[node, visited] = stack.top();

        // Only objects can be visited
        if (visited)
        {
            result += "}";
            stack.pop();
            continue;
        }

        // At first add node name with arguments
        appendNodeName(result, *node, resultArguments);

        // Just pop node if it is plain
        if (isPlain(node->type))
        {
            result += " ";
            stack.pop();
            continue;
        }

        // Mark object as visited
        result += "{";
        visited = true;

        // Push all children
        for (auto it = node->children.rbegin(); it != node->children.rend(); ++it)
        {
            stack.emplace(*it, false);
        }
    }

    result += "}";

    return Query{result, resultArguments};
}


QueryBuilder QueryBuilder::createQuery()
{
    return QueryBuilder{false};
}


QueryBuilder QueryBuilder::createMutation()
{
    return QueryBuilder{true};
}


QueryBuilder &QueryBuilder::withArgument(const QString &name)
{
    assert(!m_nodeStack.empty() && m_nodeStack.back()->type != details::query::DataType::UnionVariant);

    m_nodeStack.back()->arguments.emplace_back(details::query::Argument{name, std::nullopt});

    return *this;
}


QueryBuilder &QueryBuilder::addObject(const QString &name)
{
    return addBlock(name, DataType::Object);
}


QueryBuilder &QueryBuilder::endObject()
{
    return endBlock(DataType::Object);
}


QueryBuilder &QueryBuilder::addArray(const QString &name)
{
    return addBlock(name, DataType::Array);
}


QueryBuilder &QueryBuilder::endArray()
{
    return endBlock(DataType::Array);
}


QueryBuilder &QueryBuilder::addUnion(const QString &name)
{
    return addBlock(name, DataType::Union);
}


QueryBuilder &QueryBuilder::endUnion()
{
    return endBlock(DataType::Union);
}


QueryBuilder &QueryBuilder::addUnionVariant(const QString &name)
{
    return addBlock(name, DataType::UnionVariant);
}


QueryBuilder &QueryBuilder::endUnionVariant()
{
    return endBlock(DataType::UnionVariant);
}


QueryBuilder &QueryBuilder::addBlock(const QString &name, details::query::DataType type)
{
    assert(canAdd(type));

    auto &node = m_nodes.emplace_back(name, type);

    if (!m_nodeStack.empty())
    {
        m_nodeStack.back()->children.emplace_back(&node);
    }
    m_nodeStack.emplace_back(&node);

    return *this;
}


QueryBuilder &QueryBuilder::endBlock(DataType type)
{
    assert(canEnd(type));

    while (m_nodeStack.back()->type != type)
    {
        m_nodeStack.pop_back();
    }

    assert(!m_nodeStack.empty());

    m_nodeStack.pop_back();

    return *this;
}


bool QueryBuilder::canAdd(DataType type) const
{
    return m_nodeStack.empty() || canAdd(type, m_nodeStack.back()->type);
}


bool QueryBuilder::canAdd(DataType child, DataType parent) const
{
    switch (parent)
    {
        case DataType::Union:
            // UnionVariant can only be added to Union
            return child == DataType::UnionVariant;

        case DataType::UnionVariant:
        case DataType::Object:
        case DataType::Array:
            return child != DataType::UnionVariant;

        default:
            return false;
    }
}


bool QueryBuilder::canEnd(DataType type) const
{
    switch (type)
    {
        case DataType::Union:
        case DataType::UnionVariant:
        case DataType::Object:
        case DataType::Array:
            if (m_nodeStack.empty())
            {
                return false;
            }

            for (auto it = m_nodeStack.rbegin(); it != m_nodeStack.rend(); ++it)
            {
                if ((*it)->type == type)
                {
                    return true;
                }
            }

            return false;

        default:
            return false;
    }
}

}  // namespace app
