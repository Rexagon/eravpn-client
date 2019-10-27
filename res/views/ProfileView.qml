import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import com.eravpn.backend 1.0

import "../components"
import "../components/era"

Item {
    readonly property string lightBackgroundColor: "#4f6699"
    readonly property string darkBackgroundColor: "#0f1444"

    signal closeView

    id: view

    StackView.onActivating: {
        windowTitleText = "Профиль"
        windowTitleButtonsVisible = true
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Escape) {
            view.closeView();
        }
    }

    ScrollView {
        anchors.fill: parent
        anchors.topMargin: 16
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

            EraBackButton {
                Layout.alignment: Qt.AlignLeft

                onClicked: view.closeView()
            }

            Text {
                text: "Профиль"

                color: "white"

                font.family: futuraHeavyFont.name
                font.pointSize: 20
            }

            Item {
                implicitHeight: 20
            }

            EraButton {
                Layout.minimumWidth: 120
                Layout.minimumHeight: 40

                text: "Выход"

                onClicked: {
                    view.closeView();
                    BackEnd.profileController.signOut();
                }
            }
        }
    }
}
