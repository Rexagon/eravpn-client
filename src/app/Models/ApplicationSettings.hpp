#pragma once

#include <QObject>

namespace app
{
class ApplicationSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isCertificateAutoGenerationEnabled READ isCertificateAutoGenerationEnabled NOTIFY
                   isCertificateAutoGenerationEnabledChanged)

public:
    explicit ApplicationSettings();

    void setCertificateAutoGenerationEnabled(bool enabled);
    bool isCertificateAutoGenerationEnabled() const;

signals:
    bool isCertificateAutoGenerationEnabledChanged();

private:
    bool m_isCertificateAutoGenerationEnabled{false};
};

}  // namespace app
