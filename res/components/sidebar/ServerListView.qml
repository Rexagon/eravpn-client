import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import com.eravpn.backend 1.0

import "../era"

ListView {
    id: view

    clip: true

    delegate: Item {
        height: 60
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 15
        anchors.rightMargin: 15

        Image {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 8

            width: 31
            height: 31

            source: "../../images/flags/" + countryCode + ".png"
        }

        ColumnLayout {
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -5
            anchors.left: parent.left
            anchors.leftMargin: 50
            height: 30

            spacing: 0

            EraLabel {
                text: "Расположение сервера"
                font.pointSize: 8
            }

            EraLabel {
                text: countryTitle
                font.family: futuraMediumFont.name
                color: "white"
            }
        }

        ServerActivationButton {
            id: serverActivationButton

            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.margins: 10

            width: 100

            onClicked: {
                activated = !activated;
            }

            onActivatedChanged: {
                if (activated) {
                    BackEnd.vpnController.enableVpn(countryId);
                } else {
                    BackEnd.vpnConnection.disconnect();
                }
            }
        }

        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            height: 1

            visible: index + 1 < view.model.rowCount()

            color: lightBackgroundColor
        }
    }

    ScrollBar.vertical: ScrollBar {
        id: scrollBar

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
}
