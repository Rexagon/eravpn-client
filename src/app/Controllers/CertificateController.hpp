#pragma once

#include "../Connection.hpp"
#include "../Models/CertificateListModel.hpp"
#include "../Models/Profile.hpp"

namespace app
{
class CertificateController : public QObject
{
    Q_OBJECT

public:
    explicit CertificateController(Connection &connection, Profile &m_profile, CertificateListModel &certificateList);

    Q_INVOKABLE void refreshCertificates(const QString &countryId);
    Q_INVOKABLE void createNew(const QString &countryId);
    Q_INVOKABLE void setDefault(const QString &countryId, const QString &certificateId);

signals:
    void certificatesRequestError();
    void certificateCreationError();
    void certificateCreated(QString certificateId);

private:
    Connection &m_connection;

    Profile &m_profile;
    CertificateListModel &m_certificateListModel;
};

}  // namespace app
