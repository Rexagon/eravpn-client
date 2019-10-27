#pragma once

#include <optional>

#include <QSettings>

namespace app
{
class Settings
{
    explicit Settings() = default;

public:
    struct CertificateData
    {
        QString id;
        QString path;
    };

    static Settings &instance();

    Settings(const Settings &) = delete;
    Settings &operator=(const Settings &) = delete;
    Settings(Settings &&) = delete;
    Settings &operator=(Settings &&) = delete;

    void reset();

    void setUserIdentifier(const std::optional<QString> &identifier);
    std::optional<QString> userIdentifier() const;

    void setAccessToken(const std::optional<QString> &accessToken);
    std::optional<QString> accessToken() const;

    void setRefreshToken(const std::optional<QString> &refreshToken);
    std::optional<QString> refreshToken() const;

    void setCountryCertificate(const QString &countryId, const std::optional<CertificateData> &certificateData);
    std::optional<CertificateData> countryCertificate(const QString &countryId) const;

private:
    QSettings m_settings{};
};
}  // namespace app
