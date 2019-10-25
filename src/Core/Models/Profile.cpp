// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Profile.hpp"

namespace app
{
Profile::Profile()
    : QObject{nullptr}
{
}


void Profile::signIn()
{
    m_authorized = true;
    emit authorizedChanged();
}


void Profile::signOut()
{
    m_authorized = false;
    emit authorizedChanged();
}


bool Profile::authorized() const
{
    return m_authorized;
}


void Profile::setData(const ClientData &clientData)
{
    m_clientData = clientData;
    emit dataChanged();
}


QString Profile::id() const
{
    return m_clientData.has_value() ? m_clientData->id : "";
}


QString Profile::userName() const
{
    return m_clientData.has_value() ? m_clientData->userName : "";
}


QString Profile::email() const
{
    return m_clientData.has_value() ? m_clientData->email : "";
}


void Profile::setCurrentIp(const QString &ip)
{
    m_currentIp = ip;
    emit currentIpChanged();
}


QString Profile::currentIp() const
{
    return m_currentIp;
}

}  // namespace app
