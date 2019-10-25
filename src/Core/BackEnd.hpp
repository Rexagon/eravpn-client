#pragma once

#include <QtQml/qqmlengine.h>
#include <QObject>

#include "Connection.hpp"
#include "Controllers/CountriesController.hpp"
#include "Controllers/ProfileController.hpp"
#include "Controllers/VpnController.hpp"

#include "Models/VpnConnection.hpp"

namespace app
{
Q_NAMESPACE

class BackEnd : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ProfileController *profileController READ profileController CONSTANT)
    Q_PROPERTY(CountriesController *countriesController READ countriesController CONSTANT)
    Q_PROPERTY(VpnController *vpnController READ vpnController CONSTANT)

    Q_PROPERTY(CountryListModel *freeServersList READ freeServersList CONSTANT)
    Q_PROPERTY(CountryListModel *premiumServersList READ premiumServersList CONSTANT)
    Q_PROPERTY(VpnConnection *vpnConnection READ vpnConnection CONSTANT)
    Q_PROPERTY(Profile *profile READ profile CONSTANT)

    explicit BackEnd();

public:
    static BackEnd &instance();

    BackEnd(const BackEnd &) = delete;
    BackEnd &operator=(const BackEnd &) = delete;
    BackEnd(BackEnd &&) = delete;
    BackEnd &operator=(BackEnd &&) = delete;

    ProfileController *profileController();
    CountriesController *countriesController();
    VpnController *vpnController();

    CountryListModel *freeServersList();
    CountryListModel *premiumServersList();

    VpnConnection *vpnConnection();
    Profile *profile();

private:
    Connection m_connection;

    CountryListModel m_freeServersList{};
    CountryListModel m_premiumServersList{};

    VpnConnection m_vpnConnection{};
    Profile m_profile{};

    ProfileController m_authController;
    CountriesController m_countriesController;
    VpnController m_vpnController;
};

}  // namespace app
