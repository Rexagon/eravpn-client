import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import com.eravpn.backend 1.0

import "../components"
import "../components/era"

Item {
    id: view

    signal switchToMain
    signal switchToLogin

    Component.onCompleted: {
        BackEnd.profileController.signInRemembered();
    }

    StackView.onActivated: {
        windowTitleText = qsTr("SignIn", "as title")
        windowTitleButtonsVisible = false
    }

    Connections {
        target: BackEnd.profile
        onAuthorizedChanged: {
            view.switchToMain()
        }
    }

    Connections {
        target: BackEnd.profileController
        onSignInErrorOccurred: {
            view.switchToLogin()
        }
    }

    BackgroundMap {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

    Image {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        width: 30
        height: 30

        source: "../images/loading.svg"

        RotationAnimation on rotation {
            loops: Animation.Infinite
            duration: 1000
            from: 0
            to: 360
        }
    }
}
