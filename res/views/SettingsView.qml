import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import "../components"
import "../components/era"

Item {
    signal closeView

    id: view

    Component.onCompleted: windowTitleText = "Настройки"

    MouseArea {
        anchors.fill: parent
        onPressed: closeView()
    }
}
