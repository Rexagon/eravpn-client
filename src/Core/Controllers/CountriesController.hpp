#pragma once

#include "../Connection.hpp"
#include "../Models/CountryListModel.hpp"

namespace app
{
class CountriesController : public QObject
{
    Q_OBJECT

public:
    explicit CountriesController(Connection &connection,
                                 CountryListModel &freeServersList,
                                 CountryListModel &premiumServersList);

    Q_INVOKABLE void refreshCountries(bool isPremium);

signals:
    void countriesRequestError(bool isPremium);

private:
    Connection &m_connection;

    CountryListModel &m_freeServersList;
    CountryListModel &m_premiumServersList;
};

}  // namespace app
