import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import com.eravpn.backend 1.0

import "../components"
import "../components/era"
import "../components/settings"

Item {
    readonly property string lightBackgroundColor: "#4f6699"
    readonly property string darkBackgroundColor: "#0f1444"

    signal closeView
    signal switchToTariffSelection

    id: view

    StackView.onActivating: {
        windowTitleText = "Профиль";
        windowTitleButtonsVisible = true;
        windowTitleBar.state = "profile_opened";
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Escape) {
            view.closeView();
        }
    }

    ScrollView {
        anchors.fill: parent
        anchors.topMargin: 16
        anchors.leftMargin: 56
        anchors.rightMargin: 16

        clip: true

        ScrollBar.vertical: ScrollBar {
            id: scrollBar

            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom

            width: 10

            background: ColumnLayout {
                Item {
                    Layout.minimumHeight: 4
                }

                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Rectangle {
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.horizontalCenter: parent.horizontalCenter

                        color: darkBackgroundColor
                        width: 2
                    }
                }

                Item {
                    Layout.minimumHeight: 4
                }
            }

            contentItem: Rectangle {
                implicitWidth: 6
                implicitHeight: 100
                radius: width / 2

                color: scrollBar.pressed ? darkBackgroundColor : lightBackgroundColor
            }
        }

        ColumnLayout {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: window.width - 56 * 2

            EraBackButton {
                Layout.alignment: Qt.AlignLeft

                onClicked: view.closeView()
            }

            Text {
                text: "Профиль " + BackEnd.profile.userName

                color: "white"

                font.family: futuraHeavyFont.name
                font.pointSize: 20
            }

            Item {
                implicitHeight: 20
            }

            Group {
                Layout.minimumWidth: 120
                implicitHeight: 120

                title: {
                    const baseText = "Ваш email-адрес";

                    if (BackEnd.profile.status !== "new" || BackEnd.profile.email.length < 1) {
                        return baseText;
                    }

                    return baseText + " (подтверждён)";
                }

                contentItem: ColumnLayout {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top

                    RowLayout {
                        Layout.fillWidth: true
                        Layout.minimumHeight: 40

                        spacing: 10

                        EraTextField {
                            id: emailInput

                            Layout.fillHeight: true
                            implicitWidth: 200

                            text: BackEnd.profile.email
                            placeholderText: "Email адрес"
                        }

                        EraButton {
                            Layout.minimumWidth: 200
                            Layout.minimumHeight: 40

                            enabled: emailInput.length > 0 && emailInput.text !== BackEnd.profile.email

                            text: "Изменить"

                            onPressed: {
                                BackEnd.profileController.changeEmail(emailInput.text);
                            }
                        }
                    }
                }
            }

            Group {
                Layout.minimumWidth: 120
                implicitHeight: 120

                title: "Ваш тариф"

                contentItem: ColumnLayout {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top

                    EraButton {
                        Layout.minimumWidth: 200
                        Layout.minimumHeight: 40

                        text: "Выбрать тариф"

                        onClicked: {
                            view.switchToTariffSelection();
                        }
                    }
                }
            }

            Group {
                Layout.minimumWidth: 120
                implicitHeight: 120

                title: "Смена пароля"

                contentItem: ColumnLayout {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top

                    property bool isInputValid: {
                        const password = passwordInput.text;

                        return password.length >= 0 &&
                                newPasswordInput.length >= 6 && newPasswordInput.length <= 16 &&
                                newPasswordInput.text === newPasswordRepeatInput.text;
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Layout.minimumHeight: 40

                        spacing: 10

                        EraPasswordField {
                            id: passwordInput

                            Layout.fillHeight: true
                            implicitWidth: 200

                            placeholderText: "Текущий пароль"
                        }

                        EraPasswordField {
                            id: newPasswordInput

                            Layout.fillHeight: true
                            implicitWidth: 200

                            placeholderText: "Новый пароль"
                        }

                        EraPasswordField {
                            id: newPasswordRepeatInput

                            Layout.fillHeight: true
                            implicitWidth: 200

                            placeholderText: "Повторите новый пароль"
                        }
                    }

                    EraButton {
                        Layout.minimumWidth: 200
                        Layout.minimumHeight: 40

                        enabled: parent.isInputValid

                        text: "Подтвердить"

                        onPressed: {
                            BackEnd.profileController.changePassword(passwordInput.text, newPasswordInput.text);
                        }
                    }
                }
            }

            Item {
                implicitHeight: 20
            }

            EraButton {
                Layout.minimumWidth: 120
                Layout.minimumHeight: 40

                text: "Выход"

                onClicked: {
                    view.closeView();
                    BackEnd.profileController.signOut();
                }
            }
        }
    }
}
