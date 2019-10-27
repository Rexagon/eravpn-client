import QtQuick 2.13
import QtQuick.Controls 2.13

Item {
    signal clicked

    id: component

    width: 70
    height: 24

    Image {
        id: arrow

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: -6

        source: "../../images/icon_arrow_left.png"
    }

    Text {
        id: label

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: arrow.right

        text: "Назад"

        font.family: rootUiFontRegular.name
        font.pointSize: 12

        color: "#0063fa"
    }

    MouseArea {
        anchors.fill: parent

        cursorShape: Qt.PointingHandCursor
        hoverEnabled: true

        onClicked: component.clicked()

        onEntered: label.font.underline = true
        onExited: label.font.underline = false
    }
}
