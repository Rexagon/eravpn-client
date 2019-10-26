import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import com.eravpn.backend 1.0

import "../components"
import "../components/era"
import "../components/mainview"

Item {
    id: view

    function updateTitle() {
        windowTitleText = "EraVPN"
    }

    Component.onCompleted: {
        windowTitleButtonsVisible = true

        BackEnd.locationController.updateCurrentLocation();

        BackEnd.countriesController.refreshCountries(false);
        BackEnd.countriesController.refreshCountries(true);
    }

    Timer {
        id: locationRefreshTimer
        interval: 10000; running: false; repeat: false
        onTriggered: BackEnd.locationController.updateCurrentLocation()
    }

    Connections {
        target: BackEnd.countriesController

        onCountriesRequestError: {
            notificationArea.notify("Countries request error. IsPremium: ", isPremium);
        }
    }

    Connections {
        target: BackEnd.vpnConnection

        onConnectedChanged: {
            locationRefreshTimer.start()
        }
    }

    RowLayout {
        anchors.fill: parent

        MainSideBar {
            Layout.minimumWidth: 340
            Layout.fillHeight: true
        }

        ColumnLayout {
            Item {
                Layout.fillWidth: true
                Layout.minimumHeight: 160

                PowerButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Item {
                Layout.fillWidth: true
                Layout.minimumHeight: 100

                ConnectionInfo {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                }
            }

            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true

                BackgroundMap {
                    anchors.fill: parent
                    anchors.leftMargin: 30
                    anchors.rightMargin: 30
                }
            }

            Item {
                Layout.fillWidth: true
                Layout.minimumHeight: 30

                EraLabel {
                    anchors.fill: parent
                    anchors.leftMargin: 10

                    text: "3651 человек онлайн на 350 серверах"
                }
            }
        }
    }
}
