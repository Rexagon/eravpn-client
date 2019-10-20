#pragma once

#include "../Connection.hpp"

namespace app
{
class VpnController : public QObject
{
    Q_OBJECT

public:
    explicit VpnController(Connection &connection);

    Q_INVOKABLE void enableVpn(const QString &countryId);

private:
    Connection &m_connection;
};

}  // namespace app
