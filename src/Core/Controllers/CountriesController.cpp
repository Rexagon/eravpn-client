// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "CountriesController.hpp"

#include <QJsonArray>

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
    const auto query = QString{R"(query {
  country {
    list(isPremium: %1, hasVpn: true) {
      ... on CountryCollection {
        data {
          id
          title
          description
          code
          serversCount
        }
      }
    }
  }
})"};

    m_connection.post(query.arg(isPremium ? "true" : "false"), [this, isPremium](const QJsonDocument &reply) {
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
                                         codeData.toString(), serversCountData.toInt()});
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
    });
}

}  // namespace app
