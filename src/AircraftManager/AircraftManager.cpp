#include "AircraftManager.hpp"
#include <QStandardPaths>
#include <QDir>
#include <QQmlEngine>

AircraftManager::AircraftManager()
{
    d_dataRoot = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/AppData/Roaming/MKootstra/Simconnect Server";

    QDir dataDirs(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
    dataDirs.mkpath("/AppData/Roaming/MKootstra/Simconnect Server/Definitions");
    dataDirs.mkpath("/AppData/Roaming/MKootstra/Simconnect Server/Thumbnails");

    loadDefinitions();

    qmlRegisterSingletonInstance("SimconnectServer", 1, 0, "AircraftManager", this);
}
