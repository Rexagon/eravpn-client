// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "VpnController.hpp"

#include <iostream>

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QStandardPaths>
#include <QSysInfo>

#include "../../Stuff/Settings.hpp"

namespace
{
constexpr auto CONFIG_FILE = "/%1.ovpn";

}  // namespace

namespace app
{
VpnController::VpnController(Connection &connection, Profile &profile, VpnConnection &vpnConnection)
    : QObject{nullptr}
    , m_connection{connection}
    , m_profile{profile}
    , m_vpnConnection{vpnConnection}
    , m_configDirectory{QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)}
{
}


void VpnController::updateCertificateList()
{
    const auto query = QString{R"(query {
  client {
    getData {
      ... on ClientResult {
        client {
          id
          ovpnConfigFiles(page: 1, perPage: 1000) {
            data {
              link
              countryId
            }
          }
        }
      }
    }
  }
})"};
}


void VpnController::enableVpn(const QString &countryId)
{
    auto &settings = Settings::instance();

    auto certificatePath = settings.countryCertificatePath(countryId);
    if (certificatePath.has_value())
    {
        QFile file{*certificatePath};

        if (file.open(QIODevice::ReadOnly | QIODevice::ExistingOnly))
        {
            m_vpnConnection.start(file.readAll());
            return;
        }
    }

    // QSysInfo::machineHostName()

    const auto query = QString{R"(query {
  client {
    getData {
      ... on ClientResult {
        client {
          ovpnConfigFiles(countryId: "%1") {
            data {
              id
              link
              comment
            }
          }
        }
      }
    }
  }
})"};

    const auto errorHandler = [this](const QNetworkReply &) {
        std::cout << "NETWORK ERROR" << std::endl;
        emit m_vpnConnection.connectionErrorOccurred();
    };

    const auto downloadedConfigHandlerFactory = [this, countryId](const QString &id) {
        return [this, id, countryId](QNetworkReply &reply) {
            QFile file{QString{m_configDirectory} + QString{CONFIG_FILE}.arg(id)};
            QDir::current().mkpath(m_configDirectory);

            if (!file.open(QIODevice::WriteOnly))
            {
                emit m_vpnConnection.connectionErrorOccurred();
                return;
            }

            const auto data = reply.readAll();
            file.write(data);
            file.close();

            Settings::instance().setCountryCertificatePath(countryId, file.fileName());

            m_vpnConnection.start(data);
        };
    };

    const auto configsRequestHandler = [this, downloadedConfigHandlerFactory](const QJsonDocument &reply) {
        const auto ovpnConfigFilesData = reply["data"]["client"]["getData"]["client"]["ovpnConfigFiles"]["data"];

        if (!ovpnConfigFilesData.isArray())
        {
            std::cout << "RESULT IS NOT ARRAY" << std::endl;
            emit m_vpnConnection.connectionErrorOccurred();
            return;
        }

        const auto ovpnConfigFiles = ovpnConfigFilesData.toArray();
        if (ovpnConfigFiles.empty())
        {
            emit m_vpnConnection.connectionErrorOccurred();
            return;
        }

        const auto configData = ovpnConfigFiles[0].toObject();
        const auto configIdData = configData["id"];
        const auto configLinkData = configData["link"];
        const auto configCommentData = configData["comment"];

        m_connection.get(configLinkData.toString(), downloadedConfigHandlerFactory(configIdData.toString()));
    };

    m_connection.post(query.arg(escaped(countryId)), configsRequestHandler, errorHandler);
}

}  // namespace app
