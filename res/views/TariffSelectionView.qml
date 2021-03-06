import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import com.eravpn.backend 1.0

import "../components"
import "../components/era"
import "../components/tariffselection"

Item {
    signal closeView

    id: view

    StackView.onActivating: {
        windowTitleText = qsTr("TariffSelection")
        windowTitleButtonsVisible = true
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Escape) {
            view.closeView();
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.topMargin: 16
        anchors.bottomMargin: 16
        anchors.leftMargin: 56
        anchors.rightMargin: 56

        EraBackButton {
            Layout.alignment: Qt.AlignLeft

            onClicked: view.closeView()
        }

        Text {
            text: qsTr("TariffSelection")

            color: "white"

            font.family: futuraHeavyFont.name
            font.pointSize: 20
        }

        Item {
            implicitHeight: 40
        }

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            orientation: ListView.Horizontal

            model: BackEnd.tariffListModel

            spacing: ((window.width - 56 * 2) - 250 * 3) / 2

            delegate: TariffComponent {
                title: tariffTitle
                price: tariffPrice
                profitInPercent: tariffProfitInPercent
                monthCount: tariffMonthCount

                onPressed: {
                    BackEnd.tariffController.buy(tariffId);
                    view.closeView();
                }
            }
        }

        Item {
            Layout.fillWidth: true
            implicitHeight: 60

            Image {
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                height: 45

                source: "../images/payment.png"
                fillMode: Image.PreserveAspectFit
            }
        }
    }
}
