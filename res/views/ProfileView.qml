import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import "../components"
import "../components/era"

Item {
    signal closeView

    id: view

    StackView.onActivating: {
        windowTitleText = "Профиль"
        windowTitleButtonsVisible = true
    }

    MouseArea {
        anchors.fill: parent
        onPressed: closeView()
    }
}
