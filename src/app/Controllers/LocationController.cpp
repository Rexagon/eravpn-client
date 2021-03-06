// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "LocationController.hpp"

#include <QJsonDocument>
#include <QNetworkReply>

#include "../Stuff/Logger.hpp"

namespace
{
constexpr auto REQUEST_URL = "http://api.ipstack.com/check?access_key=%1&"
                             "language=%2&format=0&"
                             "fields=ip,country_name,region_name";

constexpr auto MAX_ATTEMPT_COUNT = 10;
}  // namespace

namespace app
{
LocationController::LocationController(const QString &ipStackKey, Location &location, const Translation &translation)
    : QObject{nullptr}
    , m_location{location}
    , m_translation{translation}
    , m_ipStackKey{ipStackKey}
{
    m_reconnectionTimer.setInterval(1000);
    m_reconnectionTimer.setSingleShot(true);

    connect(&m_reconnectionTimer, &QTimer::timeout, this, &LocationController::requestLocation);
    connect(this, &LocationController::tryReconnect, [this] { m_reconnectionTimer.start(); });
}


LocationController::~LocationController()
{
    m_reconnectionTimer.stop();
}


void LocationController::updateCurrentLocation()
{
    if (m_isInProcess)
    {
        return;
    }

    requestLocation();
}


void LocationController::replyHandler(QNetworkReply *reply)
{
    Logger::instance().debug("GET response received");

    const auto hasError = reply->error() != QNetworkReply::NoError;
    if (hasError && m_attemptCount++ < MAX_ATTEMPT_COUNT)
    {
        Logger::instance().debug("Attempt to reconnect");
        emit tryReconnect();
        return;
    }

    std::unique_lock<std::mutex> lock{m_networkManagerMutex};
    m_isInProcess = false;
    m_attemptCount = 0;

    if (hasError)
    {
        Logger::instance().error(QString{"code(%1), %1"}.arg(reply->error()).arg(reply->errorString()));
        emit m_location.errorOccurred();
        return;
    }

    const auto data = QJsonDocument::fromJson(reply->readAll());
    Logger::instance().debug(QString{data.toJson()});

    const auto ipData = data["ip"];
    const auto countryNameData = data["country_name"];
    const auto regionNameData = data["region_name"];

    if (!ipData.isString() || !countryNameData.isString() || !regionNameData.isString())
    {
        emit m_location.errorOccurred();
        return;
    }

    m_location.setData(Location::Data{ipData.toString(), countryNameData.toString(), regionNameData.toString()});
}


void LocationController::requestLocation()
{
    std::unique_lock<std::mutex> lock{m_networkManagerMutex};
    m_isInProcess = true;

    m_networkManager = std::make_unique<QNetworkAccessManager>();

    QNetworkRequest request{QString{REQUEST_URL}.arg(m_ipStackKey).arg(m_translation.language())};
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=UTF-8");
    request.setHeader(QNetworkRequest::UserAgentHeader, "EraVPN Client");
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

    auto *reply = m_networkManager->get(request);
    Logger::instance().debug("GET request sent");

    connect(reply, &QNetworkReply::finished, [this, reply] { replyHandler(reply); });
}

}  // namespace app
