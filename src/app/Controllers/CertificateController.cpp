// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "CertificateController.hpp"

#include <QJsonArray>
#include <QJsonObject>
#include <QSysInfo>

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
                            .addItem<QString>("createdAt")
                                .withArgument("format", QString{"U"})
                            .addItem<QString>("comment")
    .build();

const auto createCertificate = QueryBuilder::createMutation()
    .addObject("vpn")
        .addUnion("getOvpnFileLink")
            .withArgument("countryId")
            .withArgument("comment")
            .addUnionVariant("VpnOvpnConfigFileResult")
                .addObject("configFile")
                    .addItem<QString>("id")
                    .addItem<QString>("link")
                    .addItem<QString>("createdAt")
                        .withArgument("format", QString{"U"})
    .build();

// clang-format on
}  // namespace query

namespace app
{
CertificateController::CertificateController(app::Connection &connection,
                                             Profile &profile,
                                             app::CertificateListModel &certificateList)
    : m_connection{connection}
    , m_profile{profile}
    , m_certificateListModel{certificateList}
{
}


void CertificateController::refreshCertificates(const QString &countryId)
{
    m_certificateListModel.setLoading(true);

    const auto errorHandler = [this](const QNetworkReply &) { emit certificatesRequestError(); };

    const auto successHandler = [this](const QJsonDocument &reply) {
        const auto ovpnConfigFilesData = reply["data"]["client"]["getData"]["client"]["ovpnConfigFiles"]["data"];

        if (!ovpnConfigFilesData.isArray())
        {
            emit certificatesRequestError();
            return;
        }

        const auto ovpnConfigFiles = ovpnConfigFilesData.toArray();

        QVector<Certificate> certificates;
        certificates.reserve(ovpnConfigFiles.size());

        for (const auto &certificateData : ovpnConfigFiles)
        {
            const auto idData = certificateData["id"];
            const auto commentData = certificateData["comment"];
            const auto createdAtData = certificateData["createdAt"];
            const auto linkData = certificateData["link"];

            bool isCreatedAtValid{};
            const auto createdAtSecs = createdAtData.toString("").toInt(&isCreatedAtValid);

            if (idData.isString() && linkData.isString() && isCreatedAtValid && commentData.isString())
            {
                const auto createdAt = QDateTime::fromSecsSinceEpoch(createdAtSecs);

                certificates.append(
                    Certificate{idData.toString(), commentData.toString(), createdAt, linkData.toString()});
            }
            else
            {
                emit certificatesRequestError();
                return;
            }
        }

        m_certificateListModel.updateCertificates(certificates);
        m_certificateListModel.setLoading(false);
    };

    m_connection.post(query::getCountryCertificates.prepare(countryId), successHandler, errorHandler);
}


void CertificateController::createNew(const QString &countryId)
{
    m_certificateListModel.setLoading(true);

    const auto now = QDateTime::currentDateTime();

    const auto hostName = QSysInfo::machineHostName();

    const auto errorHandler = [this](const QNetworkReply &) { emit certificatesRequestError(); };

    const auto successHandler = [this, hostName, now](const QJsonDocument &reply) {
        const auto configData = reply["data"]["vpn"]["getOvpnFileLink"]["configFile"];

        const auto idData = configData["id"];
        const auto linkData = configData["link"];

        if (!idData.isString() || !linkData.isString())
        {
            emit certificateCreationError();
            return;
        }

        const auto certificate = Certificate{idData.toString(), hostName, now, linkData.toString()};

        m_certificateListModel.appendCertificate(certificate);

        emit certificateCreated(certificate.id());
        m_certificateListModel.setLoading(false);
    };

    m_connection.post(query::createCertificate.prepare(countryId, hostName), successHandler, errorHandler);
}


void CertificateController::setDefault(const QString &countryId, const QString &certificateId)
{
    auto &settings = Settings::instance();

    settings.setCountryCertificate(m_profile.id(), countryId, certificateId);
}

}  // namespace app
