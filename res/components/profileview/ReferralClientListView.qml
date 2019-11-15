import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import com.eravpn.backend 1.0

ListView {
    readonly property string separatorColor: "#070d24"
    readonly property string lightBlueColor: "#23a2f8"
    readonly property string darkBlueColor: "#1463f6"

    id: view

    interactive: false

    header: RowLayout {
        anchors.left: parent.left
        anchors.right: parent.right

        height: 30

        Text {
            Layout.minimumWidth: 60
            Layout.fillHeight: true

            text: qsTr("ReferralClientListLevel")

            color: "white"
            font.pointSize: 8
            font.family: rootUiFontBold.name

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: qsTr("ReferralClientListUser")

            color: "white"
            font.pointSize: 8
            font.family: rootUiFontBold.name

            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            Layout.minimumWidth: 130
            Layout.fillHeight: true


            text: qsTr("ReferralClientListCreatedAt")

            color: "white"
            font.pointSize: 8
            font.family: rootUiFontBold.name

            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            Layout.minimumWidth: 130
            Layout.fillHeight: true

            text: qsTr("ReferralClientListProfit")

            color: "white"
            font.pointSize: 8
            font.family: rootUiFontBold.name

            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }
    }

    delegate: Item {
        height: 40
        anchors.left: parent.left
        anchors.right: parent.right

        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top

            height: 1

            color: separatorColor
        }

        RowLayout {
            anchors.fill: parent
            anchors.topMargin: 10
            anchors.bottomMargin: 10

            Item {
                Layout.minimumWidth: 60
                Layout.fillHeight: true

                Rectangle {
                    radius: 3

                    color: darkBlueColor

                    width: parent.height
                    height: parent.height

                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter

                    Text {
                        anchors.fill: parent

                        text: referralClientLevel

                        color: "white"
                        font.pointSize: 10
                        font.family: rootUiFontRegular.name

                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }

            Text {
                Layout.fillWidth: true
                Layout.fillHeight: true

                text: referralClientUserName.length > 0 ? referralClientUserName : referralClientEmail

                color: "white"
                font.pointSize: 10
                font.family: rootUiFontRegular.name

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                Layout.minimumWidth: 130
                Layout.fillHeight: true


                text: Qt.formatDateTime(referralClientCreatedAt, "dd.MM.yyyy hh:mm")

                color: "white"
                font.pointSize: 10
                font.family: rootUiFontRegular.name

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                Layout.minimumWidth: 130
                Layout.fillHeight: true

                text: '$' + referralClientProfit.toFixed(2)

                color: "white"
                font.pointSize: 10
                font.family: rootUiFontRegular.name

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}
