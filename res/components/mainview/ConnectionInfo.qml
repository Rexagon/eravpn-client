import QtQuick 2.13
import QtQuick.Layouts 1.13

import "../era"

ColumnLayout {
    readonly property string lightBlueColor: "#00c5f0"
    readonly property string darkBlueColor: "#0062f7"

    spacing: 0

    Text {
        Layout.fillWidth: true

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        text: "Подключено"
        color: lightBlueColor
        font.family: futuraMediumFont.name
        font.pointSize: 16
    }

    Text {
        Layout.fillWidth: true

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        text: "00:15:34"
        color: "white"
        font.family: rootUiFontRegular.name
        font.pointSize: 12
    }

    Text {
        Layout.fillWidth: true

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        text: "Местоположение"
        color: darkBlueColor
        font.family: futuraMediumFont.name
        font.pointSize: 12
    }

    Text {
        Layout.fillWidth: true

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        text: "Исландия"
        color: "white"
        font.family: futuraMediumFont.name
        font.pointSize: 16
    }
}
