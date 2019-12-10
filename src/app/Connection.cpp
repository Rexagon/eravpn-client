// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Connection.hpp"

#include "Stuff/Logger.hpp"
#include "Stuff/Settings.hpp"

namespace
{
constexpr auto QUERY_CONTAINER = R"({"query":"%1","variables":{},"operationName":null})";

constexpr auto ACCESS_TOKEN_HEADER = "AccessToken";
constexpr auto REFRESH_TOKEN_HEADER = "RefreshToken";

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

    Logger::instance().debug("POST request sent");
    Logger::instance().debug(query);

    connect(reply, &QNetworkReply::finished, [reply, successCallback, errorCallback]() {
        Logger::instance().debug("POST response received");

        if (reply->error() == QNetworkReply::NoError)
        {
            const auto data = QJsonDocument::fromJson(reply->readAll());
            Logger::instance().debug(QString{data.toJson()});

            successCallback(data);
        }
        else
        {
            Logger::instance().error(QString{"code(%1), %1"}.arg(reply->error()).arg(reply->errorString()));

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
    Logger::instance().debug("GET request sent");

    connect(reply, &QNetworkReply::finished, [reply, successCallback, errorCallback]() {
        Logger::instance().debug("GET response received");

        if (reply->error() == QNetworkReply::NoError)
        {
            successCallback(*reply);
        }
        else
        {
            Logger::instance().error(QString{"code(%1), %1"}.arg(reply->error()).arg(reply->errorString()));

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
    m_baseRequest.setRawHeader(ACCESS_TOKEN_HEADER, data.accessToken.toUtf8());
}


void Connection::resetAuthorizationData()
{
    m_authorizationData.reset();
    m_baseRequest.setRawHeader(ACCESS_TOKEN_HEADER, "");
}


void Connection::setRefreshTokenHeaderActive(bool active)
{
    m_isRefreshTokenHeaderActive = active;

    if (active && m_authorizationData.has_value())
    {
        m_baseRequest.setRawHeader(REFRESH_TOKEN_HEADER, m_authorizationData->refreshToken.toUtf8());
    }
    else
    {
        m_baseRequest.setRawHeader(REFRESH_TOKEN_HEADER, "");
    }
}

}  // namespace app
