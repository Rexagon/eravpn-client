#pragma once

#include <QAbstractListModel>

#include "ReferralClient.hpp"

namespace app
{
class ReferralClientListModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int referralClientCount READ referralClientCount NOTIFY referralClientCountChanged)
    Q_PROPERTY(bool isLoading READ isLoading NOTIFY isLoadingChanged)

public:
    enum DataRoles
    {
        Id = Qt::UserRole + 1,
        Email,
        UserName,
        Level,
        Profit,
        CreatedAt
    };

    explicit ReferralClientListModel();

    void updateReferralClients(const QVector<ReferralClient> &referralClients);

    void setLoading(bool isLoading);

    int referralClientCount() const;
    bool isLoading() const;

signals:
    void referralClientCountChanged();
    void isLoadingChanged();

private:
    int rowCount(const QModelIndex &parent) const final;
    int columnCount(const QModelIndex &index) const final;
    QVariant data(const QModelIndex &index, int role) const final;

    QHash<int, QByteArray> roleNames() const final;

private:
    bool m_isLoading{true};
    QVector<ReferralClient> m_referralClients{};
};

}  // namespace app
