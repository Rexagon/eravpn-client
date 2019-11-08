#pragma once

#include <QAction>
#include <QMenu>
#include <QObject>
#include <QSystemTrayIcon>

#include "../Models/Translation.hpp"
#include "../Models/VpnConnection.hpp"

namespace app
{
class ApplicationController final : public QObject
{
    Q_OBJECT

public:
    explicit ApplicationController(VpnConnection &vpnConnection, Translation &translation);
    ~ApplicationController() final;

    Q_INVOKABLE void setTrayIconVisible(bool visible);

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
