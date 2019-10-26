import QtQuick 2.13
import QtQuick.Layouts 1.13

import com.eravpn.backend 1.0

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

        text: "Местоположение"
        color: darkBlueColor
        font.family: futuraMediumFont.name
        font.pointSize: 12
    }

    Text {
        Layout.fillWidth: true

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        text: BackEnd.location.countryName
        color: "white"
        font.family: futuraMediumFont.name
        font.pointSize: 16
    }
}
