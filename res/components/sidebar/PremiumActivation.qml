import QtQuick 2.13
import QtQuick.Layouts 1.13

import "../era"

Rectangle {
    id: component

    signal pressed

    EraButton {
        anchors.fill: parent
        anchors.margins: 28

        contentItem: RowLayout {
            Item {
                Layout.fillWidth: true
            }

            Image {
                source: "../../images/icon_crown.png"
            }

            Text {
                text: qsTr("ActivatePremium")

                color: "white"

                font.family: futuraHeavyFont.name
                font.pointSize: 12
            }

            Item {
                Layout.fillWidth: true
            }
        }

        onPressed: {
            component.pressed()
        }
    }
}
