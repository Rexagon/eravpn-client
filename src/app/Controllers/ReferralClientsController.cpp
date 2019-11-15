// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ReferralClientsController.hpp"

#include <QJsonArray>

namespace query
{
using namespace app;

// clang-format off
const auto getReferralUsers = QueryBuilder::createQuery()
    .addObject("client")
        .addUnion("getData")
            .addUnionVariant("ClientResult")
                .addObject("client")
                    .addObject("referralClients")
                        .withArgument("perPage", -1)
                        .addArray("data")
                            .addItem<QString>("id")
                            .addItem<QString>("email")
                            .addItem<QString>("username")
                            .addItem<double>("level")
                            .addItem<double>("profit")
                            .addItem<QString>("createdAt")
                                .withArgument("format", QString{"U"})
    .build();
// clang-format on
}  // namespace query

namespace app
{
ReferralClientsController::ReferralClientsController(Connection &connection,
                                                   ReferralClientListModel &referralClientListModel)
    : m_connection{connection}
    , m_referralClientListModel{referralClientListModel}
{
}


void ReferralClientsController::refreshReferralClients()
{
    m_referralClientListModel.setLoading(true);

    const auto errorHandler = [this](const QNetworkReply &) { emit referralClientsRequestError(); };

    const auto successHandler = [this](const QJsonDocument &reply) {
        const auto referralClientsData = reply["data"]["client"]["getData"]["client"]["referralClients"]["data"];

        if (!referralClientsData.isArray())
        {
            emit referralClientsRequestError();
            return;
        }

        const auto referralClientsArrayData = referralClientsData.toArray();

        QVector<ReferralClient> referralClients;
        referralClients.reserve(referralClientsArrayData.size());

        for (const auto &referralClientData : referralClientsArrayData)
        {
            const auto idData = referralClientData["id"];
            const auto emailData = referralClientData["email"];
            const auto userNameData = referralClientData["username"];
            const auto levelData = referralClientData["level"];
            const auto profitData = referralClientData["profit"];
            const auto createdAtData = referralClientData["createdAt"];

            bool isCreatedAtValid{};
            const auto createdAtSecs = createdAtData.toString("").toInt(&isCreatedAtValid);

            if (idData.isString() && levelData.isDouble() && profitData.isDouble() && isCreatedAtValid)
            {
                const auto createdAt = QDateTime::fromSecsSinceEpoch(createdAtSecs);

                referralClients.append(
                    ReferralClient{idData.toString(), emailData.toString(""), userNameData.toString(""),
                                   static_cast<int>(levelData.toDouble(1)), profitData.toDouble(0.0), createdAt});
            }
            else
            {
                emit referralClientsRequestError();
                return;
            }
        }

        m_referralClientListModel.updateReferralClients(referralClients);
        m_referralClientListModel.setLoading(false);
    };

    m_connection.post(query::getReferralUsers.prepare(), successHandler, errorHandler);
}

}  // namespace app
