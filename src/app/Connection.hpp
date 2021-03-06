#pragma once

#include <functional>
#include <optional>

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>

#include "Stuff/QueryBuilder.hpp"
#include "Stuff/StringHelpers.hpp"

namespace app
{
class Connection : public QObject
{
    Q_OBJECT

public:
    struct AuthorizationData
    {
        QString accessToken;
        QString refreshToken;
    };

    using RawCallback = std::function<void(QNetworkReply &)>;
    using JsonCallback = std::function<void(const QJsonDocument &)>;

    explicit Connection(const QString &apiUrl);

    void post(const QString &query,
                   const JsonCallback &successCallback,
                   const std::optional<RawCallback> &errorCallback = std::nullopt);

    void get(const QString &url,
             const RawCallback &successCallback,
             const std::optional<RawCallback> &errorCallback = std::nullopt);

    void setAuthorizationData(const AuthorizationData &data);
    void resetAuthorizationData();

    void setRefreshTokenHeaderActive(bool active);

private:
    QNetworkRequest m_baseRequest;
    std::optional<AuthorizationData> m_authorizationData{};

    bool m_isRefreshTokenHeaderActive{false};

    QNetworkAccessManager m_networkManager{};
};

}  // namespace app
