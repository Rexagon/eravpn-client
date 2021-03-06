#pragma once

#include <memory>
#include <vector>

#include <QAbstractListModel>

#include "Tariff.hpp"

namespace app
{
class TariffListModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int tariffCount READ tariffCount NOTIFY tariffCountChanged)
    Q_PROPERTY(bool isLoading READ isLoading NOTIFY isLoadingChanged)

public:
    enum DataRoles
    {
        Id = Qt::UserRole + 1,
        Title,
        Price,
        ProfitInPercent,
        MonthCount
    };

    explicit TariffListModel();

    void updateTariffs(std::vector<std::unique_ptr<Tariff>> &&tariffs);

    void setLoading(bool isLoading);

    int tariffCount() const;
    bool isLoading() const;

    Q_INVOKABLE Tariff *get(int index);

signals:
    void tariffCountChanged();
    void isLoadingChanged();

public:
    int rowCount(const QModelIndex &parent) const final;
    int columnCount(const QModelIndex &columnCount) const final;
    QVariant data(const QModelIndex &index, int role) const final;

    QHash<int, QByteArray> roleNames() const final;

private:
    bool m_isLoading{true};
    std::vector<std::unique_ptr<Tariff>> m_tariffs{};
};

}  // namespace app
