#pragma once

#include <QAction>
#include <QMenu>
#include <QObject>
#include <QSystemTrayIcon>

#include "../Models/ApplicationSettings.hpp"
#include "../Models/Profile.hpp"
#include "../Models/Translation.hpp"
#include "../Models/VpnConnection.hpp"

namespace app
{
class ApplicationController final : public QObject
{
    Q_OBJECT

public:
    explicit ApplicationController(ApplicationSettings &applicationSettings,
                                   Profile &profile,
                                   Translation &translation,
                                   VpnConnection &vpnConnection);
    ~ApplicationController() final;

    Q_INVOKABLE void setTrayIconVisible(bool visible);

    Q_INVOKABLE void refreshSettings();
    Q_INVOKABLE void setCertificateAutoGenerationEnabled(bool enabled);

signals:
    void showRequested();
    void quitRequested();

private:
    void handleIconEvent(QSystemTrayIcon::ActivationReason reason);
    void updateState();

    ApplicationSettings &m_applicationSettings;
    Profile &m_profile;
    Translation &m_translation;
    VpnConnection &m_vpnConnection;

    QMenu m_menu{};
    QAction m_quitAction{};
    QSystemTrayIcon m_systemTrayIcon{};
};

}  // namespace app
