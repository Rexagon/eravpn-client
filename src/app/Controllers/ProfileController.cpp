// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ProfileController.hpp"

#include <QJsonDocument>
#include <QJsonObject>

#include "../Stuff/Settings.hpp"

namespace query
{
using namespace app;

// clang-format off
const auto checkAccessToken = QueryBuilder::createMutation()
    .addObject("accessToken")
        .addUnion("refreshToken")
            .addUnionVariant("ClientRefreshAccessToken")
                .addItem<QString>("accessToken")
                .addItem<QString>("refreshToken")
                .addItem<bool>("success")
    .build();

const auto getClientData = QueryBuilder::createQuery()
    .addObject("client")
        .addUnion("getData")
            .addUnionVariant("ClientResult")
                .addObject("client")
                    .addItem<QString>("id")
                    .addItem<QString>("status")
                    .addItem<QString>("username")
                    .addItem<QString>("email")
                    .addItem<QString>("authKey")
                    .addItem<QString>("ovpnConfigPassword")
                    .addObject("tariffPlan")
                        .addItem<QString>("expiredAt")
                            .withArgument("format", QString{"U"})
                        .addObject("data")
                            .addItem<QString>("id")
    .build();

const auto signIn = QueryBuilder::createMutation()
    .addObject("auth")
        .addUnion("login")
            .withArgument("login")
            .withArgument("password")
            .addUnionVariant("ClientLogin")
                .addObject("client")
                    .addItem<QString>("id")
                    .addItem<QString>("status")
                    .addItem<QString>("username")
                    .addItem<QString>("email")
                    .addItem<QString>("ovpnConfigPassword")
                    .addObject("tariffPlan")
                        .addObject("data")
                            .addItem<QString>("id")
                        .endObject()
                        .addItem<QString>("expiredAt")
                            .withArgument("format", QString{"U"})
                    .endObject()
                .endObject()
                .addItem<QString>("accessToken")
                .addItem<QString>("refreshToken")
    .build();

const auto signUpWithEmail = app::QueryBuilder::createMutation()
    .addObject("auth")
        .addUnion("registration")
        .withArgument("email")
        .withArgument("password")
        .withArgument("referrerKey")
        .addUnionVariant("ClientRegistration")
            .addObject("client")
                .addItem<QString>("id")
                .addItem<QString>("status")
                .addItem<QString>("username")
                .addItem<QString>("email")
                .addItem<QString>("authKey")
                .addItem<QString>("ovpnConfigPassword")
            .endObject()
            .addItem<QString>("accessToken")
            .addItem<QString>("refreshToken")
    .build();

const auto signUpWithUsername = app::QueryBuilder::createMutation()
    .addObject("auth")
        .addUnion("registration")
        .withArgument("username")
        .withArgument("password")
        .withArgument("referrerKey")
            .addUnionVariant("ClientRegistration")
            .addObject("client")
                .addItem<QString>("id")
                .addItem<QString>("status")
                .addItem<QString>("username")
                .addItem<QString>("email")
                .addItem<QString>("authKey")
                .addItem<QString>("ovpnConfigPassword")
            .endObject()
            .addItem<QString>("accessToken")
            .addItem<QString>("refreshToken")
    .build();

const auto changeEmail = QueryBuilder::createMutation()
    .addObject("client")
        .addUnion("changeEmail")
            .withArgument("email")
            .addUnionVariant("Result")
                .addItem<QString>("success")
    .build();

const auto resendConfirmCode = QueryBuilder::createMutation()
    .addObject("auth")
        .addUnion("resendConfirmCode")
            .addUnionVariant("Result")
                .addItem<QString>("success")
    .build();

const auto changePassword = QueryBuilder::createMutation()
    .addObject("client")
        .addUnion("changePassword")
            .withArgument("oldPassword")
            .withArgument("password")
            .addUnionVariant("Result")
                .addItem<QString>("success")
    .build();

// clang-format on
}  // namespace query

