#pragma once

#include <memory>

#include <QHash>
#include <QObject>
#include <QTranslator>

#include "../Models/Translation.hpp"

namespace app
{
class TranslationController : public QObject
{
    Q_OBJECT

public:
    explicit TranslationController(Translation &translation);

    Q_INVOKABLE void setLanguage(const QString &language);

private:
    Translation &m_translation;
    QTranslator m_translator{};
};

}  // namespace app
