// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "BackEnd.hpp"

#include <iostream>

namespace app
{
QObject *BackEnd::singletonProvider(QQmlEngine *qmlEngine, QJSEngine *scriptEngine)
{
    Q_UNUSED(qmlEngine);
    Q_UNUSED(scriptEngine);

    return new BackEnd();
}

BackEnd::BackEnd(QObject *parent)
    : QObject{parent}
    , m_connection{API_URL, this}
{
}


void BackEnd::sendQuery()
{
    const auto query = R"({
  country {
    list(isPremium: true, hasVpn: true, hasProxy: true) {
      ... on CountryCollection {
        data {
          id
          title
          description
        }
      }
    }
  }
})";

    m_connection.sendQuery(query, [this](QNetworkReply &reply) {
        if (reply.error() == QNetworkReply::NoError)
        {
            std::cout << reply.readAll().toStdString() << std::endl;
        }
        else
        {
            std::cout << "Error(" << reply.error() << "): " << reply.errorString().toStdString() << std::endl;
        }
    });
}

}  // namespace app
