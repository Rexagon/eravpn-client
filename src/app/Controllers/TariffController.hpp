#pragma once

#include <QObject>

#include "../Connection.hpp"
#include "../Models/TariffListModel.hpp"

namespace app
{
class TariffController : public QObject
{
    Q_OBJECT

public:
    explicit TariffController(Connection &connection, TariffListModel &tariffListModel);

    Q_INVOKABLE void refreshTariffs();

    Q_INVOKABLE void buy(const QString &tariffId);

signals:
    void tariffsRequestError();
    void tariffLinkGenerationError();

private:
    Connection &m_connection;

    TariffListModel &m_tariffListModel;
};

}  // namespace app
