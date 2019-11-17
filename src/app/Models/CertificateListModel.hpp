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
    Q_PROPERTY(bool isGenerating READ isGenerating NOTIFY isGeneratingChanged)

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
    void setGenerating(bool isGenerating);

    int certificateCount() const;
    bool isLoading() const;
    bool isGenerating() const;

signals:
    void certificateCountChanged();
    void isLoadingChanged();
    void isGeneratingChanged();

public:
    int rowCount(const QModelIndex &parent) const final;
    int columnCount(const QModelIndex &index) const final;
    QVariant data(const QModelIndex &index, int role) const final;

    QHash<int, QByteArray> roleNames() const final;

private:
    bool m_isLoading{true};
    bool m_isGenerating{false};
    QVector<Certificate> m_certificates{};
};

}  // namespace app
