import QtQuick 2.13
import QtQuick.Controls 2.13

Button {
    readonly property FontLoader rootUiFontMedium: FontLoader { source: "../fonts/PT Root UI_Medium.ttf" }

    readonly property string lightColor: "#23a2f8"
    readonly property string darkColor: "#1463f6"

    id: control

    height: 44

    contentItem: Text {
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
            orientation: Gradient.Horizontal
            GradientStop { id: buttonGradientLeft; position: 0.0; color: lightColor }
            GradientStop { id: buttonGradientRight; position: 1.0; color: darkColor }
        }
    }

    states: [
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

    onPressed: control.state = "pressed"
    onReleased: control.state = hovered ? "hovered" : ""
    onHoveredChanged: {
        if (control.pressed) {
            return;
        }
        control.state = hovered ? "hovered" : ""
    }
    onFocusChanged: {
        controlBackground.border.width = focus ? 1 : 0;
    }
}
