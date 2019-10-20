#pragma once

#include <QtQml/qqmlengine.h>
#include <QObject>

#include "Connection.hpp"
#include "Controllers/AuthController.hpp"
#include "Controllers/CountriesController.hpp"
#include "Controllers/VpnController.hpp"

#include "Models/VpnConnection.hpp"

namespace app
{
Q_NAMESPACE

class BackEnd : public QObject
{
    Q_OBJECT

    Q_PROPERTY(AuthController *authController READ authController CONSTANT)
    Q_PROPERTY(CountriesController *countriesController READ countriesController CONSTANT)
    Q_PROPERTY(VpnController *vpnController READ vpnController CONSTANT)

    Q_PROPERTY(CountryListModel *freeServersList READ freeServersList CONSTANT)
    Q_PROPERTY(CountryListModel *premiumServersList READ premiumServersList CONSTANT)
    Q_PROPERTY(VpnConnection *vpnConnection READ vpnConnection CONSTANT)

    explicit BackEnd();

public:
    static BackEnd &instance();

    BackEnd(const BackEnd &) = delete;
    BackEnd &operator=(const BackEnd &) = delete;
    BackEnd(BackEnd &&) = delete;
    BackEnd &operator=(BackEnd &&) = delete;

    AuthController *authController();
    CountriesController *countriesController();
    VpnController *vpnController();

    CountryListModel *freeServersList();
    CountryListModel *premiumServersList();

    VpnConnection *vpnConnection();

private:
    Connection m_connection;

    CountryListModel m_freeServersList{};
    CountryListModel m_premiumServersList{};

    VpnConnection m_vpnConnection{};

    AuthController m_authController;
    CountriesController m_countriesController;
    VpnController m_vpnController;
};

}  // namespace app
