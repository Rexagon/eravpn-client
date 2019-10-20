// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "VpnController.hpp"

namespace app
{
VpnController::VpnController(Connection &connection)
    : QObject{nullptr}
    , m_connection{connection}
{
}


void VpnController::enableVpn(const QString &countryId)
{
}

}  // namespace app
