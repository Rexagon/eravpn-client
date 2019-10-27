import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

ListView {
    id: notificationArea

    property int currentNotificationId: 0

    function notify(title, duration = 1000) {
        model.append({
            modelUniqueId: currentNotificationId,
            modelTitle: title,
            modelDuration: duration
        });

        ++currentNotificationId;
    }

    spacing: 10

    model: ListModel { }

    add: Transition {
        NumberAnimation { properties: "x,y"; duration: 100 }
    }

    delegate: Notification {
        id: notification

        Layout.fillWidth: true
        Layout.alignment: Qt.AlignTop

        uniqueId: modelUniqueId
        title: modelTitle
        duration: modelDuration

        onDestroyRequested: {
            const model = notificationArea.model;

            for (var i = 0; i < model.count; ++i) {
                if (model.get(i).modelUniqueId === this.uniqueId) {
                    model.remove(i);
                    return;
                }
            }
        }
    }
}