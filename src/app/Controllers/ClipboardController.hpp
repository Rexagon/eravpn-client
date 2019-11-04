#pragma once

#include <QClipboard>
#include <QObject>
#include <QString>

namespace app
{
class ClipboardController : public QObject
{
    Q_OBJECT

public:
    explicit ClipboardController();

    Q_INVOKABLE void copyToClipboard(const QString &text);

private:
    QClipboard *m_clipboard;
};

}  // namespace app
