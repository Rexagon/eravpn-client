#pragma once

#include "../Connection.hpp"
#include "../Models/CertificateListModel.hpp"

namespace app
{
class CertificateController
{
    Q_OBJECT

public:
    explicit CertificateController(Connection &connection, CertificateListModel &certificateList);

private:
    Connection &m_connection;
    CertificateListModel &m_certificateListModel;
};

}  // namespace app
