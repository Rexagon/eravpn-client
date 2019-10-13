#pragma once

#include <functional>
#include <optional>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>

namespace app
{
class Connection : public QObject
{
    Q_OBJECT

public:
    using Callback = std::function<void(QNetworkReply &)>;

    explicit Connection(const QString &apiUrl, QObject *parent);

    void sendQuery(const QString &query, const Callback &callback);

private:
    QNetworkRequest m_baseRequest;

    QNetworkAccessManager m_networkManager{};
};

}  // namespace app
