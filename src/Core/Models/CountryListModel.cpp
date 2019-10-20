// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "CountryListModel.hpp"

#include <iostream>

namespace app
{
CountryListModel::CountryListModel(QObject *parent)
    : QAbstractListModel{parent}
{
}


void CountryListModel::updateCountries(const QVector<Country> &countries)
{
    emit layoutAboutToBeChanged();

    m_countries = countries;

    emit layoutChanged();
}


int CountryListModel::rowCount(const QModelIndex &) const
{
    return m_countries.size();
}


int CountryListModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}


QVariant CountryListModel::data(const QModelIndex &index, int role) const
{
    const auto &country = m_countries[index.row()];

    switch (role)
    {
        case DataRoles::Id:
            return country.id();

        case DataRoles::Title:
            return country.title();

        case DataRoles::Description:
            return country.description();

        case DataRoles::Code:
            return country.code();

        case DataRoles::ServersCount:
            return country.serversCount();

        default:
            break;
    }

    return QVariant{};
}


QHash<int, QByteArray> CountryListModel::roleNames() const
{
    static const QHash<int, QByteArray> roles{{DataRoles::Id, "countryId"},
                                              {DataRoles::Title, "countryTitle"},
                                              {DataRoles::Description, "countryDescription"},
                                              {DataRoles::Code, "countryCode"},
                                              {DataRoles::ServersCount, "serversCount"}};

    return roles;
}

}  // namespace app
