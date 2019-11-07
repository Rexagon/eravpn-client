import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import com.eravpn.backend 1.0

import "../era"

ListView {
    readonly property string lightBackgroundColor: "#4f6699"

    signal certificateSelected(string certificateId)

    id: view

    interactive: false

    delegate: Item {
        id: button

        height: 60
        anchors.left: parent.left
        anchors.right: parent.right

        RowLayout {
            anchors.fill: parent
            anchors.topMargin: 10
            anchors.bottomMargin: 10

            Text {
                width: 130
                Layout.fillHeight: true


                text: Qt.formatDateTime(certificateCreatedAt, "dd.MM.yyyy hh:mm")

                color: "white"
                font.pointSize: 10
                font.family: rootUiFontRegular.name

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                Layout.fillWidth: true
                Layout.fillHeight: true

                text: certificateComment

                color: "white"
                font.pointSize: 10
                font.family: rootUiFontRegular.name

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            EraButton {
                implicitWidth: 100
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignRight

                text: qsTr("Select")

                onClicked: {
                    certificateSelected(certificateId);
                }
            }
        }

        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            height: 1

            visible: index + 1 < view.model.rowCount()

            color: lightBackgroundColor
        }
    }
}
