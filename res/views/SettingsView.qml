import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import com.eravpn.backend 1.0

import "../components"
import "../components/era"
import "../components/settings"

Item {
    readonly property string lightBackgroundColor: "#4f6699"
    readonly property string darkBackgroundColor: "#0f1444"

    signal closeView

    id: view

    StackView.onActivating: {
        windowTitleText = qsTr("Settings")
        windowTitleButtonsVisible = true
        windowTitleBar.state = "settings_opened";
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Escape) {
            view.closeView();
        }
    }

    Item {
        anchors.fill: parent
        anchors.topMargin: 16
        anchors.leftMargin: 56
        anchors.rightMargin: 16

        /*clip: true

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
        */

        ColumnLayout {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: window.width - 56 * 2

            EraBackButton {
                Layout.alignment: Qt.AlignLeft

                onClicked: view.closeView()
            }

            Text {
                text: qsTr("Settings")

                color: "white"

                font.family: futuraHeavyFont.name
                font.pointSize: 20
            }

            Item {
                implicitHeight: 20
            }

            SettingsGroup {
                Layout.fillWidth: true
                Layout.minimumHeight: 30

                title: qsTr("SelectLanguage")
            }

            RowLayout {
                Layout.fillWidth: true
                Layout.minimumHeight: 60

                spacing: 10

                EraButton {
                    Layout.minimumWidth: 200
                    Layout.minimumHeight: 40

                    text: "English"

                    enabled: BackEnd.translation.language !== "en"

                    onClicked: {
                        BackEnd.translationController.setLanguage("en");
                    }
                }

                EraButton {
                    Layout.minimumWidth: 200
                    Layout.minimumHeight: 40

                    text: "Русский"

                    enabled: BackEnd.translation.language !== "ru"

                    onClicked: {
                        BackEnd.translationController.setLanguage("ru");
                    }
                }
            }

            Separator {
                Layout.fillWidth: true
            }

            SettingsGroup {
                Layout.fillWidth: true
                Layout.minimumHeight: 100

                withToggleButton: true

                title: qsTr("AutoGenerateCertificates")
                description: qsTr("AutoGenerateCertificatesDescription")
            }

            Item {
                Layout.fillHeight: true
            }

            /*
            Separator {
                Layout.fillWidth: true
            }

            SettingsGroup {
                Layout.fillWidth: true
                Layout.minimumHeight: 100

                withToggleButton: true

                title: qsTr("SafeDisconnection")
                description: qsTr("SafeDisconnectionDescription")
            }

            Separator {
                Layout.fillWidth: true
            }

            SettingsGroup {
                Layout.fillWidth: true
                Layout.minimumHeight: 100

                withToggleButton: true

                title: qsTr("UseOurDns")
                description: qsTr("UseOurDnsDescription")
            }

            Separator {
                Layout.fillWidth: true
            }

            SettingsGroup {
                Layout.fillWidth: true
                Layout.minimumHeight: 100

                title: qsTr("WhiteConnection")
                description: qsTr("WhiteConnectionDescription")
            }

            TextArea {
                Layout.fillWidth: true
                Layout.minimumHeight: 100

                placeholderText: qsTr("EnterWebsiteAddress")
                font.family: rootUiFontRegular.name
                font.pointSize: 12

                background: Rectangle {
                    color: "white"
                    radius: 3
                }
            }

            EraButton {
                Layout.alignment: Qt.AlignRight
                Layout.minimumWidth: 120
                Layout.minimumHeight: 40

                text: qsTr("Save")
            }

            Separator {
                Layout.fillWidth: true
            }

            SettingsGroup {
                Layout.fillWidth: true
                Layout.minimumHeight: 100

                title: qsTr("MultiConnection")
                description: qsTr("MultiConnectionDescription")
            }
            */
        }
    }
}
