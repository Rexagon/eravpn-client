import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import "../components"

Item {
    id: container

    Image {
        id: image
        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }

        source: "../images/map.png"
        fillMode: Image.PreserveAspectFit
    }

    Item {
        id: logoContainer

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.verticalCenter
        anchors.bottomMargin: 40

        Image {
            id: logo

            width: 85

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: logoText.top
            anchors.bottomMargin: 5

            source: "../images/logo_small.png"

            fillMode: Image.PreserveAspectFit
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
        id: inputFieldsComponent

        anchors.top: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right

        spacing: 10

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

            Layout.fillWidth: true
            Layout.minimumHeight: 44
        }

        RowLayout {
            Layout.fillWidth: true

            EraLink {
                text: "Забыли пароль?"
                onClicked: console.log("clicked forget")
            }

            Item {
                Layout.fillWidth: true
            }

            EraLink {
                text: "Перейти на сайт"
                horizontalAlignment: Text.AlignRight
                onClicked: Qt.openUrlExternally('https://eravpn.com/')
            }
        }
    }
}
