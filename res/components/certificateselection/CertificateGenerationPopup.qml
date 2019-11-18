import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import com.eravpn.backend 1.0

import "../era"

Popup {
    property string countryId: ""
    property bool connectAfterGeneration: false

    readonly property bool isGenerating: {
        return BackEnd.certificateListModel.isGenerating;
    }

    id: popup

    x: Math.round((parent.width - width) / 2)
    y: Math.round((parent.height - height) / 2)

    width: 500
    height: 200

    modal: true
    focus: true
    closePolicy: isGenerating ? 0 : Popup.CloseOnEscape | Popup.CloseOnPressOutside

    contentItem: Item {
        Connections {
            target: BackEnd.certificateListModel

            onIsGeneratingChanged: {
                if (BackEnd.certificateListModel.isGenerating === false) {
                    if (popup.connectAfterGeneration) {
                        BackEnd.vpnController.start(countryId);
                        popup.connectAfterGeneration = false;
                    }

                    popup.close();
                }
            }
        }

        Text {
            id: titleLabel

            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            height: 30

            text: qsTr("CertificateGeneration")

            color: "white"
            font.pointSize: 12
            font.family: futuraMediumFont.name

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Item {
            id: loadingStub

            anchors.fill: parent

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
    }

    background: Rectangle {
        anchors.fill: parent
        color: "#173878"
    }
}
