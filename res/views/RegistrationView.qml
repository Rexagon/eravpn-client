import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import "../components"
import "../components/era"

Item {
    signal switchToLogin
    signal switchToMain

    property bool isAnonymous: false

    id: view

    function formAction() {
        switchToMain()
    }

    Component.onCompleted: windowTitleText = "Регистрация"

    BackgroundMap {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

    Item {
        width: 285
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        Logo {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.verticalCenter
            anchors.bottomMargin: 150
        }

        ColumnLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.verticalCenter
            anchors.bottomMargin: 60

            Item {
                Layout.minimumHeight: 32
                Layout.fillWidth: true

                RowLayout {
                    Image {
                        source: isAnonymous ? "../images/icon_email_dark.png" : "../images/icon_email.png"
                    }

                    Text {
                        id: emailMethodSelectionLabel
                        text: "С email и паролем"
                        color: isAnonymous ? "#7880a2" : "white"

                        font.family: rootUiFontBold.name
                        font.pointSize: 12
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    cursorShape: isAnonymous ? Qt.PointingHandCursor : Qt.ArrowCursor
                    hoverEnabled: true

                    onEntered: emailMethodSelectionLabel.font.underline = isAnonymous
                    onExited: emailMethodSelectionLabel.font.underline = false
                    onPressed: {
                        emailMethodSelectionLabel.font.underline = false
                        isAnonymous = false
                    }
                }
            }

            Item {
                Layout.minimumHeight: 32
                Layout.fillWidth: true

                RowLayout {
                    Image {
                        source: isAnonymous ? "../images/icon_fraud.png" : "../images/icon_fraud_dark.png"
                    }

                    Text {
                        id: anonymousMethodSelectionLabel
                        text: "Анонимная регистрация"
                        color: isAnonymous ? "white" : "#7880a2"

                        font.family: rootUiFontBold.name
                        font.pointSize: 12
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    cursorShape: !isAnonymous ? Qt.PointingHandCursor : Qt.ArrowCursor
                    hoverEnabled: true

                    onEntered: anonymousMethodSelectionLabel.font.underline = !isAnonymous
                    onExited: anonymousMethodSelectionLabel.font.underline = false
                    onPressed: {
                        anonymousMethodSelectionLabel.font.underline = false
                        isAnonymous = true
                    }
                }
            }
        }

        ColumnLayout {
            anchors.top: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: -50

            spacing: 10

            Keys.onPressed: {
                if (event.key === Qt.Key_Enter || event.key === Qt.Key_Return) {
                    view.loginAction();
                }
            }

            EraTextField {
                id: identificatorInput

                focus: true

                placeholderText: isAnonymous ? "Придумайте логин" : "Введите email"

                Layout.fillWidth: true
                Layout.minimumHeight: 44
            }

            EraPasswordField {
                id: passwordInput

                placeholderText: "Придумайте пароль"

                Layout.fillWidth: true
                Layout.minimumHeight: 44
            }

            EraPasswordField {
                id: passwordRepeatInput

                placeholderText: "Введите пароль ещё раз"

                Layout.fillWidth: true
                Layout.minimumHeight: 44
            }

            EraTextField {
                id: promoCodeInput

                placeholderText: "Введите промокод"

                Layout.fillWidth: true
                Layout.minimumHeight: 44
            }

            EraButton {
                id: registrationButton

                text: isAnonymous ? "Сгенерировать код-пароль" : "Зарегистрироваться"

                onClicked: formAction()

                Layout.fillWidth: true
                Layout.minimumHeight: 44
            }

            RowLayout {
                Layout.alignment: Qt.AlignCenter

                EraLabel {
                    text: "Уже есть аккаунт?"
                }

                EraLink {
                    text: "Войти"
                    horizontalAlignment: Text.AlignRight
                    onClicked: view.switchToLogin()
                }
            }
        }
    }
}
