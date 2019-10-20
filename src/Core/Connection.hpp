#pragma once

#include <functional>
#include <optional>

#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>

#include "../Stuff/StringHelpers.hpp"

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

    using SuccessCallback = std::function<void(const QJsonDocument &)>;
    using ErrorCallback = std::function<void(const QNetworkReply &)>;

    explicit Connection(const QString &apiUrl, QObject *parent);

    void sendQuery(const QString &query,
                   const SuccessCallback &successCallback,
                   const std::optional<ErrorCallback> &errorCallback = std::nullopt);

    void setAuthorizationData(const AuthorizationData &data);
    void resetAuthorizationData();

private:
    QNetworkRequest m_baseRequest;
    std::optional<AuthorizationData> m_authorizationData;

    QNetworkAccessManager m_networkManager{};
};

}  // namespace app
