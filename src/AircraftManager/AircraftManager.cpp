#include "AircraftManager.hpp"
#include <QStandardPaths>
#include <QDir>

AircraftManager::AircraftManager()
{
    d_dataRoot = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/AppData/Roaming/MKootstra/Simconnect Server";

    QDir dataDirs(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
    dataDirs.mkpath("/AppData/Roaming/MKootstra/Simconnect Server/Definitions");
    dataDirs.mkpath("/AppData/Roaming/MKootstra/Simconnect Server/Thumbnails");

    loadDefinitions();

    QSettings settings;

    if (settings.contains("lastChosenDefinition"))
    {
        d_currentDefinitionKey = settings.value("lastChosenDefinition").toString();
    }
}