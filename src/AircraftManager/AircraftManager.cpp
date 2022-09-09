#include "AircraftManager.hpp"
#include <QStandardPaths>
#include <QDir>

AircraftManager::AircraftManager()
{
    d_dataRoot =
      QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/AppData/Roaming/Flight Display Companion";



    QSettings settings;

    if (settings.contains("lastChosenDefinition"))
    {
        d_currentDefinitionKey = settings.value("lastChosenDefinition").toString();
    }

    loadDefinitions();
}
