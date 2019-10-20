// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "AuthController.hpp"

#include <iostream>

#include <QJsonDocument>
#include <QJsonObject>

namespace app
{
AuthController::AuthController(app::Connection &connection)
    : m_connection{connection}
{
}


void AuthController::authorize(const QString &login, const QString &password)
{
    const auto query = QString{R"(mutation {
  auth {
    login(login: "%1", password: "%2") {
      ... on ClientLogin {
        accessToken
        refreshToken
        success
      }
    }
  }
})"};

    m_connection.sendQuery(
        query.arg(escaped(login)).arg(escaped(password)),
        [this](const QJsonDocument &reply) {
            const auto loginData = reply["data"]["auth"]["login"];

            const auto accessTokenData = loginData["accessToken"];
            const auto refreshTokenData = loginData["refreshToken"];

            if (!accessTokenData.isString() || !refreshTokenData.isString())
            {
                emit authorizationError();
                return;
            }

            m_connection.setAuthorizationData(
                Connection::AuthorizationData{accessTokenData.toString(), refreshTokenData.toString()});

            emit authorized();
        },
        [this](const QNetworkReply &) { emit authorizationError(); });
}


void AuthController::createUser(bool isAnonymous,
                                const QString &identifier,
                                const QString &password,
                                const QString &referrerKey)
{
    const auto query = QString{R"(mutation {
  auth {
    registration(%1: "%2", password: "%3"%4) {
      ... on ClientRegistration {
        accessToken
        refreshToken
        %5
        success
      }
    }
  }
})"};

    const auto identifierArgument = isAnonymous ? QString{"username"} : QString{"email"};

    const auto referrerArgument =
        referrerKey.isEmpty() ? QString{""} : QString{R"(, referrerKey: "%1")"}.arg(escaped(referrerKey));

    const auto authKeyArgument = isAnonymous ? QString{"client {\nauthKey\n}"} : QString{""};

    m_connection.sendQuery(
        query.arg(identifierArgument)
            .arg(escaped(identifier))
            .arg(escaped(password))
            .arg(referrerArgument)
            .arg(authKeyArgument),
        [this, isAnonymous](const QJsonDocument &reply) {
            const auto registrationData = reply["data"]["auth"]["registration"];

            const auto accessTokenData = registrationData["accessToken"];
            const auto refreshTokenData = registrationData["refreshToken"];

            const auto authKeyData = registrationData["client"]["authKey"];

            if (!accessTokenData.isString() || !refreshTokenData.isString() || (isAnonymous && !authKeyData.isString()))
            {
                emit registrationError();
                return;
            }

            m_connection.setAuthorizationData(
                Connection::AuthorizationData{accessTokenData.toString(), refreshTokenData.toString()});

            if (isAnonymous)
            {
                emit registeredWithEmail();
            }
            else
            {
                emit registeredWithLogin(authKeyData.toString());
            }
        },
        [this](const QNetworkReply &) { emit registrationError(); });
}


void AuthController::logout()
{
    m_connection.resetAuthorizationData();
    emit loggedOut();
}

}  // namespace app
