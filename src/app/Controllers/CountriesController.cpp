// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "CountriesController.hpp"

#include <QJsonArray>

namespace query
{
using namespace app;

// clang-format off
const auto countriesList = QueryBuilder::createQuery()
    .addObject("country")
        .addUnion("list")
        .withArgument("isPremium")
        .withArgument("hasVpn", true)
        .addUnionVariant("CountryCollection")
            .addArray("data")
                .addItem<QString>("id")
                .addItem<QString>("title")
                .addItem<QString>("description")
                .addItem<QString>("code")
                .addItem<int>("serversCount")
    .build();

// clang-format on
}  // namespace query

namespace app
{
CountriesController::CountriesController(app::Connection &connection,
                                         CountryListModel &freeServersList,
                                         CountryListModel &premiumServersList)
    : m_connection{connection}
    , m_freeServersList{freeServersList}
    , m_premiumServersList{premiumServersList}
{
}


void CountriesController::refreshCountries(bool isPremium)
{
    const auto errorHandler = [this, isPremium](const QNetworkReply &) { emit countriesRequestError(isPremium); };

    const auto successHandler = [this, isPremium](const QJsonDocument &reply) {
        const auto countriesData = reply["data"]["country"]["list"]["data"];

        if (!countriesData.isArray())
        {
            emit countriesRequestError(isPremium);
            return;
        }

        const auto countriesArray = countriesData.toArray();

        QVector<Country> countries;
        countries.reserve(countriesArray.size());

        for (const auto &countryData : countriesArray)
        {
            const auto idData = countryData["id"];
            const auto titleData = countryData["title"];
            const auto descriptionData = countryData["description"];
            const auto codeData = countryData["code"];
            const auto serversCountData = countryData["serversCount"];

            if (idData.isString() && titleData.isString() && descriptionData.isString() && codeData.isString() &&
                serversCountData.isDouble())
            {
                countries.append(Country{idData.toString(), titleData.toString(), descriptionData.toString(),
                                         codeData.toString().toLower(), serversCountData.toInt()});
            }
            else
            {
                emit countriesRequestError(isPremium);
                return;
            }
        }

        if (isPremium)
        {
            m_premiumServersList.updateCountries(countries);
        }
        else
        {
            m_freeServersList.updateCountries(countries);
        }
    };

    m_connection.post(query::countriesList.prepare(isPremium), successHandler, errorHandler);
}

}  // namespace app
