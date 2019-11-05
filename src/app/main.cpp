// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>

#include "BackEnd.hpp"

using namespace app;

namespace
{
constexpr auto BASE_MODULE_NAME = "com.eravpn.backend";
constexpr auto BASE_VERSION_MAJOR = 1;
constexpr auto BASE_VERSION_MINOR = 0;

}  // namespace

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("EraVPN");
    QCoreApplication::setOrganizationDomain("com.eravpn");
    QCoreApplication::setApplicationName("EraVPN Client");

    QGuiApplication application(argc, argv);

    qmlRegisterSingletonType<BackEnd>(BASE_MODULE_NAME, BASE_VERSION_MAJOR, BASE_VERSION_MINOR, "BackEnd",
                                      [](QQmlEngine *, QJSEngine *) {
                                          auto *object = static_cast<QObject *>(&BackEnd::instance());
                                          QQmlEngine::setObjectOwnership(object, QQmlEngine::CppOwnership);
                                          return object;
                                      });

    QQmlApplicationEngine viewEngine(QUrl("qrc:/main.qml"));

    return QGuiApplication::exec();
}
