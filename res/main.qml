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

    property bool attemptedToSignIn: false

    id: window
    visible: true
    width: 900
    height: 640

    minimumWidth: 300
    flags: Qt.FramelessWindowHint | Qt.WindowMinimizeButtonHint | Qt.Window

    background: Rectangle {
        id: gradientBackground

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#16295e" }
            GradientStop { position: 1.0; color: "#0f1444" }
        }
    }

    Component.onCompleted: {
        BackEnd.profileController.signInRemembered();
    }

    Connections {
        target: BackEnd.profile
        onAuthorizedChanged: {
            if (BackEnd.profile.authorized && !attemptedToSignIn) {
                attemptedToSignIn = true;
                viewsContainer.clear();
                viewsContainer.push(mainViewComponent)
            }
        }
        onSignInErrorOccurred: {
            if (attemptedToSignIn) {
                return;
            }

            attemptedToSignIn = true;
            viewsContainer.clear();
            viewsContainer.push(loginView)
        }
    }

    NotificationArea {
        id: notificationArea

        z: 1000

        width: 300
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top

        anchors.topMargin: 50
        anchors.rightMargin: 20
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

            onMinimizeRequested: window.visibility = ApplicationWindow.Minimized
            onCloseRequested: window.close()
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
                onSwitchToMain: viewsContainer.replace(mainViewComponent, StackView.PushTransition)
            }
        }

        Component {
            id: registrationView

            RegistrationView {
                onSwitchToLogin: viewsContainer.replace(loginView, StackView.PushTransition)
                onSwitchToMain: viewsContainer.replace(mainViewComponent, StackView.PushTransition)
            }
        }

        Component {
            id: mainViewComponent

            MainView {
                id: mainView
            }
        }

        Component {
            id: profileView

            ProfileView {
                onCloseView: {
                    windowTitleBar.state = "";
                    mainView.updateTitle();
                    viewsContainer.pop();
                }
            }
        }

        Component {
            id: settingsView

            SettingsView {
                onCloseView: {
                    windowTitleBar.state = "";
                    mainView.updateTitle();
                    viewsContainer.pop();
                }
            }
        }

        Component {
            id: loaderStubView

            Item {
                anchors.fill: parent

                Image {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter

                    width: 30
                    height: 30

                    source: "../images/loading.svg"

                    RotationAnimation on rotation {
                        loops: Animation.Infinite
                        duration: 1000
                        from: 0
                        to: 360
                    }
                }
            }
        }
    }
}
