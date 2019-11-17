// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifdef WIN32
#include <Windows.h>
#endif

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>

#include "BackEnd.hpp"
#include "Stuff/RunGuard.hpp"

using namespace app;

namespace
{
constexpr auto BASE_MODULE_NAME = "com.eravpn.backend";
constexpr auto BASE_VERSION_MAJOR = 1;
constexpr auto BASE_VERSION_MINOR = 0;

constexpr auto UNCREATABLE_MESSAGE = "This type of object is managed by native code";

}  // namespace

int main(int argc, char **argv)
{
#ifdef WIN32
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    SetProcessDPIAware();
#endif

    QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
    QCoreApplication::setOrganizationName("EraVPN");
    QCoreApplication::setOrganizationDomain("com.eravpn");
    QCoreApplication::setApplicationName("EraVPN Client");

    QApplication application{argc, argv};

    RunGuard runGuard{BASE_MODULE_NAME};
    if (!runGuard.tryToRun())
    {
        runGuard.notifyAnother();
        return 0;
    }

    auto &backEnd = BackEnd::instance();

    qmlRegisterSingletonType<BackEnd>(BASE_MODULE_NAME, BASE_VERSION_MAJOR, BASE_VERSION_MINOR, "BackEnd",
                                      [](QQmlEngine *, QJSEngine *) {
                                          auto *object = static_cast<QObject *>(&BackEnd::instance());
                                          QQmlEngine::setObjectOwnership(object, QQmlEngine::CppOwnership);
                                          return object;
                                      });

    qmlRegisterUncreatableType<Profile>(BASE_MODULE_NAME, BASE_VERSION_MAJOR, BASE_VERSION_MINOR, "Profile",
                                        UNCREATABLE_MESSAGE);
    qmlRegisterUncreatableType<Tariff>(BASE_MODULE_NAME, BASE_VERSION_MAJOR, BASE_VERSION_MINOR, "Tariff",
                                       UNCREATABLE_MESSAGE);
    qRegisterMetaType<Tariff *>("Tariff*");

    BackEnd::connect(&runGuard, &RunGuard::showRequested, backEnd.applicationController(),
                     &ApplicationController::showRequested);

    QQmlApplicationEngine viewEngine{QUrl("qrc:/main.qml")};

    BackEnd::connect(backEnd.translation(), &Translation::languageChanged, &viewEngine,
                     &QQmlApplicationEngine::retranslate);

    return QApplication::exec();
}
