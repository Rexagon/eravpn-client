// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <QGuiApplication>
#include <QQuickView>
#include <QQmlApplicationEngine>

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("EraVPN");
    QCoreApplication::setOrganizationDomain("eravpn.com");

    QGuiApplication application(argc, argv);
    QQmlApplicationEngine viewEngine(QUrl("qrc:/views/main.qml"));

    return QGuiApplication::exec();
}
