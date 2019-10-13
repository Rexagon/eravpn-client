import QtQuick 2.13
import QtQuick.Layouts 1.13

Rectangle {
    property string iconSource
    property string hoveredColor: darkColor

    property bool activated: false

    signal clicked

    id: component

    Layout.minimumWidth: 50
    Layout.fillHeight: true

    color: mainColor

    onActivatedChanged: state = activated ? "activated" : ""

    states: [
        State {
            name: "hovered"
            PropertyChanges {
                target: component
                color: hoveredColor
            }
        },
        State {
            name: "activated"
            PropertyChanges {
                target: component
                color: hoveredColor
            }
        }
    ]

    Image {
        source: iconSource
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        hoverEnabled: true

        onEntered: {
            if (!component.activated) {
                component.state = "hovered";
            }
        }

        onExited: {
            if (!component.activated) {
                component.state = "";
            }
        }

        onClicked: {
            if (!component.activated) {
                component.clicked()
            }
        }
    }
}
