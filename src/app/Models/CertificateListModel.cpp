// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "CertificateListModel.hpp"

namespace app
{
CertificateListModel::CertificateListModel()
    : QAbstractListModel{nullptr}
{
}


void CertificateListModel::updateCertificates(const QVector<Certificate> &certificates)
{
    emit layoutAboutToBeChanged();

    m_certificates = certificates;

    emit layoutChanged();
    emit certificateCountChanged();
}


void CertificateListModel::appendCertificate(const Certificate &certificate)
{
    emit layoutAboutToBeChanged();

    m_certificates.append(certificate);

    emit layoutChanged();
    emit certificateCountChanged();
}


void CertificateListModel::setLoading(bool isLoading)
{
    m_isLoading = isLoading;

    emit isLoadingChanged();
}


void CertificateListModel::setGenerating(bool isGenerating)
{
    m_isGenerating = isGenerating;

    emit isGeneratingChanged();
}


int CertificateListModel::certificateCount() const
{
    return m_certificates.size();
}


bool CertificateListModel::isLoading() const
{
    return m_isLoading;
}


bool CertificateListModel::isGenerating() const
{
    return m_isGenerating;
}


int CertificateListModel::rowCount(const QModelIndex &) const
{
    return m_certificates.size();
}


int CertificateListModel::columnCount(const QModelIndex &) const
{
    return 1;
}


QVariant CertificateListModel::data(const QModelIndex &index, int role) const
{
    const auto &certificate = m_certificates[index.row()];

    switch (role)
    {
        case DataRoles::Id:
            return certificate.id();

        case DataRoles::Comment:
            return certificate.comment();

        case DataRoles::CreatedAt:
            return certificate.createdAt();

        default:
            break;
    }

    return QVariant{};
}


QHash<int, QByteArray> CertificateListModel::roleNames() const
{
    static const QHash<int, QByteArray> roles{{DataRoles::Id, "certificateId"},
                                              {DataRoles::Comment, "certificateComment"},
                                              {DataRoles::CreatedAt, "certificateCreatedAt"}};

    return roles;
}

}  // namespace app
