import QtQuick 2.13
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.13

import com.eravpn.backend 1.0

Item {
    readonly property string inactiveSecondaryColor: "#173878"
    readonly property string inactivePrimaryColor: "#24488c"

    readonly property string activeSecondaryColor: "#0162f6"
    readonly property string activePrimaryColor: "#00ddf6"

    property bool activated: false

    id: component

    width: 140
    height: width

    state: BackEnd.vpnConnection.connected ? "active" : ""

    Rectangle {
        id: componentShadow

        anchors.fill: parent
        radius: width * 2

        opacity: 0

        layer.enabled: true
        layer.effect: DropShadow {
            //cached: true
            color: "#3786ff"
            radius: 30
            samples: 17
            transparentBorder: true
        }
    }

    Rectangle {
        id: outerCircle

        anchors.fill: parent
        radius: width * 2

        color: inactiveSecondaryColor
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
                target: componentShadow
                opacity: 0.58
            }
            PropertyChanges {
                target: outerCircle
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

    transitions: Transition {
        ColorAnimation { duration: 1000 }
        NumberAnimation { properties: "opacity"; duration: 1000 }
    }

    onActivatedChanged: state = activated ? "activated" : ""
}
