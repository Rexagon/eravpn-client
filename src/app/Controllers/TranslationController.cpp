// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "TranslationController.hpp"

#include <QGuiApplication>
#include <QLocale>

#include "../Stuff/Settings.hpp"

namespace
{
constexpr auto TRANSLATION_PATH = ":/translations/main_%1.qm";

const QStringList LOCALES = {"en", "ru"};


QString getDefaultLanguage()
{
    const auto language = QLocale::system().name();
    if (LOCALES.contains(language))
    {
        return language;
    }

    return LOCALES.first();
}
}  // namespace

namespace app
{
TranslationController::TranslationController(Translation &translation)
    : QObject{nullptr}
    , m_translation{translation}
{
    setLanguage(Settings::instance().getLanguage().value_or(""));
}


void TranslationController::setLanguage(const QString &language)
{
    auto newLanguage = language;
    if (LOCALES.contains(language))
    {
        newLanguage = language;
    }
    else
    {
        newLanguage = getDefaultLanguage();
    }

    QGuiApplication::removeTranslator(&m_translator);
    m_translator.load(QString{TRANSLATION_PATH}.arg(newLanguage));
    QGuiApplication::installTranslator(&m_translator);

    m_translation.setLanguage(newLanguage);
}

}  // namespace app
