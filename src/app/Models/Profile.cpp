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


void Profile::setData(const Data &data)
{
    m_data = data;
    emit dataChanged();
}


void Profile::setEmail(const QString &email)
{
    if (!m_data.has_value())
    {
        return;
    }

    m_data->email = email;
    emit dataChanged();
}


QString Profile::id() const
{
    return m_data.has_value() ? m_data->id : "";
}


QString Profile::userName() const
{
    return m_data.has_value() ? m_data->userName : "";
}


QString Profile::email() const
{
    return m_data.has_value() ? m_data->email : "";
}


Profile::Status Profile::status() const
{
    return m_data.has_value() ? m_data->status : Status::Unknown;
}


QString Profile::ovpnConfigPassword() const
{
    return m_data.has_value() ? m_data->ovpnConfigPassword : "";
}


bool Profile::isTariffPurchased() const
{
    return m_data.has_value() && m_data->tariffData.has_value();
}


QString Profile::tariffId() const
{
    return isTariffPurchased() ? m_data->tariffData->id : "";
}


QDateTime Profile::tariffExpiredAt() const
{
    return isTariffPurchased() ? m_data->tariffData->expiredAt : QDateTime{};
}

}  // namespace app
