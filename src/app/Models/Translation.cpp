// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Translation.hpp"

namespace app
{
Translation::Translation()
    : QObject{nullptr}
{
}


void Translation::setLanguage(const QString &language)
{
    m_language = language;
    emit languageChanged();
}


const QString &Translation::language() const
{
    return m_language;
}

}  // namespace app
