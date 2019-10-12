import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import "../components"

Item {
    id: view

    Component.onCompleted: windowTitleText = "EraVPN"

    RowLayout {
        anchors.fill: parent

        MainSideBar {
            Layout.minimumWidth: 340
            Layout.fillHeight: true
        }
    }
}
