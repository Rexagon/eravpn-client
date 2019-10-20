import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

Rectangle {
    readonly property string darkRedColor: "#ee252e"

    property int uniqueId

    property alias title: titleLabel.text
    property alias duration: animationPause.duration

    signal destroyRequested

    id: notification

    radius: 3
    width: 300
    height: 40

    color: darkRedColor

    Text {
        anchors.fill: parent
        anchors.margins: 10

        verticalAlignment: Text.AlignVCenter

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
