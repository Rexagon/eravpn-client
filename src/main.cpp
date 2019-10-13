// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>

#include "Core/BackEnd.hpp"

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("EraVPN");
    QCoreApplication::setOrganizationDomain("com.eravpn");

    QGuiApplication application(argc, argv);

    qmlRegisterSingletonType<app::BackEnd>("com.eravpn.backend", 1, 0, "BackEnd", &app::BackEnd::singletonProvider);

    QQmlApplicationEngine viewEngine(QUrl("qrc:/main.qml"));

    return QGuiApplication::exec();
}
