import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import com.eravpn.backend 1.0

import "../components"
import "../components/era"
import "../components/mainview"
import "../components/certificateselection"

Item {
    id: view

    signal switchToTariffSelection

    function showCertificateSelectionPopup(countryId, startOnSelect) {
        BackEnd.certificateController.refreshCertificates(countryId);
        certificateSelectionPopup.countryId = countryId;
        certificateSelectionPopup.startOnSelect = startOnSelect;
        certificateSelectionPopup.open();
    }

    Component.onCompleted: {
        BackEnd.applicationController.refreshSettings();

        BackEnd.locationController.updateCurrentLocation();

        BackEnd.tariffController.refreshTariffs();

        BackEnd.referralClientsController.refreshReferralClients();

        BackEnd.countriesController.refreshCountries(false);
        BackEnd.countriesController.refreshCountries(true);
    }

    StackView.onActivating: {
        windowTitleText = qsTr("Title")
        windowTitleButtonsVisible = true

        profileRefreshTimer.start();
    }

    Component.onDestruction: {
        profileRefreshTimer.stop();
        BackEnd.vpnController.stop();
    }

    Timer {
        id: locationRefreshTimer
        interval: 500; running: false; repeat: false
        onTriggered: BackEnd.locationController.updateCurrentLocation()
    }

    Timer {
        id: profileRefreshTimer
        interval: 60000
        running: false
        repeat: true
        onTriggered: {
            if (BackEnd.profile.isTariffPurchased) {
                stop();
            }

            BackEnd.profileController.refreshProfile();
        }
    }

    Connections {
        target: BackEnd.countriesController

        onCountriesRequestError: {
            notificationArea.notify(qsTr("CountriesRequestError"));
        }
    }

    Connections {
        target: BackEnd.vpnController

        onCertificateNotFound: {
            if (BackEnd.applicationSettings.isCertificateAutoGenerationEnabled && certificateCount < 5) {
                BackEnd.certificateController.createNew(countryId);
            }

            showCertificateSelectionPopup(countryId, true);
        }
    }

    Connections {
        target: BackEnd.vpnConnection

        onConnectedChanged: {
            locationRefreshTimer.start()
        }

        onRuntimeErrorOccurred: {
            notificationArea.notify(qsTr("VpnError"));
        }
    }

    Connections {
        target: BackEnd.translation

        onLanguageChanged: {
            BackEnd.locationController.updateCurrentLocation()
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
                Layout.minimumHeight: 140
                Layout.topMargin: 60

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

            /*Item {
                Layout.fillWidth: true
                Layout.minimumHeight: 30

                EraLabel {
                    anchors.fill: parent
                    anchors.leftMargin: 10

                    text: "3651 человек онлайн на 350 серверах"
                }
            }*/
        }
    }

    CertificateSelectionPopup {
        id: certificateSelectionPopup
    }
}
