// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "TariffController.hpp"

#include <QDesktopServices>
#include <QJsonArray>

namespace query
{
using namespace app;

// clang-format off
const auto tariffsList = QueryBuilder::createQuery()
    .addObject("tariffPlan")
        .addUnion("list")
            .withArgument("perPage", -1)
            .addUnionVariant("TariffPlanCollection")
                .addArray("data")
                    .addItem<QString>("id")
                    .addItem<QString>("title")
                    .addItem<double>("price")
                    .addItem<double>("profitInPercent")
                    .addItem<int>("monthCount")
    .build();

const auto buildPaymentLink = QueryBuilder::createMutation()
    .addObject("tariffPlan")
        .addUnion("buildPaymentLink")
            .withArgument("tariffPlanId")
            .addUnionVariant("TariffPlanPaymentFormLinkResult")
                .addItem<QString>("link")
    .build();

// clang-format on
}  // namespace query

namespace app
{
TariffController::TariffController(app::Connection &connection, app::TariffListModel &tariffListModel)
    : QObject{nullptr}
    , m_connection{connection}
    , m_tariffListModel{tariffListModel}
{
}


void TariffController::refreshTariffs()
{
    m_tariffListModel.setLoading(true);

    const auto errorHandler = [this](const QNetworkReply &) { emit tariffsRequestError(); };

    const auto successHandler = [this](const QJsonDocument &reply) {
        const auto tariffsData = reply["data"]["tariffPlan"]["list"]["data"];

        if (!tariffsData.isArray())
        {
            emit tariffsRequestError();
            return;
        }

        const auto tariffsArray = tariffsData.toArray();

        QVector<Tariff> tariffs;
        tariffs.reserve(tariffsArray.size());

        for (const auto &tariffData : tariffsArray)
        {
            const auto idData = tariffData["id"];
            const auto titleData = tariffData["title"];
            const auto priceData = tariffData["price"];
            const auto profitInPercentData = tariffData["profitInPercent"];
            const auto monthCountData = tariffData["monthCount"];

            if (!idData.isString() || !titleData.isString() || !priceData.isDouble() ||
                !profitInPercentData.isDouble() || !monthCountData.isDouble())
            {
                emit tariffsRequestError();
                return;
            }

            tariffs.append(Tariff{idData.toString(), titleData.toString(), priceData.toDouble(),
                                  profitInPercentData.toDouble(), static_cast<int>(monthCountData.toDouble())});
        }

        m_tariffListModel.updateTariffs(tariffs);
        m_tariffListModel.setLoading(false);
    };

    m_connection.post(query::tariffsList.prepare(), successHandler, errorHandler);
}


void TariffController::buy(const QString &tariffId)
{
    m_tariffListModel.setLoading(true);

    const auto errorHandler = [this](const QNetworkReply &) { emit tariffLinkGenerationError(); };

    const auto successHandler = [this](const QJsonDocument &reply) {
        const auto linkData = reply["data"]["tariffPlan"]["buildPaymentLink"]["link"];

        if (!linkData.isString())
        {
            m_tariffListModel.setLoading(false);
            emit tariffLinkGenerationError();
            return;
        }

        m_tariffListModel.setLoading(false);
        QDesktopServices::openUrl(linkData.toString());
    };

    m_connection.post(query::buildPaymentLink.prepare(tariffId), successHandler, errorHandler);
}

}  // namespace app
