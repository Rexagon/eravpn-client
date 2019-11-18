import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import com.eravpn.backend 1.0

import "../era"

Popup {
    property string countryId: ""
    property bool startOnSelect: false

    readonly property bool isLoading: {
        return BackEnd.certificateListModel.isLoading ||
                BackEnd.certificateListModel.isGenerating;
    }

    id: popup

    x: Math.round((parent.width - width) / 2)
    y: Math.round((parent.height - height) / 2)

    width: 500
    height: 400

    modal: true
    focus: true
    closePolicy: isLoading ? 0 : Popup.CloseOnEscape | Popup.CloseOnPressOutside

    Overlay.modal: Rectangle {
        color: "#55000000"
    }

    contentItem: Item {
        state: BackEnd.certificateListModel.certificateCount < 1 ? "initial" : ""

        states: [
            State {
                name: "initial"
                PropertyChanges {
                    target: certificateGenerationButtonGroup
                    anchors.bottomMargin: popup.height / 2 - 75
                }
            }
        ]

        Connections {
            target: BackEnd.certificateController

            onCertificateCreationError: {
                if (BackEnd.profile.status === Profile.New) {
                    notificationArea.notify(qsTr("UserIsNotVerified"))
                } else {
                    notificationArea.notify(qsTr("CertificateCreationError"))
                }
            }
        }

        Text {
            id: titleLabel

            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            height: 30

            text: qsTr("ConfigurationFiles")

            color: "white"
            font.pointSize: 12
            font.family: futuraMediumFont.name

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        CertificateListView {
            id: certificateListView

            anchors.top: titleLabel.bottom
            anchors.bottom: elapsedCertificatesLabel.top
            anchors.left: parent.left
            anchors.right: parent.right

            visible: !isLoading

            anchors.margins: 10

            model: BackEnd.certificateListModel

            onCertificateSelected: {
                BackEnd.certificateController.setDefault(popup.countryId, certificateId);
                popup.close();

                if (!BackEnd.vpnConnection.running && popup.startOnSelect) {
                    BackEnd.vpnController.start(countryId);
                }
            }
        }

        Item {
            id: loadingStub

            anchors.top: titleLabel.bottom
            anchors.bottom: elapsedCertificatesLabel.top
            anchors.left: parent.left
            anchors.right: parent.right

            visible: isLoading

            Image {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

                width: 30
                height: 30

                source: "../../images/loading.svg"

                RotationAnimation on rotation {
                    loops: Animation.Infinite
                    duration: 1000
                    from: 0
                    to: 360
                }
            }
        }

        Item {
            id: certificateGenerationButtonGroup

            anchors.bottom: elapsedCertificatesLabel.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 60

            visible: !isLoading && BackEnd.certificateListModel.certificateCount < 5

            EraButton {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.topMargin: 10
                anchors.bottomMargin: 10

                width: 120

                text: qsTr("Generate")

                onClicked: {
                    BackEnd.certificateController.createNew(countryId);
                }
            }
        }

        Text {
            id: elapsedCertificatesLabel

            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            height: 30

            visible: !isLoading

            text: BackEnd.certificateListModel.certificateCount + " / 5"

            color: "white"
            font.pointSize: 10
            font.family: futuraMediumFont.name

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    background: Rectangle {
        anchors.fill: parent
        color: "#173878"
    }
}
