// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "BackEnd.hpp"

namespace app
{
BackEnd::BackEnd()
    : QObject{nullptr}
    , m_connection{API_URL}
    , m_countriesController{m_connection, m_freeServersList, m_premiumServersList}
    , m_locationController{IPSTACK_KEY, m_location}
    , m_profileController{m_connection, m_profile}
    , m_vpnController{m_connection, m_profile, m_vpnConnection}
{
}


BackEnd &BackEnd::instance()
{
    static BackEnd backEnd;
    return backEnd;
}


CountriesController *BackEnd::countriesController()
{
    return &m_countriesController;
}


LocationController *BackEnd::locationController()
{
    return &m_locationController;
}


ProfileController *BackEnd::profileController()
{
    return &m_profileController;
}


VpnController *BackEnd::vpnController()
{
    return &m_vpnController;
}


CountryListModel *BackEnd::freeServersList()
{
    return &m_freeServersList;
}


CountryListModel *BackEnd::premiumServersList()
{
    return &m_premiumServersList;
}


VpnConnection *BackEnd::vpnConnection()
{
    return &m_vpnConnection;
}


Profile *BackEnd::profile()
{
    return &m_profile;
}


Location *BackEnd::location()
{
    return &m_location;
}

}  // namespace app
