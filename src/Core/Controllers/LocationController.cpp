// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "LocationController.hpp"

#include <iostream>

#include <QJsonDocument>
#include <QNetworkReply>

namespace
{
constexpr auto REQUEST_URL = "http://api.ipstack.com/check?access_key=%1&"
                             "language=ru&format=0&"
                             "fields=ip,country_name,region_name";

}  // namespace

namespace app
{
LocationController::LocationController(const QString &ipstackKey, Location &location)
    : QObject{nullptr}
    , m_location{location}
    , m_ipstackKey{ipstackKey}
{
}


void LocationController::updateCurrentLocation()
{
    m_networkManager.clearConnectionCache();

    QNetworkRequest request{QString{REQUEST_URL}.arg(m_ipstackKey)};
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=UTF-8");
    request.setHeader(QNetworkRequest::UserAgentHeader, "EraVPN Client");
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

    auto *reply = m_networkManager.get(request);
    std::cout << "GET request sent" << std::endl;

    connect(reply, &QNetworkReply::finished, [this, reply] {
        std::cout << "GET response received" << std::endl;

        if (reply->error() != QNetworkReply::NoError)
        {
            std::cout << "Error(" << reply->error() << "): " << reply->errorString().toStdString() << std::endl;
            emit m_location.errorOccurred();
            return;
        }

        const auto data = QJsonDocument::fromJson(reply->readAll());
        std::cout << data.toJson().toStdString() << std::endl;

        const auto ipData = data["ip"];
        const auto countryNameData = data["country_name"];
        const auto regionNameData = data["region_name"];

        if (!ipData.isString() || !countryNameData.isString() || !regionNameData.isString())
        {
            emit m_location.errorOccurred();
            return;
        }

        m_location.setData(Location::Data{ipData.toString(), countryNameData.toString(), regionNameData.toString()});
    });
}

}  // namespace app
