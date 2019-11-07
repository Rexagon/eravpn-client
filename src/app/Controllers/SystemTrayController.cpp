// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "SystemTrayController.hpp"

namespace
{
constexpr auto APPLICATION_TRAY_ICON = ":images/icon.ico";
constexpr auto APPLICATION_TRAY_TOOLTIP = "EraVPN (%1)";

}  // namespace

namespace app
{
SystemTrayController::SystemTrayController(VpnConnection &vpnConnection, Translation &translation)
    : QObject{nullptr}
    , m_vpnConnection{vpnConnection}
    , m_translation{translation}
{
    m_menu.addAction(&m_quitAction);

    m_systemTrayIcon.setContextMenu(&m_menu);
    m_systemTrayIcon.setIcon(QIcon{APPLICATION_TRAY_ICON});
    m_systemTrayIcon.show();

    updateState();
    connect(&vpnConnection, &VpnConnection::connectedChanged, this, &SystemTrayController::updateState);
    connect(&translation, &Translation::languageChanged, this, &SystemTrayController::updateState);

    connect(&m_systemTrayIcon, &QSystemTrayIcon::activated, this, &SystemTrayController::handleIconEvent);
    connect(&m_quitAction, &QAction::triggered, this, &SystemTrayController::quitRequested);
}


SystemTrayController::~SystemTrayController()
{
    m_systemTrayIcon.hide();
}


void SystemTrayController::handleIconEvent(QSystemTrayIcon::ActivationReason reason)
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


void SystemTrayController::updateState()
{
    // Update context menu
    m_quitAction.setText(tr("Quit"));

    // Update tooltip
    const auto state = m_vpnConnection.connected() ? tr("Connected") : tr("Disconnected");

    m_systemTrayIcon.setToolTip(QString{APPLICATION_TRAY_TOOLTIP}.arg(state));
}

}  // namespace app
