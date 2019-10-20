// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "BackEnd.hpp"

namespace app
{
BackEnd::BackEnd()
    : QObject{nullptr}
    , m_connection{API_URL, this}
    , m_authController{m_connection}
    , m_countriesController{m_connection, m_freeServersList, m_premiumServersList}
    , m_vpnController{m_connection}
{
}


BackEnd &BackEnd::instance()
{
    static BackEnd backEnd;
    return backEnd;
}


AuthController *BackEnd::authController()
{
    return &m_authController;
}


CountriesController *BackEnd::countriesController()
{
    return &m_countriesController;
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

}  // namespace app
