// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "BackEnd.hpp"

#include <iostream>

namespace app
{
QObject *BackEnd::singletonProvider(QQmlEngine *qmlEngine, QJSEngine *scriptEngine)
{
    Q_UNUSED(qmlEngine);
    Q_UNUSED(scriptEngine);

    return new BackEnd();
}

BackEnd::BackEnd(QObject *parent)
    : QObject{parent}
    , m_connection{API_URL, this}
    , m_authController{m_connection}
{
}


AuthController *BackEnd::authController()
{
    return &m_authController;
}

}  // namespace app
