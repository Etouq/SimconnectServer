#include "main.hpp"

#include <QApplication>
#include <QFile>
#include <QFontDatabase>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QSurfaceFormat>
#include <QStandardPaths>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qSetMessagePattern("[%{time HH:mm:ss.zzz} %{type}]%{if-category} %{category}: %{endif} - %{message}");

    QApplication a(argc, argv);

    // set basic application data for settings object
    a.setOrganizationName("MKootstra");
    a.setApplicationName("simconnectServer");
    a.setApplicationDisplayName("Simconnect Server");

    // set icon
    a.setWindowIcon(QIcon(":/SimconnectServerIcon.ico"));

    // add application font
    QFontDatabase::addApplicationFont(":/Roboto-Mono-Variable.ttf");
    QGuiApplication::setFont(QFont("Roboto Mono", -1, QFont::Bold));

    // add slight anti aliasing to reduce jagged edges on flightplan leg arrow
    QSurfaceFormat format;
    format.setSamples(2);
    QSurfaceFormat::setDefaultFormat(format);

    // make sure necessary directories exist
    QDir dataDirs(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
    dataDirs.mkpath("AppData/Roaming/Flight Display Companion/Definitions");
    dataDirs.mkpath("AppData/Roaming/Flight Display Companion/Thumbnails");

    // copy definitions for first time setup
    QDir dir(QDir::currentPath() + "/Definitions Temp");
    if (dir.exists())
    {
        QString dataRoot = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/AppData/Roaming/Flight Display Companion";
        dir.cd("Definitions");

        QFileInfoList files = dir.entryInfoList({"*.fdc"}, QDir::Files | QDir::Readable);

        for (const QFileInfo &fileInfo : files)
        {
            QFile::copy(fileInfo.canonicalFilePath(), dataRoot + "/Definitions/" + fileInfo.fileName());
        }

        dir.cdUp();
        dir.cd("Thumbnails");

        files = dir.entryInfoList({"*.png"}, QDir::Files | QDir::Readable);

        for (const QFileInfo &fileInfo : files)
        {
            QFile::copy(fileInfo.canonicalFilePath(), dataRoot + "/Thumbnails/" + fileInfo.fileName());
        }

        dir.cdUp();

        dir.removeRecursively();

    }


    // application state & data managers
    AircraftManager aircraftManager;
    ConnectionHandler connectionHandler;
    FlightplanManager flightplanManager;
    sim::SimThreadManager simManager(aircraftManager.getCurrentDefinition().toConfig());

    setupQml(&aircraftManager, &connectionHandler, &flightplanManager, &simManager);
    connectSignals(&aircraftManager, &connectionHandler, &flightplanManager, &simManager);

    QObject::connect(&a, &QApplication::aboutToQuit, &flightplanManager, &FlightplanManager::storeFlightplan);

    connectionHandler.init();

    // init for testing
    // flightplanManager.readFromFile(
    //   "C:/Users/Mikey/AppData/Roaming/Microsoft Flight Simulator/CRJ_TUTORIAL_EDLP_EDDM.PLN");

    QQmlApplicationEngine engine;

    engine.load("qrc:/main.qml");

    return a.exec();
}
