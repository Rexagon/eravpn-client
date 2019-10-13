import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

Rectangle {
    readonly property string mainColor: "#081640"
    readonly property string closeButtonHoverColor: "#040A1F"
    readonly property string minimizeButtonHoverColor: "#040A1F"

    signal titleBarPressed(int x, int y)
    signal titleBarMoved(int x, int y)

    signal closeRequested
    signal minimizeRequested

    id: windowTitleBar

    height: 40

    color: mainColor

    z: 100

    RowLayout {
        anchors.fill: parent

        spacing: 1

        Rectangle {
            id: profileButton

            Layout.minimumWidth: 50
            Layout.fillHeight: true

            color: mainColor

            Image {
                source: "../images/icon_profile.png"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                hoverEnabled: true

                onEntered: profileButton.color = minimizeButtonHoverColor
                onExited: profileButton.color = mainColor
                //onClicked: windowTitleBar.minimizeRequested()
            }
        }

        Rectangle {
            id: settingsButton

            Layout.minimumWidth: 50
            Layout.fillHeight: true

            color: mainColor

            Image {
                source: "../images/icon_settings.png"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                hoverEnabled: true

                onEntered: settingsButton.color = minimizeButtonHoverColor
                onExited: settingsButton.color = mainColor
                //onClicked: windowTitleBar.minimizeRequested()
            }
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            MouseArea {
                anchors.fill: parent

                hoverEnabled: false

                onPressed: windowTitleBar.titleBarPressed(mouseX, mouseY)
                onPositionChanged: windowTitleBar.titleBarMoved(mouseX, mouseY)
            }
        }

        Rectangle {
            id: minimizeButton

            Layout.minimumWidth: 50
            Layout.fillHeight: true

            color: mainColor

            Image {
                source: "../images/icon_minimize.png"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                hoverEnabled: true

                onEntered: minimizeButton.color = minimizeButtonHoverColor
                onExited: minimizeButton.color = mainColor
                onClicked: windowTitleBar.minimizeRequested()
            }
        }

        Rectangle {
            id: closeButton

            Layout.minimumWidth: 50
            Layout.fillHeight: true

            color: mainColor

            Image {
                source: "../images/icon_close.png"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                hoverEnabled: true

                onEntered: closeButton.color = closeButtonHoverColor
                onExited: closeButton.color = mainColor
                onClicked: windowTitleBar.closeRequested()
            }
        }
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        text: windowTitleText

        color: "white"

        font.family: futuraMediumFont.name
        font.pointSize: 12
    }
}
