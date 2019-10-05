import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtGraphicalEffects 1.13

ApplicationWindow
{
    id: window
    visible: true
    width: 900
    height: 640

    flags: Qt.Window | Qt.FramelessWindowHint

    property int previousMouseXPosition
    property int previousMouseYPosition

    LinearGradient {
        anchors.fill: parent
        start: Qt.point(0, 0)
        end: Qt.point(0, parent.height)
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#16295e" }
            GradientStop { position: 1.0; color: "#0f1444" }
        }
    }

    Rectangle {
        id: windowTitleBar
        height: 40

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        color: "#081640"

        MouseArea {
            id: appMovigArea

            anchors.fill: windowTitleBar
            hoverEnabled: false
            onPressed: {
                previousMouseXPosition = mouseX;
                previousMouseYPosition = mouseY;
            }

            onPositionChanged: {
                if(window.visibility === ApplicationWindow.Maximized) {
                    showNormal();
                } else {
                    window.setX(window.x + (mouseX - previousMouseXPosition));
                    window.setY(window.y + (mouseY - previousMouseYPosition));
                }
            }
        }
    }
}
