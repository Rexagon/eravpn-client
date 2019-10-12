import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import "../components"

Item {
    signal switchToRegistration

    id: view

    function loginAction() {
        console.log('login');
    }

    EraBackgroundMap {}

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

            EraLogo {
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
                if (event.key === Qt.Key_Enter || event.key === Qt.Key_Return) {
                    view.loginAction();
                }
            }

            EraTextField {
                id: emailInput

                focus: true

                placeholderText: "Введите email"

                Layout.fillWidth: true
                Layout.minimumHeight: 44
            }

            EraPasswordField {
                id: passwordInput

                placeholderText: "Введите пароль"

                Layout.fillWidth: true
                Layout.minimumHeight: 44
            }

            EraButton {
                id: loginButton

                text: "Вход"

                onClicked: loginAction()

                Layout.fillWidth: true
                Layout.minimumHeight: 44
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
