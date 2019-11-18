// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ApplicationSettings.hpp"

namespace app
{
ApplicationSettings::ApplicationSettings()
    : QObject{nullptr}
{
}


void ApplicationSettings::setCertificateAutoGenerationEnabled(bool enabled)
{
    m_isCertificateAutoGenerationEnabled = enabled;

    emit isCertificateAutoGenerationEnabledChanged();
}


bool ApplicationSettings::isCertificateAutoGenerationEnabled() const
{
    return m_isCertificateAutoGenerationEnabled;
}

}  // namespace app
