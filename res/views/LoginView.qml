import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import com.eravpn.backend 1.0

import "../components/era"
import "../components"

Item {
    readonly property Item loadingSpinner: Item {
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

    signal switchToRegistration
    signal switchToMain

    id: view

    function formAction() {
        view.state = "loading";
        BackEnd.profileController.signIn(identificatorInput.text, passwordInput.text);
    }

    property bool isInputValid: {
        const password = passwordInput.text;

        return identificatorInput.text.length > 0 &&
                password.length > 0 && password.length <= 16;
    }

    StackView.onActivating: {
        windowTitleText = "Вход в аккаунт"
        windowTitleButtonsVisible = false
    }

    Connections {
        target: BackEnd.profile
        onAuthorizedChanged: {
            if (BackEnd.profile.authorized) {
                view.switchToMain()
            }
        }
        onSignInErrorOccurred: {
            notificationArea.notify("Неправильный логин или пароль");
            view.state = "";
        }
    }

    states: [
        State {
            name: "loading"
            PropertyChanges {
                target: identificatorInput
                enabled: false
            }
            PropertyChanges {
                target: passwordInput
                enabled: false
            }
            PropertyChanges {
                target: loginButton
                enabled: false
            }
        }
    ]

    BackgroundMap {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

    Item {
        width: 285
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        Item {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.verticalCenter
            anchors.bottomMargin: 40

            Logo {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: logoText.top
                anchors.bottomMargin: 5
            }

            Text {
                id: logoText

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: logoSmallText.top
                anchors.bottomMargin: 5

                text: "EraVPN"

                font.family: futuraHeavyFont.name
                font.pointSize: 17
                color: "white"
            }

            Text {
                id: logoSmallText

                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right

                horizontalAlignment: Text.AlignHCenter

                text: "EraVPN – это, пожалуй, самый быстрый\nи безопасный способ подключения к сети"
                textFormat: Text.PlainText

                font.family: futuraMediumFont.name
                font.pointSize: 10

                color: "#a4acca"
            }
        }

        ColumnLayout {
            anchors.top: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right

            spacing: 10

            Keys.onPressed: {
                if (isInputValid && (event.key === Qt.Key_Enter || event.key === Qt.Key_Return)) {
                    view.formAction();
                }
            }

            EraTextField {
                id: identificatorInput

                focus: true

                placeholderText: "Введите логин или email"

                Layout.fillWidth: true
                Layout.minimumHeight: 44

                large: true
            }

            EraPasswordField {
                id: passwordInput

                placeholderText: "Введите пароль"

                Layout.fillWidth: true
                Layout.minimumHeight: 44

                large: true
            }

            EraButton {
                id: loginButton

                text: "Вход"

                enabled: view.isInputValid

                onClicked: formAction()

                Layout.fillWidth: true
                Layout.minimumHeight: 44

                large: true
            }

            RowLayout {
                Layout.fillWidth: true

                /*
                EraLink {
                    text: "Забыли пароль?"
                }

                Item {
                    Layout.fillWidth: true
                }
                */

                EraLink {
                    text: "Зарегистрироваться"
                    horizontalAlignment: Text.AlignHCenter /* Qt.AlignRight */
                    onClicked: view.switchToRegistration()

                    Layout.fillWidth: true /* temp */
                }
            }
        }
    }
}
