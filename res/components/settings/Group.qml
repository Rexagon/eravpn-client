import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import "../era"

Item {
    id: component

    property alias title: titleLabel.text

    property Item contentItem

    Text {
        id: titleLabel

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        color: "white"
        font.pointSize: 14
        font.family: futuraMediumFont.name
    }

    Item {
        id: descriptionLabel

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: titleLabel.bottom
        anchors.bottom: parent.bottom
        anchors.topMargin: 10

        children: [
            component.contentItem
        ]
    }
}
