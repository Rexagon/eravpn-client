import QtQuick 2.13
import QtQuick.Controls 2.13

Text {
    readonly property FontLoader rootUiFontRegular: FontLoader { source: "../fonts/PT Root UI_Regular.ttf" }

    signal clicked

    id: link

    font.family: rootUiFontRegular.name
    font.pointSize: 12

    color: "#a4acca"

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor

        onEntered: link.font.underline = true
        onExited: link.font.underline = false
        onClicked: parent.clicked()
    }
}
