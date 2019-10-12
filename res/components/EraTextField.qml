import QtQuick 2.13
import QtQuick.Controls 2.13

TextField {
    height: 44

    font.family: rootUiFontRegular.name
    font.pointSize: 12

    color: "white"

    background: Rectangle {
        radius: 3

        color: "transparent"

        border.width: 1
        border.color: "#a4acca"
    }
}
