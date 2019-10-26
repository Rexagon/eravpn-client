import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import com.eravpn.backend 1.0

import "../era"

Rectangle {
    ColumnLayout {
        anchors.fill: parent
        anchors.leftMargin: 40
        anchors.topMargin: 35
        anchors.bottomMargin: 35

        RowLayout {
            Image {
                source: "../../images/icon_alert.png"
            }

            EraLabel {
                text: "Соединение не защищено"
                color: redColor
            }
        }

        EraLabel {
            text: "Ваш IP: " + BackEnd.location.ip
            color: "white"
        }

        EraLabel {
            text: "Местоположение: " + BackEnd.location.regionName
            color: "white"
        }
    }
}
