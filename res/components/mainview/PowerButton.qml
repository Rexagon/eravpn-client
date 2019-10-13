import QtQuick 2.13
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.13

Rectangle {
    readonly property string inactiveSecondaryColor: "#173878"
    readonly property string inactivePrimaryColor: "#24488c"

    readonly property string activeSecondaryColor: "#0162f6"
    readonly property string activePrimaryColor: "#00ddf6"

    property bool activated: false

    id: component

    width: 140
    height: width
    radius: width * 2

    color: inactiveSecondaryColor

    state: "active"

    layer.enabled: true
    layer.effect: DropShadow {
        //cached: true
        color: "#3786ff"
        opacity: 0.58
        radius: 30
        samples: 17
        transparentBorder: true
    }

    Rectangle {
        id: innerCircle

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        width: 64
        height: width
        radius: width * 2

        color: inactivePrimaryColor

        Image {
            id: innerCircleImage

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            source: "../../images/icon_power_on.png"
        }
    }

    states: [
        State {
            name: "active"
            PropertyChanges {
                target: component
                color: activeSecondaryColor
            }
            PropertyChanges {
                target: innerCircle
                color: activePrimaryColor
            }
            PropertyChanges {
                target: innerCircleImage
                source: "../../images/icon_power_off.png"
            }
        }
    ]

    onActivatedChanged: state = activated ? "activated" : ""
}
