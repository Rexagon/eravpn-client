#pragma once

#include <QAbstractListModel>

#include "Certificate.hpp"

namespace app
{
class CertificateListModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int certificateCount READ certificateCount NOTIFY certificateCountChanged)
    Q_PROPERTY(bool isLoading READ isLoading NOTIFY isLoadingChanged)

public:
    enum DataRoles
    {
        Id = Qt::UserRole + 1,
        Comment,
        CreatedAt
    };

    explicit CertificateListModel();

    void updateCertificates(const QVector<Certificate> &certificates);
    void appendCertificate(const Certificate &certificate);

    void setLoading(bool isLoading);

    int certificateCount() const;
    bool isLoading() const;

signals:
    void certificateCountChanged();
    void isLoadingChanged();

public:
    int rowCount(const QModelIndex &parent) const final;
    int columnCount(const QModelIndex &columnCount) const final;
    QVariant data(const QModelIndex &index, int role) const final;

    QHash<int, QByteArray> roleNames() const final;

private:
    bool m_isLoading{true};
    QVector<Certificate> m_certificates{};
};

}  // namespace app
