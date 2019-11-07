import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

Rectangle {
    readonly property string redTextColor: "#ff5d81"

    readonly property string lightProfitColor: "#dcdee2"
    readonly property string lightColor: "#f4f6fa"
    readonly property string lightTextColor: "#0e1242"
    readonly property string lightTextColorBottom: "#b1b3bf"

    readonly property string darkProfitGradientLeft: "#ffb280"
    readonly property string darkProfitGradientRight: "#ff5d81"
    readonly property string darkGradientBottom: "#173b93"
    readonly property string darkGradientTop: "#142560"
    readonly property string darkTextColor: "#f4f6fa"
    readonly property string darkTextColorBottom: "#99bbed"

    property string title: "title"
    property double price: 36
    property double profitInPercent: 70
    property int monthCount: 12

    property bool isPressed: false

    readonly property double pricePerMonth: price / monthCount
    readonly property double originalPrice: price * 100 / (100 - profitInPercent)

    signal pressed

    function declension(number, titles) {
        const cases = [2, 0, 1, 1, 1, 2];
        return titles[(number % 100 > 4 && number % 100 < 20) ? 2 : cases[(number % 10 < 5) ? number % 10 : 5]];
    }

    id: component

    radius: 10

    width: 250
    height: 350

    state: "unhovered"

    states: [
        State {
            name: "unhovered"
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
            PropertyChanges {
                target: profitGradientLeft
                color: darkProfitGradientLeft
            }
            PropertyChanges {
                target: profitGradientRight
                color: darkProfitGradientRight
            }
            PropertyChanges {
                target: profitInPercentLabel
                color: darkTextColor
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

        text: title

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

                text: "/ " + qsTr("PerMonth")

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

                visible: originalPrice != price

                font.strikeout: true

                color: redTextColor
                font.family: futuraMediumFont.name
                font.pointSize: 12
            }

            Text {
                id: billDescriptionPriceLabel

                text: '$' + price

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
            let string = qsTr("Billed") + " ";

            if (monthCount == 1) {
                return string + qsTr("MonthDeclensionOne");
            }

            const declensions = [qsTr("MonthDeclensionOne"), qsTr("MonthDeclensionTwo"), qsTr("MonthDeclensionFive")];
            return string + monthCount + " " + declension(monthCount, declensions);
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

        text: qsTr("UnlimitedTraffic")

        color: lightTextColor
        font.family: futuraMediumFont.name
        font.pointSize: 14
    }

    Text {
        id: referralLabel

        anchors.top: trafficLabel.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 10

        text: qsTr("ReferralProgramAvailable")

        horizontalAlignment: Text.AlignHCenter

        color: lightTextColorBottom
        font.family: futuraMediumFont.name
        font.pointSize: 12
    }

    Rectangle {
        anchors.verticalCenter: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        visible: profitInPercent > 0

        width: 105
        height: 30

        radius: 10

        gradient: Gradient {
            id: profitBackgroundGradient

            orientation: Gradient.Horizontal
            GradientStop { id: profitGradientLeft; position: 0.0; color: lightProfitColor }
            GradientStop { id: profitGradientRight; position: 1.0; color: lightProfitColor }
        }

        Text {
            id: profitInPercentLabel

            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            text: qsTr("Profit") + profitInPercent + "%"

            color: lightTextColor
            font.family: futuraMediumFont.name
            font.pointSize: 10
        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor

        onEntered: component.state = ""
        onExited: component.state = "unhovered"

        onPressed: {
            component.isPressed = true;
            component.pressed();
        }

        onReleased: {
            component.isPressed = false;
        }
    }
}
