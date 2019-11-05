// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "TariffListModel.hpp"

namespace app
{
TariffListModel::TariffListModel()
    : QAbstractListModel{nullptr}
{
}


void TariffListModel::updateTariffs(const QVector<Tariff> &tariffs)
{
    emit layoutAboutToBeChanged();

    m_tariffs = tariffs;

    emit layoutChanged();
    emit tariffCountChanged();
}


void TariffListModel::setLoading(bool isLoading)
{
    m_isLoading = isLoading;
    emit isLoadingChanged();
}


int TariffListModel::tariffCount() const
{
    return m_tariffs.size();
}


bool TariffListModel::isLoading() const
{
    return m_isLoading;
}


int TariffListModel::rowCount(const QModelIndex &parent) const
{
    return m_tariffs.size();
}


int TariffListModel::columnCount(const QModelIndex &columnCount) const
{
    return 1;
}


QVariant TariffListModel::data(const QModelIndex &index, int role) const
{
    const auto &tariff = m_tariffs[index.row()];

    switch (role)
    {
        case DataRoles::Id:
            return tariff.id();

        case DataRoles::Title:
            return tariff.title();

        case DataRoles::Price:
            return tariff.price();

        case DataRoles::ProfitInPercent:
            return tariff.profitInPercent();

        case DataRoles::MonthCount:
            return tariff.monthCount();

        default:
            break;
    }

    return QVariant{};
}


QHash<int, QByteArray> TariffListModel::roleNames() const
{
    static const QHash<int, QByteArray> roles{{DataRoles::Id, "tariffId"},
                                              {DataRoles::Title, "tariffTitle"},
                                              {DataRoles::Price, "tariffPrice"},
                                              {DataRoles::ProfitInPercent, "tariffProfitInPercent"},
                                              {DataRoles::MonthCount, "tariffMonthCount"}};

    return roles;
}

}  // namespace app
