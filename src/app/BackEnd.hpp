#pragma once

#include <QtQml/qqmlengine.h>
#include <QObject>

#include "Connection.hpp"
#include "Controllers/ApplicationController.hpp"
#include "Controllers/CertificateController.hpp"
#include "Controllers/ClipboardController.hpp"
#include "Controllers/CountriesController.hpp"
#include "Controllers/LocationController.hpp"
#include "Controllers/ProfileController.hpp"
#include "Controllers/ReferralClientsController.hpp"
#include "Controllers/TariffController.hpp"
#include "Controllers/TranslationController.hpp"
#include "Controllers/VpnController.hpp"

namespace app
{
Q_NAMESPACE

class BackEnd : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ApplicationController *applicationController READ applicationController CONSTANT)
    Q_PROPERTY(CertificateController *certificateController READ certificateController CONSTANT)
    Q_PROPERTY(ClipboardController *clipboardController READ clipboardController CONSTANT)
    Q_PROPERTY(ProfileController *profileController READ profileController CONSTANT)
    Q_PROPERTY(LocationController *locationController READ locationController CONSTANT)
    Q_PROPERTY(CountriesController *countriesController READ countriesController CONSTANT)
    Q_PROPERTY(ReferralClientsController *referralClientsController READ referralClientsController CONSTANT)
    Q_PROPERTY(TariffController *tariffController READ tariffController CONSTANT)
    Q_PROPERTY(TranslationController *translationController READ translationController CONSTANT)
    Q_PROPERTY(VpnController *vpnController READ vpnController CONSTANT)

    Q_PROPERTY(CountryListModel *freeServersList READ freeServersList CONSTANT)
    Q_PROPERTY(CountryListModel *premiumServersList READ premiumServersList CONSTANT)
    Q_PROPERTY(CertificateListModel *certificateListModel READ certificateListModel CONSTANT)
    Q_PROPERTY(ReferralClientListModel *referralClientListModel READ referralClientListModel CONSTANT)
    Q_PROPERTY(TariffListModel *tariffListModel READ tariffListModel CONSTANT)

    Q_PROPERTY(VpnConnection *vpnConnection READ vpnConnection CONSTANT)
    Q_PROPERTY(Profile *profile READ profile CONSTANT)
    Q_PROPERTY(Location *location READ location CONSTANT)
    Q_PROPERTY(Translation *translation READ translation CONSTANT)

    explicit BackEnd();

public:
    static BackEnd &instance();

    BackEnd(const BackEnd &) = delete;
    BackEnd &operator=(const BackEnd &) = delete;
    BackEnd(BackEnd &&) = delete;
    BackEnd &operator=(BackEnd &&) = delete;

    ApplicationController *applicationController();
    CertificateController *certificateController();
    ClipboardController *clipboardController();
    ProfileController *profileController();
    LocationController *locationController();
    CountriesController *countriesController();
    ReferralClientsController *referralClientsController();
    TariffController *tariffController();
    TranslationController *translationController();
    VpnController *vpnController();

    CountryListModel *freeServersList();
    CountryListModel *premiumServersList();
    CertificateListModel *certificateListModel();
    ReferralClientListModel *referralClientListModel();
    TariffListModel *tariffListModel();

    VpnConnection *vpnConnection();
    Profile *profile();
    Location *location();
    Translation *translation();

private:
    Connection m_connection;

    CountryListModel m_freeServersList{};
    CountryListModel m_premiumServersList{};
    CertificateListModel m_certificateListModel{};
    ReferralClientListModel m_referralClientListModel{};
    TariffListModel m_tariffListModel{};

    VpnConnection m_vpnConnection{};
    Profile m_profile{};
    Location m_location{};
    Translation m_translation{};

    ApplicationController m_applicationController;
    CertificateController m_certificateController;
    ClipboardController m_clipboardController{};
    CountriesController m_countriesController;
    LocationController m_locationController;
    ProfileController m_profileController;
    ReferralClientsController m_referralClientsController;
    TariffController m_tariffController;
    TranslationController m_translationController;
    VpnController m_vpnController;
};

}  // namespace app
