import QtQuick 2.13
import QtQuick.Controls 2.13

TextField {
    property bool large: false

    height: 44

    selectByMouse: true

    font.family: rootUiFontRegular.name
    font.pointSize: large ? 12 : 10

    color: "white"
    selectedTextColor: "white"
    selectionColor: "#1463f6"

    background: Rectangle {
        radius: 3

        color: "transparent"

        border.width: 1
        border.color: "#a4acca"
    }
}
