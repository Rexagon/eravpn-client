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

    const auto clientQuery = QString{R"(query {
  client {
    getData {
      ... on ClientResult {
        client {
          id
          status
          username
          email
          authKey
          ovpnConfigPassword
        }
      }
    }
  }
})"};

    const auto emitConnectionError = [this] {
        m_connection.resetAuthorizationData();
        emit m_profile.signInErrorOccurred();
    };

    const auto errorHandler = [emitConnectionError](const QNetworkReply &) { emitConnectionError(); };

    const auto clientDataHandler = [this, clientQuery, emitConnectionError](const QJsonDocument &reply) {
        const auto clientData = reply["data"]["client"]["getData"]["client"];

        if (!clientData.isObject())
        {
            emitConnectionError();
        }

        setProfileData(clientData.toObject());
        m_profile.signIn();
    };

    m_connection.post(
        query,
        [this, emitConnectionError, clientQuery, clientDataHandler, errorHandler](const QJsonDocument &reply) {
            const auto resultData = reply["data"]["accessToken"]["checkAccessToken"];
            const auto success = resultData["success"].toBool(false);

            if (!success)
            {
                emitConnectionError();
                return;
            }

            m_connection.post(clientQuery, clientDataHandler, errorHandler);
        },
        errorHandler);
}


void ProfileController::signIn(const QString &login, const QString &password)
{
    const auto query = QString{R"(mutation {
  auth {
    login(login: "%1", password: "%2") {
      ... on ClientLogin {
        client {
          id
          status
          username
          email
          ovpnConfigPassword
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

            setAuthData(accessTokenData.toString(), refreshTokenData.toString());
            setProfileData(clientData.toObject());

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
          status
          username
          email
          authKey
          ovpnConfigPassword
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
            const auto statusData = clientData["status"];

            if (!accessTokenData.isString() || !refreshTokenData.isString() || !clientData.isObject() ||
                (isAnonymous && !authKeyData.isString()) || !statusData.isString())
            {
                emit m_profile.signUpErrorOccurred();
                return;
            }

            setAuthData(accessTokenData.toString(), refreshTokenData.toString());
            setProfileData(clientData.toObject());

            if (isAnonymous)
            {
                emit m_profile.authKeyCopyRequested(authKeyData.toString());
                return;
            }

            m_profile.signIn();
        },
        [this](const QNetworkReply &) { emit m_profile.signUpErrorOccurred(); });
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

    m_profile.setData(Profile::Data{
        profileData["id"].toString(""),                //
        profileData["username"].toString(""),          //
        profileData["email"].toString(""),             //
        profileData["ovpnConfigPassword"].toString(),  //
        clientStatus                                   //
    });
}

}  // namespace app
