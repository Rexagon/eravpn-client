#pragma once

#include "../Connection.hpp"
#include "../Models/ReferralClientListModel.hpp"

namespace app
{
class ReferralClientsController : public QObject
{
    Q_OBJECT

public:
    explicit ReferralClientsController(Connection &connection, ReferralClientListModel &referralClientListModel);

    Q_INVOKABLE void refreshReferralClients();

signals:
    void referralClientsRequestError();

private:
    Connection &m_connection;

    ReferralClientListModel &m_referralClientListModel;
};

}  // namespace app
