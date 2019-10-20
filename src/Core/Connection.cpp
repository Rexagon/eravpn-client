// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Connection.hpp"

#include <iostream>

namespace
{
constexpr auto QUERY_CONTAINER = R"({"query":"%1","variables":{},"operationName":null})";
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


void Connection::sendQuery(const QString &query,
                           const SuccessCallback &successCallback,
                           const std::optional<ErrorCallback> &errorCallback)
{
    const auto escapedQuery = QString{QUERY_CONTAINER}.arg(escaped(query));
    const auto bytes = escapedQuery.toUtf8();

    auto *reply = m_networkManager.post(m_baseRequest, bytes);
    std::cout << "POST request sent" << std::endl;
    std::cout << query.toStdString() << std::endl;

    connect(reply, &QNetworkReply::finished, [reply, successCallback, errorCallback]() {
        std::cout << "POST response received" << std::endl;

        if (reply->error() == QNetworkReply::NoError)
        {
            const auto data = QJsonDocument::fromJson(reply->readAll());
            std::cout << data.toJson().toStdString() << std::endl;

            successCallback(data);
        }
        else
        {
            std::cout << "Error(" << reply->error() << "): " << reply->errorString().toStdString() << std::endl;

            if (errorCallback)
            {
                (*errorCallback)(*reply);
            }
        }
    });

    connect(reply, &QNetworkReply::sslErrors, [](const QList<QSslError> &errors) {
        for (const auto &error : errors)
        {
            std::cout << "Ssl error: " << error.errorString().toStdString() << std::endl;
        }
    });
}


void Connection::setAuthorizationData(const Connection::AuthorizationData &data)
{
    m_authorizationData = data;
    m_baseRequest.setRawHeader("AccessToken", data.accessToken.toUtf8());
}


void Connection::resetAuthorizationData()
{
    m_authorizationData.reset();
    m_baseRequest.setRawHeader("AccessToken", "");
}

}  // namespace app
