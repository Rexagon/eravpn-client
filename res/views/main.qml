import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import "../components"
import "../views"

ApplicationWindow
{
    readonly property FontLoader futuraHeavyFont: FontLoader { source: "../fonts/Futura PT_Heavy.ttf" }
    readonly property FontLoader futuraMediumFont: FontLoader { source: "../fonts/Futura PT_Medium.ttf" }
    readonly property FontLoader rootUiFontBold: FontLoader { source: "../fonts/PT Root UI_Bold.ttf" }
    readonly property FontLoader rootUiFontLight: FontLoader { source: "../fonts/PT Root UI_Light.ttf" }
    readonly property FontLoader rootUiFontMedium: FontLoader { source: "../fonts/PT Root UI_Medium.ttf" }
    readonly property FontLoader rootUiFontRegular: FontLoader { source: "../fonts/PT Root UI_Regular.ttf" }

    property int previousMousePositionX
    property int previousMousePositionY

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

    ColumnLayout {
        anchors.fill: parent

        WindowTitleBar {
            Layout.fillWidth: true

            title: "Вход в аккаунт"

            onTitleBarPressed: {
                previousMousePositionX = x;
                previousMousePositionY = y;
            }

            onTitleBarMoved: {
                window.setX(window.x + (x - previousMousePositionX));
                window.setY(window.y + (y - previousMousePositionY));
            }

            onMinimizeRequested: window.visibility = ApplicationWindow.Minimized
            onCloseRequested: window.close()
        }

        StackView {
            id: viewsContainer

            Layout.fillHeight: true
            Layout.fillWidth: true

            initialItem: loginView
        }

        Component {
            id: loginView

            LoginView {
                onSwitchToRegistration: viewsContainer.replace(registrationView, StackView.PopTransition)
            }
        }

        Component {
            id: registrationView

            RegistrationView {
                onSwitchToLogin: viewsContainer.replace(loginView, StackView.PushTransition)
            }
        }
    }
}
