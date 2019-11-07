#pragma once

#include <QObject>
#include <QString>

namespace app
{
class Translation : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString language READ language NOTIFY languageChanged)

public:
    explicit Translation();

    void setLanguage(const QString &language);
    const QString &language() const;

signals:
    void languageChanged();

private:
    QString m_language{};
};

}  // namespace app
