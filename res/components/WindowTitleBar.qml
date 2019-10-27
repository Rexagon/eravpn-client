import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import "titlebar"

Rectangle {
    readonly property string mainColor: "#081640"
    readonly property string darkColor: "#040a1f"

    signal titleBarPressed(int x, int y)
    signal titleBarMoved(int x, int y)

    signal openProfile
    signal openSettings
    signal backToMain

    signal closeRequested
    signal minimizeRequested

    id: component

    height: 40

    color: mainColor

    z: 100

    states: [
        State {
            name: "profile_opened"
            PropertyChanges {
                target: profileButton
                activated: true
            }
        },
        State {
            name: "settings_opened"
            PropertyChanges {
                target: settingsButton
                activated: true
            }
        }
    ]

    RowLayout {
        anchors.fill: parent

        spacing: 1

        TitleBarButton {
            id: profileButton

            visible: windowTitleButtonsVisible

            iconSource: "../../images/icon_profile.png"
            onClicked: {
                if (component.state === "profile_opened") {
                    component.backToMain();
                } else {
                    component.state = "profile_opened";
                    component.openProfile();
                }
            }
        }

        TitleBarButton {
            id: settingsButton

            visible: windowTitleButtonsVisible

            iconSource: "../../images/icon_settings.png"
            onClicked: {
                if (component.state === "settings_opened") {
                    component.backToMain();
                } else {
                    component.state = "settings_opened";
                    component.openSettings();
                }
            }
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            MouseArea {
                anchors.fill: parent

                hoverEnabled: false

                onPressed: component.titleBarPressed(mouseX, mouseY)
                onPositionChanged: component.titleBarMoved(mouseX, mouseY)
            }
        }

        TitleBarButton  {
            id: minimizeButton

            iconSource: "../../images/icon_minimize.png"
            onClicked: component.minimizeRequested()
        }

        TitleBarButton {
            id: closeButton

            iconSource: "../../images/icon_close.png"
            onClicked: component.closeRequested()
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
