#include <QApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>

#include "mainwindow/mainwindow.hpp"
#include "AircraftManager/AircraftManager.hpp"
#include "FlightplanManager/FlightplanManager.hpp"
#include "ConnectionHandler/ConnectionHandler.hpp"
#include "common/QmlEnums.hpp"
#include <QtQml>
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);

    a.setOrganizationName("MKootstra");
    a.setWindowIcon(QIcon("qrc:/SimconnectServerIcon.ico"));

    QFontDatabase::addApplicationFont(":/Roboto-Mono-Variable.ttf");
    QGuiApplication::setFont(QFont("Roboto Mono", -1, QFont::Bold));

    qRegisterMetaType<QmlWaypointType>("QmlWaypointType");
    qmlRegisterUncreatableType<QmlWaypointTypeClass>("TypeEnums",
                                                     1,
                                                     0,
                                                     "WaypointType",
                                                     "Not creatable as it is an enum type");

    qRegisterMetaType<QmlWpAltitudeType>("QmlWpAltitudeType");
    qmlRegisterUncreatableType<QmlWpAltitudeTypeClass>("TypeEnums",
                                                     1,
                                                     0,
                                                     "WpAltitudeType",
                                                     "Not creatable as it is an enum type");

    qRegisterMetaType<io::network::ConnectionState>("ConnectionState");
    qmlRegisterUncreatableType<io::network::ConnectionStateClass>("TypeEnums",
                                                     1,
                                                     0,
                                                     "ConnectionState",
                                                     "Not creatable as it is an enum type");

    AircraftManager manager;
    FlightplanManager flightplanManager;
    ConnectionHandler connectionHandler;

    connectionHandler.init();

    flightplanManager.readFromFile("C:/Users/Mikey/AppData/Roaming/Microsoft Flight Simulator/CRJ_TUTORIAL_EDLP_EDDM.PLN");

    qmlRegisterSingletonInstance("Flightplan", 1, 0, "FlightplanManager", &flightplanManager);

    // MainWindow w;
    // w.show();

    QQmlApplicationEngine engine;

    engine.load("qrc:/main.qml");

    return a.exec();
}
