// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ApplicationController.hpp"

#include "../Stuff/Settings.hpp"

namespace
{
constexpr auto APPLICATION_TRAY_ICON = ":images/icon.ico";
constexpr auto APPLICATION_TRAY_TOOLTIP = "EraVPN (%1)";

}  // namespace

namespace app
{
ApplicationController::ApplicationController(ApplicationSettings &applicationSettings,
                                             Profile &profile,
                                             Translation &translation,
                                             VpnConnection &vpnConnection)
    : QObject{nullptr}
    , m_applicationSettings{applicationSettings}
    , m_profile{profile}
    , m_translation{translation}
    , m_vpnConnection{vpnConnection}
{
    m_menu.addAction(&m_quitAction);

    m_systemTrayIcon.setContextMenu(&m_menu);
    m_systemTrayIcon.setIcon(QIcon{APPLICATION_TRAY_ICON});

    updateState();
    connect(&vpnConnection, &VpnConnection::connectedChanged, this, &ApplicationController::updateState);
    connect(&translation, &Translation::languageChanged, this, &ApplicationController::updateState);

    connect(&m_systemTrayIcon, &QSystemTrayIcon::activated, this, &ApplicationController::handleIconEvent);
    connect(&m_quitAction, &QAction::triggered, this, &ApplicationController::quitRequested);
}


ApplicationController::~ApplicationController()
{
    m_systemTrayIcon.hide();
}


void ApplicationController::setTrayIconVisible(bool visible)
{
    m_systemTrayIcon.setVisible(visible);
}


void ApplicationController::refreshSettings()
{
    auto &settings = Settings::instance();
    setCertificateAutoGenerationEnabled(settings.isCertificateAutoGenerationEnabled(m_profile.id()));
}


void ApplicationController::setCertificateAutoGenerationEnabled(bool enabled)
{
    Settings::instance().setCertificateAutoGenerationEnabled(m_profile.id(), enabled);
    m_applicationSettings.setCertificateAutoGenerationEnabled(enabled);
}


void ApplicationController::handleIconEvent(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::DoubleClick:
        case QSystemTrayIcon::Trigger:
            emit showRequested();
            break;

        default:
            break;
    }
}


void ApplicationController::updateState()
{
    // Update context menu
    m_quitAction.setText(tr("Quit"));

    // Update tooltip
    const auto state = m_vpnConnection.connected() ? tr("Connected") : tr("Disconnected");

    m_systemTrayIcon.setToolTip(QString{APPLICATION_TRAY_TOOLTIP}.arg(state));
}

}  // namespace app
