// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ClipboardController.hpp"

#include <QClipboard>
#include <QGuiApplication>

namespace app
{
ClipboardController::ClipboardController()
    : QObject{nullptr}
    , m_clipboard{QGuiApplication::clipboard()}
{
}


void ClipboardController::copyToClipboard(const QString &text)
{
    m_clipboard->setText(text, QClipboard::Clipboard);
}

}  // namespace app
