#pragma once

#include <QObject>
#include <QString>

namespace app
{
class Location : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString ip READ ip NOTIFY dataChanged)
    Q_PROPERTY(QString countryName READ countryName NOTIFY dataChanged)
    Q_PROPERTY(QString regionName READ regionName NOTIFY dataChanged)

public:
    struct Data
    {
        QString ip{};
        QString countryName{};
        QString regionName{};
    };

    explicit Location();

    void setData(const Data &data);

    QString ip() const;
    QString countryName() const;
    QString regionName() const;

signals:
    void dataChanged();
    void errorOccurred();

private:
    Data m_data{};
};

}  // namespace app
