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

    void setAccessToken(const std::optional<QString> &accessToken);
    std::optional<QString> accessToken() const;

    void setRefreshToken(const std::optional<QString> &refreshToken);
    std::optional<QString> refreshToken() const;

    void setCountryCertificate(const QString &userId,
                               const QString &countryId,
                               const std::optional<CertificateData> &certificateData);
    std::optional<CertificateData> countryCertificate(const QString &userId, const QString &countryId) const;

private:
    QSettings m_settings{};
};
}  // namespace app
