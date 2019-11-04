#pragma once

#include <QAbstractListModel>

#include "Certificate.hpp"

namespace app
{
class CertificateListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum DataRoles
    {
        Id = Qt::UserRole + 1,
        Comment,
        CreatedAt
    };

    explicit CertificateListModel();

    void updateCertificates(const QVector<Certificate> &certificates);

public:
    int rowCount(const QModelIndex &parent) const final;
    int columnCount(const QModelIndex &columnCount) const final;
    QVariant data(const QModelIndex &index, int role) const final;

    QHash<int, QByteArray> roleNames() const final;

private:
    QVector<Certificate> m_certificates{};
};

}  // namespace app
