import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import "../era"

Item {
    id: component

    property bool activated: false

    property bool withToggleButton: false

    property alias title: titleLabel.text
    property alias description: descriptionLabel.text

    Text {
        id: titleLabel

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        color: "white"
        font.pointSize: 14
        font.family: futuraMediumFont.name
    }

    EraSwitch {
        anchors.verticalCenter: titleLabel.verticalCenter
        anchors.right: parent.right

        visible: withToggleButton

        checked: activated
        onCheckedChanged: component.activated = checked
    }

    Text {
        id: descriptionLabel

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: titleLabel.bottom
        anchors.topMargin: 10

        wrapMode: Text.WordWrap

        font.family: rootUiFontRegular.name
        font.pointSize: 12
        color: "#a4acca"
    }
}
