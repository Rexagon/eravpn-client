// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Settings.hpp"

namespace
{
constexpr auto USER_IDENTIFIER = "user/identifier";
constexpr auto ACCESS_TOKEN = "user/accessToken";
constexpr auto REFRESH_TOKEN = "user/refreshToken";

constexpr auto COUNTRY_CERTIFICATE = "vpn/certificate/%1";

template <typename T>
void set(QSettings &settings, const QString &key, const std::optional<T> &value)
{
    if (value)
    {
        settings.setValue(key, *value);
    }
    else
    {
        settings.remove(key);
    }
}

template <typename T>
std::optional<T> get(const QSettings &settings, const QString &key)
{
    const auto variant = settings.value(key);

    if (variant.isNull())
    {
        return std::nullopt;
    }

    return variant.value<T>();
}

}  // namespace

namespace app
{
Settings &Settings::instance()
{
    static Settings settings;
    return settings;
}


void Settings::reset()
{
    m_settings.clear();
}


void Settings::setUserIdentifier(const std::optional<QString> &identifier)
{
    set(m_settings, USER_IDENTIFIER, identifier);
}


std::optional<QString> Settings::userIdentifier() const
{
    return get<QString>(m_settings, USER_IDENTIFIER);
}


void Settings::setAccessToken(const std::optional<QString> &accessToken)
{
    set(m_settings, ACCESS_TOKEN, accessToken);
}


std::optional<QString> Settings::accessToken() const
{
    return get<QString>(m_settings, ACCESS_TOKEN);
}


void Settings::setRefreshToken(const std::optional<QString> &refreshToken)
{
    set(m_settings, REFRESH_TOKEN, refreshToken);
}


std::optional<QString> Settings::refreshToken() const
{
    return get<QString>(m_settings, REFRESH_TOKEN);
}


void Settings::setCountryCertificatePath(const QString &countryId, const std::optional<QString> &path)
{
    set(m_settings, QString{COUNTRY_CERTIFICATE}.arg(countryId), path);
}


std::optional<QString> Settings::countryCertificatePath(const QString &countryId) const
{
    return get<QString>(m_settings, QString{COUNTRY_CERTIFICATE}.arg(countryId));
}

}  // namespace app
