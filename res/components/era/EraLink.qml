import QtQuick 2.13
import QtQuick.Controls 2.13

EraLabel {
    signal clicked

    id: link

    color: "#2fa4ff"

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor

        onEntered: link.font.underline = true
        onExited: link.font.underline = false
        onClicked: parent.clicked()
    }
}
