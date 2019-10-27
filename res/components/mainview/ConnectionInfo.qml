import QtQuick 2.13
import QtQuick.Layouts 1.13

import com.eravpn.backend 1.0

import "../era"

ColumnLayout {
    id: connectionInfo

    readonly property string blueColor: "#00c5f0"
    readonly property string redColor: "#ff4747"
    readonly property string darkBlueColor: "#0062f7"

    spacing: 0

    property bool connected: {
        return BackEnd.vpnConnection.connected
    }

    Text {
        Layout.fillWidth: true

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        text: connectionInfo.connected ? "Подключено" : "Не подключено"
        color: connectionInfo.connected ? blueColor : redColor
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
