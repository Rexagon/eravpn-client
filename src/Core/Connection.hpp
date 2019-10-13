#pragma once

#include <functional>
#include <optional>

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

    using Callback = std::function<void(QNetworkReply &)>;

    explicit Connection(const QString &apiUrl, QObject *parent);

    void sendQuery(const QString &query, const Callback &callback);

    void setAuthorizationData(const AuthorizationData &data);
    void resetAuthorizationData();

private:
    QNetworkRequest m_baseRequest;
    std::optional<AuthorizationData> m_authorizationData;

    QNetworkAccessManager m_networkManager{};
};

}  // namespace app
