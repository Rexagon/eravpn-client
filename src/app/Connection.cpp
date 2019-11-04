// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Connection.hpp"

#include <iostream>

#include "Stuff/Settings.hpp"

namespace
{
constexpr auto QUERY_CONTAINER = R"({"query":"%1","variables":{},"operationName":null})";
}  // namespace


namespace app
{
Connection::Connection(const QString &url)
    : QObject{nullptr}
    , m_baseRequest{url}
{
    m_baseRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=UTF-8");
    m_baseRequest.setHeader(QNetworkRequest::UserAgentHeader, "EraVPN Client");
    m_baseRequest.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

    const auto &settings = Settings::instance();
    const auto accessToken = settings.accessToken();
    const auto refreshToken = settings.refreshToken();
    if (accessToken.has_value() && refreshToken.has_value())
    {
        setAuthorizationData(AuthorizationData{*accessToken, *refreshToken});
    }
}


void Connection::post(const QString &query,
                           const JsonCallback &successCallback,
                           const std::optional<RawCallback> &errorCallback)
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
}


void Connection::get(const QString &url,
                     const Connection::RawCallback &successCallback,
                     const std::optional<RawCallback> &errorCallback)
{
    auto request = QNetworkRequest{m_baseRequest};
    request.setUrl(url);

    auto *reply = m_networkManager.get(request);
    std::cout << "GET request sent" << std::endl;

    connect(reply, &QNetworkReply::finished, [reply, successCallback, errorCallback]() {
        std::cout << "GET response received" << std::endl;

        if (reply->error() == QNetworkReply::NoError)
        {
            successCallback(*reply);
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
