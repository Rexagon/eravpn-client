import QtQuick 2.13
import QtQuick.Controls 2.13

TextField {
    property bool large: false

    height: 44

    font.family: rootUiFontRegular.name
    font.pointSize: large ? 12 : 10

    color: "white"

    background: Rectangle {
        radius: 3

        color: "transparent"

        border.width: 1
        border.color: "#a4acca"
    }
}
