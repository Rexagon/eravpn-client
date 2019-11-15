// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ReferralClientListModel.hpp"

namespace app
{
ReferralClientListModel::ReferralClientListModel()
    : QAbstractListModel{nullptr}
{
}


void ReferralClientListModel::updateReferralClients(const QVector<ReferralClient> &referralClients)
{
    emit layoutAboutToBeChanged();

    m_referralClients = referralClients;

    emit layoutChanged();
    emit referralClientCountChanged();
}


void ReferralClientListModel::setLoading(bool isLoading)
{
    m_isLoading = isLoading;

    emit isLoadingChanged();
}


int ReferralClientListModel::referralClientCount() const
{
    return m_referralClients.size();
}


bool ReferralClientListModel::isLoading() const
{
    return m_isLoading;
}


int ReferralClientListModel::rowCount(const QModelIndex &parent) const
{
    return m_referralClients.size();
}


int ReferralClientListModel::columnCount(const QModelIndex &) const
{
    return 1;
}


QVariant ReferralClientListModel::data(const QModelIndex &index, int role) const
{
    const auto &referralClient = m_referralClients[index.row()];

    switch (role)
    {
        case DataRoles::Id:
            return referralClient.id();

        case DataRoles::Email:
            return referralClient.email();

        case DataRoles::UserName:
            return referralClient.userName();

        case DataRoles::Level:
            return referralClient.level();

        case DataRoles::Profit:
            return referralClient.profit();

        case DataRoles::CreatedAt:
            return referralClient.createdAt();

        default:
            break;
    }

    return QVariant{};
}


QHash<int, QByteArray> ReferralClientListModel::roleNames() const
{
    static const QHash<int, QByteArray> roles{{DataRoles::Id, "referralClientId"},
                                              {DataRoles::Email, "referralClientEmail"},
                                              {DataRoles::UserName, "referralClientUserName"},
                                              {DataRoles::Level, "referralClientLevel"},
                                              {DataRoles::Profit, "referralClientProfit"},
                                              {DataRoles::CreatedAt, "referralClientCreatedAt"}};

    return roles;
}

}  // namespace app
