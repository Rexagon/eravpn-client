import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import "../components"
import "../components/era"
import "../components/settings"

Item {
    readonly property string lightBackgroundColor: "#4f6699"
    readonly property string darkBackgroundColor: "#0f1444"

    signal closeView

    id: view

    StackView.onActivating: {
        windowTitleText = "Настройки"
        windowTitleButtonsVisible = true
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Escape) {
            view.closeView();
        }
    }

    ScrollView {
        anchors.fill: parent
        anchors.leftMargin: 56
        anchors.rightMargin: 16

        clip: true

        ScrollBar.vertical: ScrollBar {
            id: scrollBar

            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom

            width: 10

            background: ColumnLayout {
                Item {
                    Layout.minimumHeight: 4
                }

                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Rectangle {
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.horizontalCenter: parent.horizontalCenter

                        color: darkBackgroundColor
                        width: 2
                    }
                }

                Item {
                    Layout.minimumHeight: 4
                }
            }

            contentItem: Rectangle {
                implicitWidth: 6
                implicitHeight: 100
                radius: width / 2

                color: scrollBar.pressed ? darkBackgroundColor : lightBackgroundColor
            }
        }

        ColumnLayout {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: window.width - 56 * 2

            SettingsGroup {
                z: 100

                Layout.fillWidth: true
                Layout.minimumHeight: 100

                withToggleButton: true

                title: "Безопасный разрыв соединения"
                description: "Если соединение с vpn будет нестабильным, то при его отключении, сервис зашифрует и прервёт передачу данных через провайдера."
            }

            Separator {
                Layout.fillWidth: true
            }

            SettingsGroup {
                z: 100

                Layout.fillWidth: true
                Layout.minimumHeight: 100

                withToggleButton: true

                title: "Использовать наши DNS"
                description: "Для полной конфиденциальности в сети рекомендуем вам использовать наши собственные доменные серверы, чтобы никто не мог узнать, какие сайты вы посещали."
            }

            Separator {
                Layout.fillWidth: true
            }

            SettingsGroup {
                Layout.fillWidth: true
                Layout.minimumHeight: 100

                title: "White connection"
                description: "Внесите в список сайты, которые вы хотите посещать напрямую, без прослойки Era VPN. Например: ваш онлайн банк."
            }

            TextArea {
                z: 100

                Layout.fillWidth: true
                Layout.minimumHeight: 100

                placeholderText: "Введите адрес сайта"
                font.family: rootUiFontRegular.name
                font.pointSize: 12

                background: Rectangle {
                    color: "white"
                    radius: 3
                }
            }

            EraButton {
                z: 100

                Layout.alignment: Qt.AlignRight
                Layout.minimumWidth: 120
                Layout.minimumHeight: 40

                contentItem: Text {
                    text: "Сохранить"
                    color: "white"

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

                    font.family: rootUiFontRegular.name
                    font.pointSize: 12
                }
            }

            Separator {
                Layout.fillWidth: true
            }

            SettingsGroup {
                Layout.fillWidth: true
                Layout.minimumHeight: 100

                title: "Multi connection"
                description: "Для большей надёжности вы можете пропускать ваш интернет трафик через два ниших сервера, чтобы исключить малейшую вероятность вычисления вашего реального IP."
            }
        }
    }
}
