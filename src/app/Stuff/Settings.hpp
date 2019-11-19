#pragma once

#include <optional>

#include <QSettings>

namespace app
{
class Settings
{
    explicit Settings();

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
                               const std::optional<QString> &certificateId);
    std::optional<CertificateData> countryCertificate(const QString &userId, const QString &countryId) const;

    void setLastConnectedCountry(const QString &userId, const QString &countryId);
    std::optional<QString> lastConnectedCountry(const QString &userId);

    void setCertificateAutoGenerationEnabled(const QString &userId, bool enabled);
    bool isCertificateAutoGenerationEnabled(const QString &userId) const;

    void setLanguage(const QString &language);
    std::optional<QString> getLanguage() const;

    QString createCertificatePath(const QString &certificateId);
    const QString &configsDirectory() const;

private:
    QSettings m_settings{};
    QString m_configsDirectory;
};
}  // namespace app
