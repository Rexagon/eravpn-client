import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

Item {
    readonly property string darkRedColor: "#ee252e"
    readonly property string greenColor: "#0ed079"

    property int uniqueId

    property alias title: titleLabel.text
    property alias duration: animationPause.duration
    property bool success: false

    signal destroyRequested

    id: notification

    height: 40

    Rectangle {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        radius: 3

        color: success ? greenColor : darkRedColor

        width: titleLabel.width + 20

        Text {
            verticalAlignment: Text.AlignVCenter
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            id: titleLabel

            color: "white"

            font.family: rootUiFontRegular.name
            font.pointSize: 12
        }

        MouseArea {
            hoverEnabled: true
            anchors.fill: parent

            cursorShape: Qt.PointingHandCursor

            onEntered: {
                animation.stop();
                notification.opacity = 100;
            }

            onExited: {
                animation.start();
            }
        }

        SequentialAnimation {
            id: animation

            running: true

            PauseAnimation {
                id: animationPause
                duration: 1000
            }

            NumberAnimation {
                target: notification
                property: "opacity"

                to: 0
                duration: 500
            }

            onFinished: destroyRequested()
        }
    }
}
