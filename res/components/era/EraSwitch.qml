import QtQuick 2.13
import QtQuick.Controls 2.13

Switch {
    id: control

    width: 58
    height: 24
    checkable: true
    checked: false

    state: checked ? "checked" : ""

    states: [
        State {
            name: "checked"
            PropertyChanges {
                target: label
                text: qsTr("On")
                horizontalAlignment: Text.AlignLeft
            }
            PropertyChanges {
                target: indicator
                x: 58 - 14 - 5
            }
            PropertyChanges {
                target: backgroundRectangle
                color: "#8dc41b"
            }
        }
    ]

    transitions: Transition {
        NumberAnimation {
            properties: "x";
            duration: 100
            easing.type: Easing.InOutQuad
        }
        ColorAnimation {
            duration: 100
        }
    }

    contentItem: Text {
        id: label

        anchors.fill: parent
        anchors.leftMargin: 9
        anchors.rightMargin: 9
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight

        text: qsTr("Off")

        color: "white"
        font.family: futuraHeavyFont.name
        font.pointSize: 7
    }

    indicator: Rectangle {
        id: indicator

        anchors.verticalCenter: parent.verticalCenter
        x: 5

        width: 14
        height: 14
        radius: width / 2
        color: "white"
    }

    background: Rectangle {
        id: backgroundRectangle

        implicitWidth: parent.width
        implicitHeight: parent.height
        radius: implicitHeight / 2
        visible: true
        color: "#081640"
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onPressed: mouse.accepted = false
    }
}
