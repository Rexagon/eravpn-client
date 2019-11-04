// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "StringHelpers.hpp"

#include <unordered_map>

namespace app
{
QString escaped(const QString &string)
{
    static std::unordered_map<char, QString> const escapes = {
        {'\a', "\\a"},  //  7, ^G, alert (bell)
        {'\b', "\\b"},  //  8, ^H, backspace
        {'\t', "\\t"},  //  9, ^I, tab
        {'\n', "\\n"},  // 10, ^J, newline / linefeed
        {'\v', "\\v"},  // 11, ^K, vertical tab
        {'\f', "\\f"},  // 12, ^L, formfeed
        {'\r', "\\r"},  // 13, ^M, carriage return
        {'"', "\\\""},  // double quotes
        {'\\', "\\\\"}  // backslash
    };

    QString result;
    result.reserve(string.size() * 2);

    for (const auto &symbol : string)
    {
        auto const it = escapes.find(symbol.toLatin1());
        if (it == escapes.end())
        {
            result += symbol;
        }
        else
        {
            result += it->second;
        }
    }

    return result;
}

}  // namespace app
