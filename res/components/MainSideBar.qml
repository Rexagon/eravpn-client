import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import com.eravpn.backend 1.0

import "era"
import "sidebar"

Item {
    readonly property string lightBackgroundColor: "#4f6699"
    readonly property string backgroundColor: "#173878"
    readonly property string semiDarkBackgroundColor: "#122b5e"
    readonly property string darkBackgroundColor: "#0f1444"
    readonly property string redColor: "#ff4747"
    readonly property string blueColor: "#00d2f4"

    property string currentServersList: "free"

    id: component

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        PremiumActivation {
            Layout.fillWidth: true
            Layout.minimumHeight: 100

            color: backgroundColor

            visible: !BackEnd.profile.isTariffPurchased

            onPressed: {
                view.switchToTariffSelection();
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.minimumHeight: 1
            color: BackEnd.profile.isTariffPurchased ? darkBackgroundColor : lightBackgroundColor
        }

        ConnectionInfo {
            Layout.fillWidth: true
            Layout.minimumHeight: 150

            color: darkBackgroundColor
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.minimumHeight: 1
            color: lightBackgroundColor
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true

            color: backgroundColor

            TabBar {
                id: tabBar

                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top

                height: 50
                spacing: 0

                TabButton {
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom

                    background: Rectangle {
                        color: tabBar.currentIndex === 0 ? backgroundColor : semiDarkBackgroundColor
                    }

                    contentItem: EraLabel {
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter

                        text: "Бесплатные серверы"
                        font.pointSize: 11
                    }

                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onPressed: mouse.accepted = false
                    }
                }

                TabButton {
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom

                    background: Rectangle {
                        color: tabBar.currentIndex === 0 ? semiDarkBackgroundColor : backgroundColor
                    }

                    contentItem: EraLabel {
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter

                        text: "Премиум-доступ"
                        font.pointSize: 11
                    }

                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onPressed: mouse.accepted = false
                    }
                }
            }

            StackLayout {
                currentIndex: tabBar.currentIndex

                clip: true

                anchors.fill: parent
                anchors.topMargin: 50

                ServerListView {
                    isPremium: false
                    model: BackEnd.freeServersList
                }

                ServerListView {
                    isPremium: true
                    model: BackEnd.premiumServersList
                }
            }
        }
    }
}
