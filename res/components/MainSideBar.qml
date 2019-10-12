import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

Rectangle {
    readonly property string lightBackgroundColor: "#4f6699"
    readonly property string backgroundColor: "#173878"
    readonly property string darkBackgroundColor: "#0f1444"
    readonly property string redColor: "#ff4747"

    id: component

    color: lightBackgroundColor

    ColumnLayout {
        anchors.fill: parent
        spacing: 1

        Rectangle {
            Layout.fillWidth: true
            Layout.minimumHeight: 100

            color: backgroundColor

            EraButton {
                anchors.fill: parent
                anchors.margins: 28

                contentItem: RowLayout {
                    Item {
                        Layout.fillWidth: true
                    }

                    Image {
                        source: "../images/icon_crown.png"
                    }

                    Text {
                        text: "Активировать премиум"

                        color: "white"

                        font.family: futuraHeavyFont.name
                        font.pointSize: 12
                    }

                    Item {
                        Layout.fillWidth: true
                    }
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.minimumHeight: 150

            color: darkBackgroundColor

            ColumnLayout {
                anchors.fill: parent
                anchors.leftMargin: 40
                anchors.topMargin: 35
                anchors.bottomMargin: 35

                RowLayout {
                    Image {
                        source: "../images/icon_alert.png"
                    }

                    EraLabel {
                        text: "Соединение не защищено"
                        color: redColor
                    }
                }

                EraLabel {
                    text: "Ваш IP: 198.166.0.2"
                    color: "white"
                }

                EraLabel {
                    text: "Местоположение: Москва"
                    color: "white"
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true

            color: backgroundColor
        }
    }
}
