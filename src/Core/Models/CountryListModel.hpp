#pragma once

#include <QAbstractListModel>

#include "Country.hpp"

namespace app
{
class CountryListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum DataRoles
    {
        Id = Qt::UserRole + 1,
        Title,
        Description,
        Code,
        ServersCount
    };

    explicit CountryListModel(QObject *parent = nullptr);

    void updateCountries(const QVector<Country> &countries);

public:
    int rowCount(const QModelIndex &parent = QModelIndex{}) const final;
    int columnCount(const QModelIndex &parent = QModelIndex{}) const final;
    QVariant data(const QModelIndex &index, int role) const final;

    QHash<int, QByteArray> roleNames() const final;

private:
    QVector<Country> m_countries{};
};

}  // namespace app
