import QtQuick 2.13
import QtQuick.Controls 2.13

Button {
    readonly property string lightBlueColor: "#23a2f8"
    readonly property string darkBlueColor: "#1463f6"

    readonly property string lightRedColor: "#ee3840"
    readonly property string darkRedColor: "#ee252e"

    property string lightColor: lightBlueColor
    property string darkColor: darkBlueColor

    property bool activated: false

    id: control

    contentItem: Text {
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        text: activated ? "Отключиться" : "Подключиться"

        color: "white"
        font.family: futuraMediumFont.name
        font.pointSize: 10
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

        if (enabled) {
            state = "pressed"
        }
    }

    onReleased: {
        if (!enabled) {
            state = "disabled";
            return;
        }

        state = hovered ? "hovered" : ""
    }

    onHoveredChanged: {
        if (!enabled) {
            state = "disabled";
            return;
        }

        if (pressed) {
            return;
        }

        state = hovered ? "hovered" : ""
    }

    onFocusChanged: {
        controlBackground.border.width = focus ? 1 : 0;
    }

    onEnabledChanged: {
        state = enabled ? (pressed ? "pressed" : (hovered ? "hovered" : "")) : "disabled"
    }

    onActivatedChanged: {
        lightColor = activated ? lightRedColor : lightBlueColor;
        darkColor = activated ? darkRedColor : darkBlueColor;
        focus = false;
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onPressed: mouse.accepted = false
    }
}

