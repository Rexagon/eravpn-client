import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

Rectangle {
    readonly property string redTextColor: "#ff5d81"

    readonly property string lightColor: "#f4f6fa"
    readonly property string lightTextColor: "#0e1242"
    readonly property string lightTextColorBottom: "#b1b3bf"

    readonly property string darkGradientBottom: "#173b93"
    readonly property string darkGradientTop: "#142560"
    readonly property string darkTextColor: "#f4f6fa"
    readonly property string darkTextColorBottom: "#99bbed"

    property string tariffId: ""
    property string tariffTitle: "title"
    property double tariffPrice: 36
    property double tariffProfitInPercent: 70
    property int tariffMonthCount: 12

    property bool isPressed: false

    readonly property double pricePerMonth: tariffPrice / tariffMonthCount
    readonly property double originalPrice: tariffPrice * 100 / (100 - tariffProfitInPercent)

    signal pressed

    function declension(number, titles) {
        const cases = [2, 0, 1, 1, 1, 2];
        return titles[(number % 100 > 4 && number % 100 < 20) ? 2 : cases[(number % 10 < 5) ? number % 10 : 5]];
    }

    id: component

    radius: 10

    width: 260
    height: 350

    states: [
        State {
            name: "hovered"
            PropertyChanges {
                target: gradientTop
                color: darkGradientTop
            }
            PropertyChanges {
                target: gradientBottom
                color: component.isPressed ? darkGradientTop : darkGradientBottom
            }
            PropertyChanges {
                target: titleLabel
                color: darkTextColor
            }
            PropertyChanges {
                target: priceIntegerPartLabel
                color: darkTextColor
            }
            PropertyChanges {
                target: priceFrationPartLabel
                color: darkTextColor
            }
            PropertyChanges {
                target: perMonthLabel
                color: darkTextColor
            }
            PropertyChanges {
                target: billDescriptionPriceLabel
                color: darkTextColor
            }
            PropertyChanges {
                target: billDescriptionLabel
                color: darkTextColor
            }
            PropertyChanges {
                target: trafficLabel
                color: darkTextColor
            }
            PropertyChanges {
                target: referralLabel
                color: darkTextColorBottom
            }
        }
    ]

    transitions: Transition {
        ColorAnimation {
            duration: 100
        }
    }

    gradient: Gradient {
        id: controlBackgroundGradient

        orientation: Gradient.Vertical
        GradientStop { id: gradientBottom; position: 0.0; color: lightColor }
        GradientStop { id: gradientTop; position: 1.0; color: lightColor }
    }

    Text {
        id: titleLabel

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 30

        text: tariffTitle

        color: lightTextColor
        font.family: futuraMediumFont.name
        font.pointSize: 18
    }

    RowLayout {
        id: priceLabel
        spacing: 0

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: titleLabel.bottom
        anchors.topMargin: 20

        Item {
            Layout.fillWidth: true
        }

        Text {
            id: priceIntegerPartLabel

            Layout.fillHeight: true

            text: '$' + Math.floor(pricePerMonth).toString()
            font.letterSpacing: -1
            verticalAlignment: Text.AlignVCenter

            color: lightTextColor
            font.family: futuraHeavyFont.name
            font.pointSize: 42
        }

        Item {
            Layout.fillHeight: true
            width: 80

            Text {
                id: priceFrationPartLabel

                anchors.bottom: perMonthLabel.top
                anchors.left: parent.left

                text: '.' + (pricePerMonth - Math.floor(pricePerMonth)).toFixed(2).split('.')[1]

                color: lightTextColor
                font.family: futuraHeavyFont.name
                font.pointSize: 22
            }

            Text {
                id: perMonthLabel

                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.bottomMargin: 8

                text: '/ за месяц'

                color: lightTextColor
                font.family: futuraHeavyFont.name
                font.pointSize: 12
            }
        }

        Item {
            Layout.fillWidth: true
        }
    }

    Item {
        anchors.top: priceLabel.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.topMargin: 10

        RowLayout {
            anchors.fill: parent

            Item {
                Layout.fillWidth: true
            }

            Text {
                text: '$' + originalPrice

                font.strikeout: true

                color: redTextColor
                font.family: futuraMediumFont.name
                font.pointSize: 12
            }

            Text {
                id: billDescriptionPriceLabel

                text: '$' + tariffPrice

                color: lightTextColor
                font.family: futuraMediumFont.name
                font.pointSize: 12
            }

            Item {
                Layout.fillWidth: true
            }
        }
    }

    Text {
        id: billDescriptionLabel

        anchors.top: priceLabel.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.topMargin: 30

        text: {
            "счёт выставляется\nраз в " + tariffMonthCount + " " +
                    declension(tariffMonthCount, ["месяц", "месяца", "месяцев"])
        }

        horizontalAlignment: Text.AlignHCenter

        color: lightTextColor
        font.family: futuraMediumFont.name
        font.pointSize: 12
    }

    Text {
        id: trafficLabel

        anchors.top: billDescriptionLabel.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20

        text: "Безлимитный трафик"

        color: lightTextColor
        font.family: futuraMediumFont.name
        font.pointSize: 14
    }

    Text {
        id: referralLabel

        anchors.top: trafficLabel.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 10

        text: "В данном тарифе доступна\nреферальная программа"

        horizontalAlignment: Text.AlignHCenter

        color: lightTextColorBottom
        font.family: futuraMediumFont.name
        font.pointSize: 12
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor

        onEntered: component.state = "hovered"
        onExited: component.state = ""

        onPressed: {
            component.isPressed = true;
            component.pressed();
        }

        onReleased: {
            component.isPressed = false;
        }
    }
}
