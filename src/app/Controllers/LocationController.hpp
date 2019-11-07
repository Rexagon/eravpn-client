#pragma once

#include <mutex>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QObject>
#include <QTimer>

#include "../Models/Location.hpp"
#include "TranslationController.hpp"

namespace app
{
class LocationController final : public QObject
{
    Q_OBJECT

public:
    explicit LocationController(const QString &ipStackKey, Location &location, const Translation &translation);
    ~LocationController() override;

    Q_INVOKABLE void updateCurrentLocation();

signals:
    void tryReconnect();

private:
    void replyHandler(QNetworkReply *reply);
    void requestLocation();

    Location &m_location;
    const Translation &m_translation;

    QString m_ipStackKey;

    std::mutex m_networkManagerMutex{};
    bool m_isInProcess{};
    size_t m_attemptCount{};
    std::unique_ptr<QNetworkAccessManager> m_networkManager{};

    QTimer m_reconnectionTimer{};
};

}  // namespace app
