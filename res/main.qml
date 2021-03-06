import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import com.eravpn.backend 1.0

import "components"
import "views"

ApplicationWindow
{
    readonly property FontLoader futuraHeavyFont: FontLoader { source: "fonts/Futura PT_Heavy.ttf" }
    readonly property FontLoader futuraMediumFont: FontLoader { source: "fonts/Futura PT_Medium.ttf" }
    readonly property FontLoader rootUiFontBold: FontLoader { source: "fonts/PT Root UI_Bold.ttf" }
    readonly property FontLoader rootUiFontLight: FontLoader { source: "fonts/PT Root UI_Light.ttf" }
    readonly property FontLoader rootUiFontMedium: FontLoader { source: "fonts/PT Root UI_Medium.ttf" }
    readonly property FontLoader rootUiFontRegular: FontLoader { source: "fonts/PT Root UI_Regular.ttf" }

    property int previousMousePositionX
    property int previousMousePositionY

    property string windowTitleText: ""
    property bool windowTitleButtonsVisible: false

    function minimizeToTray() {
        windowHidingTimer.start();
    }

    id: window
    visible: true
    width: 900
    height: 640

    flags: Qt.FramelessWindowHint | Qt.WindowMinimizeButtonHint | Qt.Window

    background: Rectangle {
        id: gradientBackground

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#16295e" }
            GradientStop { position: 1.0; color: "#0f1444" }
        }
    }

    Connections {
        target: BackEnd.profile
        onAuthorizedChanged: {
            const authorized = BackEnd.profile.authorized;

            BackEnd.applicationController.setTrayIconVisible(authorized);

            if (!authorized) {
                viewsContainer.replace(loginView, StackView.PopTransition);
            }
        }
    }

    Connections {
        target: BackEnd.applicationController

        onShowRequested: {
            window.showNormal();
        }

        onQuitRequested: {
            window.close();
        }
    }

    Connections {
        target: BackEnd.tariffController

        onTariffLinkGenerationError: {
            if (BackEnd.profile.status === Profile.New) {
                notificationArea.notify(qsTr("AccountIsNotActivatedError"));
            } else {
                notificationArea.notify(qsTr("TariffLinkGenerationError"));
            }
        }
    }

    Timer {
        id: windowHidingTimer

        interval: 0
        repeat: false
        running: false

        onTriggered: {
            window.hide();
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        WindowTitleBar {
            id: windowTitleBar

            Layout.fillWidth: true

            onTitleBarPressed: {
                previousMousePositionX = x;
                previousMousePositionY = y;
            }

            onTitleBarMoved: {
                window.setX(window.x + (x - previousMousePositionX));
                window.setY(window.y + (y - previousMousePositionY));
            }

            onOpenProfile: {
                if (viewsContainer.depth === 1) {
                    viewsContainer.push(profileView)
                } else {
                    viewsContainer.replace(profileView)
                }
            }

            onOpenSettings: {
                if (viewsContainer.depth === 1) {
                    viewsContainer.push(settingsView)
                } else {
                    viewsContainer.replace(settingsView)
                }
            }

            onBackToMain: {
                windowTitleBar.state = "";
                viewsContainer.pop();
            }

            onMinimizeRequested: {
                if (BackEnd.profile.authorized) {
                    window.minimizeToTray();
                } else {
                    window.visibility = ApplicationWindow.Minimized
                }
            }
            onCloseRequested: {
                window.close();
            }
        }

        StackView {
            id: viewsContainer

            Layout.fillHeight: true
            Layout.fillWidth: true

            initialItem: loaderStubView
        }

        Component {
            id: loginView

            LoginView {
                onSwitchToRegistration: viewsContainer.replace(registrationView, StackView.PopTransition)
                onSwitchToMain: viewsContainer.replace(mainView, StackView.PushTransition)
            }
        }

        Component {
            id: registrationView

            RegistrationView {
                onSwitchToMain: viewsContainer.replace(mainView, StackView.PushTransition)
                onSwitchToLogin: viewsContainer.replace(loginView, StackView.PushTransition)
                onSwitchToAuthKey: {
                    viewsContainer.replace([
                        authKeyView,
                        {
                            authKey
                        }
                    ], StackView.PushTransition);
                }
            }
        }

        Component {
            id: authKeyView

            AuthKeyView {
                onSwitchToMain: viewsContainer.replace(mainView, StackView.PushTransition)
            }
        }

        Component {
            id: mainView

            MainView {
                onSwitchToTariffSelection: {
                    viewsContainer.push(tariffSelectionView);
                }
            }
        }

        Component {
            id: profileView

            ProfileView {
                onCloseView: {
                    windowTitleBar.state = "";
                    viewsContainer.pop();
                }

                onSwitchToTariffSelection: {
                    viewsContainer.push(tariffSelectionView);
                }
            }
        }

        Component {
            id: settingsView

            SettingsView {
                onCloseView: {
                    windowTitleBar.state = "";
                    viewsContainer.pop();
                }
            }
        }

        Component {
            id: tariffSelectionView

            TariffSelectionView {
                onCloseView: {
                    windowTitleBar.state = "";
                    viewsContainer.pop();
                }
            }
        }

        Component {
            id: loaderStubView

            RememberedSignInView {
                onSwitchToLogin: viewsContainer.replace(loginView, StackView.PushTransition)
                onSwitchToMain: viewsContainer.replace(mainView, StackView.PushTransition)
            }
        }
    }

    NotificationArea {
        id: notificationArea

        z: 1000

        width: 0
        height: 0

        anchors.right: parent.right
        anchors.top: parent.top

        anchors.topMargin: 50
        anchors.rightMargin: 20
    }
}
