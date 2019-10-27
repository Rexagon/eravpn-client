import QtQuick 2.13
import QtQuick.Controls 2.13

Button {
    readonly property string lightColor: "#23a2f8"
    readonly property string darkColor: "#1463f6"

    id: control

    height: 44

    contentItem: Text {
        id: contentText

        text: control.text
        font.family: rootUiFontMedium.name
        font.pointSize: 12
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "white"
    }

    background: Rectangle {
        id: controlBackground

        radius: 3

        border.width: 0
        border.color: darkColor

        gradient: Gradient {
            id: controlBackgroundGradient

            orientation: Gradient.Horizontal
            GradientStop { id: buttonGradientLeft; position: 0.0; color: lightColor }
            GradientStop { id: buttonGradientRight; position: 1.0; color: darkColor }
        }
    }

    states: [
        State {
            name: "disabled"

            PropertyChanges {
                target: controlBackground
                border.width: 1
                border.color: "#485083"
            }
            PropertyChanges {
                target: buttonGradientLeft
                color: "transparent"
            }
            PropertyChanges {
                target: buttonGradientRight
                color: "transparent"
            }
        },
        State {
            name: "hovered"
            PropertyChanges {
                target: buttonGradientLeft
                color: lightColor
            }
            PropertyChanges {
                target: buttonGradientRight
                color: lightColor
            }
        },
        State {
            name: "pressed"
            PropertyChanges {
                target: buttonGradientLeft
                color: darkColor
            }
            PropertyChanges {
                target: buttonGradientRight
                color: darkColor
            }
        }
    ]

    transitions: Transition {
        ColorAnimation {
            properties: "color"
            easing.type: Easing.InOutQuad
            duration: 100
        }
    }

    onPressed: {
        if (!enabled) {
            state = "disabled";
            return;
        }

        state = "pressed";
    }

    onReleased: {
        if (!enabled) {
            state = "disabled";
            return;
        }

        state = hovered ? "hovered" : "";
    }

    onHoveredChanged: {
        if (!enabled) {
            state = "disabled";
            return;
        }

        if (pressed) {
            state = "pressed";
            return;
        }

        state = hovered ? "hovered" : ""
    }

    onFocusChanged: {
        controlBackground.border.width = focus ? 1 : 0;
    }

    onEnabledChanged: {
        state = enabled ? "" : "disabled"
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onPressed: mouse.accepted = false
    }
}
