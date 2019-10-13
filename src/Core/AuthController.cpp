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


void AuthController::auth(const QString &login, const QString &password)
{
    const auto query = QString{R"(mutation {
  auth {
    login(login: "%1", password: "%2") {
      ... on ClientLogin {
        accessToken
        refreshToken
        success
      }
      ... on AccessTokenError {
        success
      }
      ... on ValidationErrorsList {
        success
        errors {
          field
          messages
        }
      }
    }
  }
})"};

    m_connection.sendQuery(query.arg(escaped(login)).arg(escaped(password)), [this](QNetworkReply &reply) {
        if (reply.error() == QNetworkReply::NoError)
        {
            const auto parsed = QJsonDocument::fromJson(reply.readAll());
            const auto &loginData = parsed["data"]["auth"]["login"];

            std::cout << "AccessToken: " << loginData["accessToken"].toString("unknown").toStdString() << std::endl;
            std::cout << "RefreshToken: " << loginData["refreshToken"].toString("unknown").toStdString() << std::endl;
        }
        else
        {
            std::cout << "Error(" << reply.error() << "): " << reply.errorString().toStdString() << std::endl;
        }
    });
}

}  // namespace app
