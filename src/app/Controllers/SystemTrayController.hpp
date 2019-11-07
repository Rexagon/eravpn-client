#pragma once

#include <QAction>
#include <QMenu>
#include <QObject>
#include <QSystemTrayIcon>

#include "../Models/Translation.hpp"
#include "../Models/VpnConnection.hpp"

namespace app
{
class SystemTrayController : public QObject
{
    Q_OBJECT

public:
    explicit SystemTrayController(VpnConnection &vpnConnection, Translation &translation);
    virtual ~SystemTrayController();

signals:
    void showRequested();
    void quitRequested();

private:
    void handleIconEvent(QSystemTrayIcon::ActivationReason reason);
    void updateState();

    VpnConnection &m_vpnConnection;
    Translation &m_translation;

    QMenu m_menu{};
    QAction m_quitAction{};
    QSystemTrayIcon m_systemTrayIcon{};
};

}  // namespace app
