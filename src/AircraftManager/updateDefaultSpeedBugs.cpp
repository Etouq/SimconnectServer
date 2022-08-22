#include "AircraftManager.hpp"

#include <QFile>


void AircraftManager::updateDefaultSpeedBugs(const QList<definitions::ReferenceSpeed> &newBugs)
{
    if (d_currentDefinitionKey.isEmpty() || !d_definitions.contains(d_currentDefinitionKey))
        return;

    QFile file(d_dataRoot + "/Definitions/" + d_currentDefinitionKey + ".fdc");

    d_definitions[d_currentDefinitionKey].refSpeedDefaults = newBugs;

    if (file.open(QFile::WriteOnly | QIODevice::Truncate))
    {
        constexpr definitions::FileVersion version = definitions::FileVersion::V3;
        file.write(reinterpret_cast<const char *>(&version), sizeof(version));

        file.write(d_definitions.at(d_currentDefinitionKey).toBinary());
        file.close();
    }
}