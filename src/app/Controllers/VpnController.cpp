// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "VpnController.hpp"

#include <QFile>
#include <QJsonArray>
#include <QStandardPaths>
#include <QSysInfo>

#include <iostream>

#include "../Stuff/Settings.hpp"


namespace query
{
using namespace app;

// clang-format off
const auto getCountryCertificates = QueryBuilder::createQuery()
    .addObject("client")
        .addUnion("getData")
            .addUnionVariant("ClientResult")
                .addObject("client")
                    .addObject("ovpnConfigFiles")
                        .withArgument("countryId")
                        .addObject("data")
                            .addItem<QString>("id")
                            .addItem<QString>("link")
                            .addItem<QString>("comment")
    .build();

// clang-format on
}  // namespace query


namespace app
{
VpnController::VpnController(Connection &connection, Profile &profile, VpnConnection &vpnConnection)
    : QObject{nullptr}
    , m_connection{connection}
    , m_profile{profile}
    , m_vpnConnection{vpnConnection}
{
}


void VpnController::start(const QString &countryId)
{
    auto &settings = Settings::instance();

    const auto start = [this, countryId](const QString &config) {
        Settings::instance().setLastConnectedCountry(m_profile.id(), countryId);
        m_vpnConnection.start(countryId, m_profile.ovpnConfigPassword(), config);
    };

    auto savedCertificate = settings.countryCertificate(m_profile.id(), countryId);
    if (savedCertificate.has_value())
    {
        QFile file{savedCertificate->path};

        if (file.open(QIODevice::ReadOnly | QIODevice::ExistingOnly))
        {
            start(file.readAll());
            return;
        }
    }

    const auto hostName = QSysInfo::machineHostName();

    const auto errorHandler = [this](const QNetworkReply &) { emit m_vpnConnection.connectionErrorOccurred(); };

    const auto downloadedConfigHandlerFactory = [this, start](const QString &id) {
        return [this, id, start](QNetworkReply &reply) {
            QFile file{Settings::instance().createCertificatePath(id)};

            if (!file.open(QIODevice::WriteOnly))
            {
                emit m_vpnConnection.connectionErrorOccurred();
                return;
            }

            const auto data = reply.readAll();
            file.write(data);
            file.close();

            start(data);
        };
    };

    const auto configsRequestHandler = [this, hostName, countryId, savedCertificate,
                                        downloadedConfigHandlerFactory](const QJsonDocument &reply) {
        const auto ovpnConfigFilesData = reply["data"]["client"]["getData"]["client"]["ovpnConfigFiles"]["data"];

        if (!ovpnConfigFilesData.isArray())
        {
            emit m_vpnConnection.connectionErrorOccurred();
            return;
        }

        const auto ovpnConfigFiles = ovpnConfigFilesData.toArray();

        for (const auto &certificateData : ovpnConfigFiles)
        {
            const auto configIdData = certificateData["id"];
            const auto configLinkData = certificateData["link"];
            const auto configCommentData = certificateData["comment"];

            if (!configIdData.isString() || !configLinkData.isString() || !configCommentData.isString())
            {
                emit m_vpnConnection.connectionErrorOccurred();
                return;
            }

            if ((savedCertificate.has_value() && savedCertificate->id == configIdData.toString()) ||
                configCommentData.toString() == hostName)
            {
                m_connection.get(configLinkData.toString(), downloadedConfigHandlerFactory(configIdData.toString()));
                return;
            }
        }

        emit certificateNotFound(countryId, ovpnConfigFiles.size());
    };

    m_connection.post(query::getCountryCertificates.prepare(countryId), configsRequestHandler, errorHandler);
}


void VpnController::startLastSaved()
{
    const auto lastConnectedCountry = Settings::instance().lastConnectedCountry(m_profile.id());
    if (!lastConnectedCountry.has_value())
    {
        return;
    }

    start(*lastConnectedCountry);
}


void VpnController::stop()
{
    m_vpnConnection.stop();
}

}  // namespace app
