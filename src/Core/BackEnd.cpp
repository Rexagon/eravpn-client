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


CountryListModel *BackEnd::freeServersList()
{
    return &m_freeServersList;
}


CountryListModel *BackEnd::premiumServersList()
{
    return &m_premiumServersList;
}

}  // namespace app
