import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import com.eravpn.backend 1.0

import "../components"
import "../components/era"

Item {
    property string authKey: ""

    signal switchToMain

    id: view

    function copyAuthKey() {
        BackEnd.clipboardController.copyToClipboard(view.authKey);
        notificationArea.notify(qsTr("AuthKeyCopied"), true);
    }

    StackView.onActivating: {
        windowTitleText = qsTr("AuthKey", "as title")
        windowTitleButtonsVisible = false
    }

    BackgroundMap {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

    Item {
        width: 285
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        ColumnLayout {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right

            spacing: 10

            EraLabel {
                Layout.fillWidth: true

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WordWrap

                text: qsTr("AuthKey") + ":"
                color: "white"

                font.pointSize: 16
                font.family: futuraMediumFont.name
            }

            EraLabel {
                property bool tooltipVisible: false

                text: authKey

                Layout.fillWidth: true
                Layout.minimumHeight: 100

                wrapMode: Text.WrapAnywhere

                ToolTip.visible: tooltipVisible
                ToolTip.text: qsTr("PressToCopy")

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    hoverEnabled: true

                    onClicked: {
                        view.copyAuthKey();
                    }

                    onEntered: {
                        parent.font.underline = true;
                        parent.tooltipVisible = true;
                    }

                    onExited: {
                        parent.font.underline = false;
                        parent.tooltipVisible = false;
                    }
                }
            }

            EraLabel {
                Layout.fillWidth: true

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WordWrap

                text: qsTr("SaveThisCode")
                color: "white"

                font.pointSize: 16
                font.family: futuraMediumFont.name
            }

            EraLabel {
                Layout.fillWidth: true

                text: qsTr("SaveThisCodeDescription")

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WordWrap
            }

            Item {
                Layout.minimumHeight: 10
            }

            EraButton {
                id: confirmButton

                text: qsTr("Done")

                onClicked: switchToMain()

                Layout.fillWidth: true
                Layout.minimumHeight: 44

                large: true
            }
        }
    }
}
