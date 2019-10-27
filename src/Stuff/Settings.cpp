// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Settings.hpp"

namespace
{
constexpr auto USER_IDENTIFIER = "user/identifier";
constexpr auto ACCESS_TOKEN = "user/accessToken";
constexpr auto REFRESH_TOKEN = "user/refreshToken";

constexpr auto COUNTRY_CERTIFICATE_ID = "vpn/%1/certificate/%2/id";
constexpr auto COUNTRY_CERTIFICATE_PATH = "vpn/%1/certificate/%2/path";

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


void Settings::setCountryCertificate(const QString &userId,
                                     const QString &countryId,
                                     const std::optional<CertificateData> &certificateData)
{
    set(m_settings, QString{COUNTRY_CERTIFICATE_ID}.arg(userId).arg(countryId),
        certificateData.has_value() ? std::optional{certificateData->id} : std::nullopt);

    set(m_settings, QString{COUNTRY_CERTIFICATE_PATH}.arg(userId).arg(countryId),
        certificateData.has_value() ? std::optional{certificateData->path} : std::nullopt);
}


std::optional<Settings::CertificateData> Settings::countryCertificate(const QString &userId,
                                                                      const QString &countryId) const
{
    const auto idData = get<QString>(m_settings, QString{COUNTRY_CERTIFICATE_ID}.arg(userId).arg(countryId));
    const auto pathData = get<QString>(m_settings, QString{COUNTRY_CERTIFICATE_PATH}.arg(userId).arg(countryId));

    if (!idData.has_value() || !pathData.has_value())
    {
        return std::nullopt;
    }

    return CertificateData{*idData, *pathData};
}

}  // namespace app
