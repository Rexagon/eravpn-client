#pragma once

#include "../Connection.hpp"
#include "../Models/Profile.hpp"
#include "../Models/VpnConnection.hpp"

namespace app
{
class VpnController : public QObject
{
    Q_OBJECT

public:
    explicit VpnController(Connection &connection, Profile &profile, VpnConnection &vpnConnection);

    Q_INVOKABLE void start(const QString &countryId);
    Q_INVOKABLE void stop();

private:
    Connection &m_connection;
    Profile &m_profile;
    VpnConnection &m_vpnConnection;

    QString m_configDirectory;
};

}  // namespace app
