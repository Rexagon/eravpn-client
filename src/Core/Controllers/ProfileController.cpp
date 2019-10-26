// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ProfileController.hpp"

#include <iostream>

#include <QJsonDocument>
#include <QJsonObject>

#include "../../Stuff/Settings.hpp"

namespace app
{
ProfileController::ProfileController(app::Connection &connection, Profile &profile)
    : m_connection{connection}
    , m_profile{profile}
{
}


void ProfileController::signInRemembered()
{
    const auto query = QString{R"(mutation {
    accessToken {
        checkAccessToken {
            ... on Result {
                success
            }
        }
    }
})"};

    m_connection.post(
        query,
        [this](const QJsonDocument &reply) {
            const auto resultData = reply["data"]["accessToken"]["checkAccessToken"];

            const auto successData = resultData["success"];

            if (successData.toBool(false))
            {
                m_profile.signIn();
            }
            else
            {
                m_connection.resetAuthorizationData();
                emit m_profile.signInErrorOccurred();
            }
        },
        [this](const QNetworkReply &) { emit m_profile.signInErrorOccurred(); });
}


void ProfileController::signIn(const QString &login, const QString &password)
{
    const auto query = QString{R"(mutation {
  auth {
    login(login: "%1", password: "%2") {
      ... on ClientLogin {
        client {
            id
            username
            email
        }
        accessToken
        refreshToken
        success
      }
    }
  }
})"};

    m_connection.post(
        query.arg(escaped(login)).arg(escaped(password)),
        [this](const QJsonDocument &reply) {
            const auto loginData = reply["data"]["auth"]["login"];

            const auto accessTokenData = loginData["accessToken"];
            const auto refreshTokenData = loginData["refreshToken"];
            const auto clientData = loginData["client"];

            if (!accessTokenData.isString() || !refreshTokenData.isString() || !clientData.isObject())
            {
                emit m_profile.signInErrorOccurred();
                return;
            }

            fillProfile(clientData.toObject(), accessTokenData.toString(), refreshTokenData.toString());

            m_profile.signIn();
        },
        [this](const QNetworkReply &) { emit m_profile.signInErrorOccurred(); });
}


void ProfileController::signUp(bool isAnonymous,
                               const QString &identifier,
                               const QString &password,
                               const QString &referrerKey)
{
    const auto query = QString{R"(mutation {
  auth {
    registration(%1: "%2", password: "%3"%4) {
      ... on ClientRegistration {
        client {
          id
          username
          email
          authKey
        }
        accessToken
        refreshToken
        success
      }
    }
  }
})"};

    const auto identifierArgument = isAnonymous ? QString{"username"} : QString{"email"};

    const auto referrerArgument =
        referrerKey.isEmpty() ? QString{""} : QString{R"(, referrerKey: "%1")"}.arg(escaped(referrerKey));

    m_connection.post(
        query.arg(identifierArgument).arg(escaped(identifier)).arg(escaped(password)).arg(referrerArgument),
        [this, isAnonymous](const QJsonDocument &reply) {
            const auto registrationData = reply["data"]["auth"]["registration"];

            const auto accessTokenData = registrationData["accessToken"];
            const auto refreshTokenData = registrationData["refreshToken"];

            const auto clientData = registrationData["client"];
            const auto authKeyData = clientData["authKey"];

            if (!accessTokenData.isString() || !refreshTokenData.isString() || !clientData.isObject() ||
                (isAnonymous && !authKeyData.isString()))
            {
                emit m_profile.signUpErrorOccurred();
                return;
            }

            fillProfile(clientData.toObject(), accessTokenData.toString(), refreshTokenData.toString());

            if (isAnonymous)
            {
                emit m_profile.authKeyCopyRequested(authKeyData.toString());
            }
            else
            {
                emit m_profile.emailVerificationRequested();
            }
        },
        [this](const QNetworkReply &) { emit m_profile.signUpErrorOccurred(); });
}


void ProfileController::signOut()
{
    m_connection.resetAuthorizationData();
    m_profile.signOut();
}


void ProfileController::fillProfile(const QJsonObject &clientData,
                                    const QString &accessToken,
                                    const QString &refreshToken)
{
    auto &settings = Settings::instance();
    settings.setAccessToken(accessToken);
    settings.setRefreshToken(refreshToken);

    m_connection.setAuthorizationData(Connection::AuthorizationData{accessToken, refreshToken});

    m_profile.setData(Profile::Data{
        clientData["id"].toString(""),
        clientData["username"].toString(""),
        clientData["email"].toString(""),
    });
}

}  // namespace app
