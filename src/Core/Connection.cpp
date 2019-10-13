// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Connection.hpp"

#include <iostream>

namespace
{
constexpr auto QUERY_CONTAINER = R"({"query":"%1","variables":{},"operationName":null})";

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
}  // namespace


namespace app
{
Connection::Connection(const QString &url, QObject *parent)
    : QObject{parent}
    , m_baseRequest{url}
{
    m_baseRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=UTF-8");
    m_baseRequest.setHeader(QNetworkRequest::UserAgentHeader, "EraVPN Client");
}


void Connection::sendQuery(const QString &query, const Callback &callback)
{
    const auto escapedQuery = QString{QUERY_CONTAINER}.arg(escaped(query));
    const auto bytes = escapedQuery.toUtf8();

    auto *reply = m_networkManager.post(m_baseRequest, bytes);

    connect(reply, &QNetworkReply::finished, [reply, callback]() {
        std::cout << "Request finished" << std::endl;
        callback(*reply);
    });

    connect(reply, &QNetworkReply::sslErrors, [](const QList<QSslError> &errors) {
        for (const auto &error : errors)
        {
            std::cout << "Ssl error: " << error.errorString().toStdString() << std::endl;
        }
    });
}

}  // namespace app
