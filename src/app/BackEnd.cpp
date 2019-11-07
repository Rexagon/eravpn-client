// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "BackEnd.hpp"

namespace app
{
BackEnd::BackEnd()
    : QObject{nullptr}
    , m_connection{API_URL}
    , m_certificateController{m_connection, m_profile, m_certificateListModel}
    , m_countriesController{m_connection, m_freeServersList, m_premiumServersList}
    , m_locationController{IPSTACK_KEY, m_location, m_translation}
    , m_profileController{m_connection, m_profile}
    , m_systemTrayController{m_vpnConnection, m_translation}
    , m_tariffController{m_connection, m_tariffListModel}
    , m_translationController{m_translation}
    , m_vpnController{m_connection, m_profile, m_vpnConnection}
{
}


BackEnd &BackEnd::instance()
{
    static BackEnd backEnd;
    return backEnd;
}


CertificateController *BackEnd::certificateController()
{
    return &m_certificateController;
}


ClipboardController *BackEnd::clipboardController()
{
    return &m_clipboardController;
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


SystemTrayController *BackEnd::systemTrayController()
{
    return &m_systemTrayController;
}


TariffController *BackEnd::tariffController()
{
    return &m_tariffController;
}


TranslationController *BackEnd::translationController()
{
    return &m_translationController;
}


VpnController *BackEnd::vpnController()
{
    return &m_vpnController;
}


CertificateListModel *BackEnd::certificateListModel()
{
    return &m_certificateListModel;
}


CountryListModel *BackEnd::freeServersList()
{
    return &m_freeServersList;
}


CountryListModel *BackEnd::premiumServersList()
{
    return &m_premiumServersList;
}


TariffListModel *BackEnd::tariffListModel()
{
    return &m_tariffListModel;
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


Translation *BackEnd::translation()
{
    return &m_translation;
}

}  // namespace app
