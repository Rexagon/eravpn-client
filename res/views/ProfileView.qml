import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import com.eravpn.backend 1.0

import "../components"
import "../components/era"
import "../components/settings"
import "../components/profileview"

Item {
    readonly property string lightBackgroundColor: "#4f6699"
    readonly property string darkBackgroundColor: "#0f1444"

    signal closeView
    signal switchToTariffSelection

    id: view

    StackView.onActivating: {
        windowTitleText = qsTr("Profile");
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
                text: qsTr("Profile") + " " + BackEnd.profile.userName

                color: "white"

                font.family: futuraHeavyFont.name
                font.pointSize: 20
            }

            Item {
                implicitHeight: 20
            }

            EraButton {
                Layout.minimumWidth: 120
                Layout.minimumHeight: 40

                text: qsTr("SignOut", "as action")

                onClicked: {
                    view.closeView();
                    BackEnd.profileController.signOut();
                }
            }

            Item {
                implicitHeight: 20
            }

            Group {
                Layout.minimumWidth: 120
                implicitHeight: 120

                title: {
                    const baseText = qsTr("YourEmailAddress");

                    if (BackEnd.profile.email.length < 1) {
                        return baseText;
                    }

                    const status = BackEnd.profile.status === Profile.New ? qsTr("NotVerified") : qsTr("Verified");

                    return baseText + " (" + status + ")";
                }

                contentItem: ColumnLayout {
                    id: emailChangeGroup

                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top

                    property bool inProcess: false
                    property bool isInputValid: {
                        return emailInput.length > 0 &&
                                emailInput.validator.regExp.test(emailInput.text) &&
                                emailInput.text !== BackEnd.profile.email;
                    }

                    Connections {
                        target: BackEnd.profileController

                        onEmailChangeError: {
                            notificationArea.notify(qsTr("EmailChangeError"));
                            emailChangeGroup.inProcess = false;
                        }

                        onEmailChanged: {
                            notificationArea.notify(qsTr("EmailChanged"), true);
                            emailChangeGroup.inProcess = false;
                            BackEnd.profileController.refreshProfile();
                        }

                        onConfirmCodeResendError: {
                            notificationArea.notify(qsTr("ConfirmCodeResendError"));
                            emailChangeGroup.inProcess = false;
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Layout.minimumHeight: 40

                        spacing: 10

                        EraTextField {
                            id: emailInput

                            Layout.fillHeight: true
                            implicitWidth: 200

                            text: BackEnd.profile.email
                            placeholderText: qsTr("EmailAddress")

                            validator: RegExpValidator {
                                regExp: /\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*/
                            }
                        }

                        EraButton {
                            Layout.minimumWidth: 200
                            Layout.minimumHeight: 40

                            visible: BackEnd.profile.email !== emailInput.text

                            enabled: emailChangeGroup.isInputValid && !emailChangeGroup.inProcess

                            text: qsTr("Change")

                            onClicked: {
                                emailChangeGroup.inProcess = true;
                                BackEnd.profileController.changeEmail(emailInput.text);
                            }
                        }

                        EraButton {
                            Layout.minimumWidth: 200
                            Layout.minimumHeight: 40

                            visible: BackEnd.profile.status === Profile.New &&
                                     BackEnd.profile.email.length > 0 &&
                                     BackEnd.profile.email === emailInput.text

                            enabled: BackEnd.profile.status === Profile.New &&
                                     BackEnd.profile.email.length > 0 &&
                                     !emailChangeGroup.inProcess

                            text: qsTr("ResendConfirmCode")

                            onClicked: {
                                emailChangeGroup.inProcess = true;
                                BackEnd.profileController.resendConfirmCode();
                            }
                        }
                    }
                }
            }

            Separator {
                Layout.fillWidth: true
            }

            Group {
                Layout.minimumWidth: 120
                implicitHeight: 120

                title: qsTr("YourTariff")

                contentItem: ColumnLayout {
                    id: tariffGroup

                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top

                    property string tariffId: BackEnd.profile.tariffId

                    property Tariff tariff: {
                        const model = BackEnd.tariffListModel;
                        for (let i = 0; i < model.tariffCount; ++i) {
                            const tariff = model.get(i);

                            if (tariff.id === tariffId) {
                                return tariff;
                            }
                        }

                        return null;
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Layout.minimumHeight: 40

                        spacing: 10

                        visible: BackEnd.profile.isTariffPurchased

                        Rectangle {
                            radius: 4

                            Layout.minimumWidth: 200
                            Layout.minimumHeight: 40

                            gradient: Gradient {
                                orientation: Gradient.Horizontal
                                GradientStop { position: 0.0; color: "#ffb280" }
                                GradientStop { position: 1.0; color: "#ff5d81" }
                            }

                            Text {
                                anchors.fill: parent

                                text: tariffGroup.tariff ? tariffGroup.tariff.title : "unknown"

                                color: "white"

                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font.family: futuraMediumFont.name
                                font.pointSize: 12
                            }
                        }

                        Item {
                            Layout.minimumWidth: 300
                            Layout.minimumHeight: 40

                            Text {
                                anchors.fill: parent

                                text: {
                                    return qsTr("ExpiresAt") + ": " +
                                            Qt.formatDateTime(BackEnd.profile.tariffExpiredAt, "dd.MM.yyyy hh:mm");
                                }

                                color: "white"

                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font.family: futuraMediumFont.name
                                font.pointSize: 12
                            }
                        }
                    }

                    EraButton {
                        Layout.minimumWidth: 200
                        Layout.minimumHeight: 40

                        visible: !BackEnd.profile.isTariffPurchased

                        text: qsTr("SelectTariff")

                        onClicked: {
                            view.switchToTariffSelection();
                        }
                    }
                }
            }

            Separator {
                Layout.fillWidth: true
            }

            Group {
                Layout.minimumWidth: 120
                implicitHeight: 160

                title: qsTr("ChangePassword", "as title")

                contentItem: ColumnLayout {
                    id: passwordChangeGroup

                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top

                    property bool inProcess: false
                    property bool isInputValid: {
                        const password = passwordInput.text;

                        return password.length >= 0 &&
                                newPasswordInput.length >= 6 && newPasswordInput.length <= 16 &&
                                newPasswordInput.text === newPasswordRepeatInput.text;
                    }

                    Connections {
                        target: BackEnd.profileController

                        onPasswordChangeError: {
                            notificationArea.notify(qsTr("PasswordChangeError"));
                            passwordChangeGroup.inProcess = false;
                            passwordInput.text = "";
                            newPasswordRepeatInput.text = "";
                        }

                        onPasswordChanged: {
                            notificationArea.notify(qsTr("PasswordChanged"), true);
                            passwordChangeGroup.inProcess = false;
                            passwordInput.text = "";
                            newPasswordInput.text = "";
                            newPasswordRepeatInput.text = "";

                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Layout.minimumHeight: 40

                        spacing: 10

                        EraPasswordField {
                            id: passwordInput

                            Layout.fillHeight: true
                            implicitWidth: 200

                            placeholderText: qsTr("CurrentPassword")
                        }

                        EraPasswordField {
                            id: newPasswordInput

                            Layout.fillHeight: true
                            implicitWidth: 200

                            placeholderText: qsTr("NewPassword")
                        }

                        EraPasswordField {
                            id: newPasswordRepeatInput

                            Layout.fillHeight: true
                            implicitWidth: 200

                            placeholderText: qsTr("NewPasswordRepeat")
                        }
                    }

                    EraButton {
                        Layout.minimumWidth: 200
                        Layout.minimumHeight: 40

                        enabled: parent.isInputValid && !parent.inProcess

                        text: qsTr("Apply")

                        onClicked: {
                            parent.inProcess = true;
                            BackEnd.profileController.changePassword(passwordInput.text, newPasswordInput.text);
                        }
                    }
                }
            }

            Separator {
                Layout.fillWidth: true
            }

            Group {
                id: referralsGroup

                readonly property int referralCount: BackEnd.referralClientListModel.referralClientCount

                Layout.fillWidth: true
                Layout.minimumHeight: 100 + referralCount * 40

                title: referralCount > 0 ? qsTr("YourReferrals") : qsTr("YouHaveNoReferrals")

                contentItem: ColumnLayout {
                    anchors.fill: parent

                    visible: referralsGroup.referralCount > 0

                    Item {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        ReferralClientListView {
                            id: referralClientListView

                            anchors.fill: parent
                            anchors.leftMargin: 20
                            anchors.rightMargin: 20

                            model: BackEnd.referralClientListModel
                        }
                    }
                }
            }
        }
    }
}
