import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import com.eravpn.backend 1.0

import "../era"

Rectangle {
    id: connectionInfo

    readonly property string alertIcon: "../../images/icon_alert.png"
    readonly property string houseIcon: "../../images/icon_house.png"

    property bool connected: {
        return BackEnd.vpnConnection.connected
    }

    function formatSpeed(bytesPerSecond) {
        if (bytesPerSecond < (1 << 10)) {
            return bytesPerSecond + " B/s";
        }

        if (bytesPerSecond < (1 << 20)) {
            return (bytesPerSecond / (1 << 10)).toFixed(2) + " KB/s";
        }

        return (bytesPerSecond / (1 << 20)).toFixed(2) + " MB/s";
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 25

        RowLayout {
            Layout.alignment: Qt.AlignVCenter

            Image {
                source: connectionInfo.connected ? houseIcon : alertIcon
            }

            EraLabel {
                text: connectionInfo.connected ? qsTr("ConnectionIsSecure") : qsTr("ConnectionIsNotSecure")
                font.family: futuraMediumFont.name
                color: connectionInfo.connected ? blueColor : redColor
            }
        }

        EraLabel {
            Layout.alignment: Qt.AlignVCenter

            text: qsTr("YourIp") + ": " + BackEnd.location.ip
            color: "white"
        }

        EraLabel {
            Layout.alignment: Qt.AlignVCenter

            text: qsTr("Location") + ": " + BackEnd.location.regionName
            color: "white"
        }

        Item {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
            Layout.minimumHeight: 16

            visible: connectionInfo.connected

            RowLayout {
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.horizontalCenter

                Image {
                    Layout.alignment: Qt.AlignLeft
                    source: "../../images/icon_download.png"
                }

                EraLabel {
                    text: formatSpeed(BackEnd.vpnConnection.bytesInDelta)
                    color: "white"
                }
            }

            RowLayout {
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.horizontalCenter
                anchors.right: parent.right

                Image {
                    Layout.alignment: Qt.AlignLeft
                    source: "../../images/icon_upload.png"
                }

                EraLabel {
                    text: formatSpeed(BackEnd.vpnConnection.bytesOutDelta)
                    color: "white"
                }
            }
        }
    }
}
