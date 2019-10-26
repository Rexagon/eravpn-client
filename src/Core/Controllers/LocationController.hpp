#pragma once

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QObject>

#include "../Models/Location.hpp"

namespace app
{
class LocationController : public QObject
{
    Q_OBJECT

public:
    explicit LocationController(const QString &ipstackKey, Location &location);

    Q_INVOKABLE void updateCurrentLocation();

private:
    Location &m_location;

    QString m_ipstackKey;

    QNetworkAccessManager m_networkManager{};
};

}  // namespace app