namespace app
{
ProfileController::ProfileController(app::Connection &connection, Profile &profile)
    : m_connection{connection}
    , m_profile{profile}
{
}


void ProfileController::signInRemembered()
{
    const auto emitConnectionError = [this] {
        m_connection.resetAuthorizationData();
        emit signInErrorOccurred();
    };

    const auto errorHandler = [this, emitConnectionError](const QNetworkReply &) {
        m_connection.setRefreshTokenHeaderActive(false);
        emitConnectionError();
    };

    const auto clientDataHandler = [this, emitConnectionError](const QJsonDocument &reply) {
        const auto clientData = reply["data"]["client"]["getData"]["client"];

        if (!clientData.isObject())
        {
            emitConnectionError();
        }

        setProfileData(clientData.toObject());
        m_profile.signIn();
    };

    m_connection.setRefreshTokenHeaderActive(true);

    m_connection.post(
        query::checkAccessToken.prepare(),
        [this, emitConnectionError, clientDataHandler, errorHandler](const QJsonDocument &reply) {
            const auto resultData = reply["data"]["accessToken"]["refreshToken"];
            const auto accessTokenData = resultData["success"];
            const auto refreshTokenData = resultData["success"];
            const auto success = resultData["success"].toBool(false);

            if (!success || accessTokenData.isString() || refreshTokenData.isString())
            {
                emitConnectionError();
                return;
            }

            m_connection.setRefreshTokenHeaderActive(false);
            m_connection.setAuthorizationData(
                Connection::AuthorizationData{accessTokenData.toString(), refreshTokenData.toString()});

            m_connection.post(query::getClientData.prepare(), clientDataHandler, errorHandler);
        },
        errorHandler);
}


void ProfileController::signIn(const QString &login, const QString &password)
{
    m_connection.post(
        query::signIn.prepare(login, password),
        [this](const QJsonDocument &reply) {
            const auto loginData = reply["data"]["auth"]["login"];

            const auto accessTokenData = loginData["accessToken"];
            const auto refreshTokenData = loginData["refreshToken"];

            const auto clientData = loginData["client"];

            if (!accessTokenData.isString() || !refreshTokenData.isString() || !clientData.isObject())
            {
                emit signInErrorOccurred();
                return;
            }

            setAuthData(accessTokenData.toString(), refreshTokenData.toString());
            setProfileData(clientData.toObject());

            m_profile.signIn();
        },
        [this](const QNetworkReply &) { emit signInErrorOccurred(); });
}


void ProfileController::signUp(bool isAnonymous,
                               const QString &identifier,
                               const QString &password,
                               const QString &referrerKey)
{
    const auto query = isAnonymous ? query::signUpWithUsername.prepare(identifier, password, referrerKey)
                                   : query::signUpWithEmail.prepare(identifier, password, referrerKey);

    m_connection.post(
        query,
        [this, isAnonymous](const QJsonDocument &reply) {
            const auto registrationData = reply["data"]["auth"]["registration"];

            const auto accessTokenData = registrationData["accessToken"];
            const auto refreshTokenData = registrationData["refreshToken"];

            const auto clientData = registrationData["client"];
            const auto authKeyData = clientData["authKey"];
            const auto statusData = clientData["status"];

            if (!accessTokenData.isString() || !refreshTokenData.isString() || !clientData.isObject() ||
                (isAnonymous && !authKeyData.isString()) || !statusData.isString())
            {
                emit signUpErrorOccurred();
                return;
            }

            setAuthData(accessTokenData.toString(), refreshTokenData.toString());
            setProfileData(clientData.toObject());

            if (isAnonymous)
            {
                emit authKeyCopyRequested(authKeyData.toString());
                return;
            }

            m_profile.signIn();
        },
        [this](const QNetworkReply &) { emit signUpErrorOccurred(); });
}


void ProfileController::signOut()
{
    auto &settings = Settings::instance();
    settings.setAccessToken(std::nullopt);
    settings.setRefreshToken(std::nullopt);

    m_connection.resetAuthorizationData();

    m_profile.signOut();
}


void ProfileController::setAuthData(const QString &accessToken, const QString &refreshToken)
{
    auto &settings = Settings::instance();
    settings.setAccessToken(accessToken);
    settings.setRefreshToken(refreshToken);

    m_connection.setAuthorizationData(Connection::AuthorizationData{accessToken, refreshToken});
}


void ProfileController::refreshProfile()
{
    const auto errorHandler = [this](const QNetworkReply &) { emit profileUpdateError(); };

    const auto successHandler = [this](const QJsonDocument &reply) {
        const auto clientData = reply["data"]["client"]["getData"]["client"];

        if (!clientData.isObject())
        {
            emit profileUpdateError();
            return;
        }

        setProfileData(clientData.toObject());
    };

    m_connection.post(query::getClientData.prepare(), successHandler, errorHandler);
}


void ProfileController::changeEmail(const QString &newEmail)
{
    const auto errorHandler = [this](const QNetworkReply &) { emit emailChangeError(); };

    const auto successHandler = [this, newEmail](const QJsonDocument &reply) {
        const auto successData = reply["data"]["client"]["changeEmail"]["success"];

        if (!successData.toBool(false))
        {
            emit emailChangeError();
            return;
        }

        emit emailChanged();
        m_profile.setEmail(newEmail);
    };

    m_connection.post(query::changeEmail.prepare(newEmail), successHandler, errorHandler);
}


void ProfileController::resendConfirmCode()
{
    const auto errorHandler = [this](const QNetworkReply &) { emit confirmCodeResendError(); };

    const auto successHandler = [this](const QJsonDocument &reply) {
        const auto successData = reply["data"]["client"]["resendConfirmCode"]["success"];

        if (!successData.toBool(false))
        {
            emit confirmCodeResendError();
            return;
        }

        emit confirmCodeSent();
    };

    m_connection.post(query::resendConfirmCode.prepare(), successHandler, errorHandler);
}


void ProfileController::changePassword(const QString &oldPassword, const QString &newPassword)
{
    const auto errorHandler = [this](const QNetworkReply &) { emit passwordChangeError(); };

    const auto successHandler = [this](const QJsonDocument &reply) {
        const auto successData = reply["data"]["client"]["changePassword"]["success"];

        if (!successData.toBool(false))
        {
            emit passwordChangeError();
            return;
        }

        emit passwordChanged();
    };

    m_connection.post(query::changePassword.prepare(oldPassword, newPassword), successHandler, errorHandler);
}


void ProfileController::setProfileData(const QJsonObject &profileData)
{
    const auto statusData = profileData["status"].toString();
    auto clientStatus = Profile::Status::Unknown;
    if (statusData == "new")
    {
        clientStatus = Profile::Status::New;
    }
    else if (statusData == "active")
    {
        clientStatus = Profile::Status::Active;
    }

    std::optional<Profile::TariffData> tariffData{};
    if (const auto tariffPlanData = profileData["tariffPlan"]; tariffPlanData.isObject())
    {
        const auto tariffId = tariffPlanData["data"]["id"];
        const auto tariffExpiredAtData = tariffPlanData["expiredAt"];

        bool isExpiredAtValid{};
        const auto expiredAtSecs = tariffExpiredAtData.toString("").toInt(&isExpiredAtValid);

        if (tariffId.isString() && isExpiredAtValid)
        {
            tariffData = Profile::TariffData{tariffId.toString(), QDateTime::fromSecsSinceEpoch(expiredAtSecs)};
        }
    }

    m_profile.setData(Profile::Data{profileData["id"].toString(""),                //
                                    profileData["username"].toString(""),          //
                                    profileData["email"].toString(""),             //
                                    profileData["ovpnConfigPassword"].toString(),  //
                                    clientStatus,                                  //
                                    tariffData});
}

}  // namespace app
