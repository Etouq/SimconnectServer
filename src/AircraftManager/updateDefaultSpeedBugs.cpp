#include "AircraftManager.hpp"

#include <QDir>
#include <QFile>


void AircraftManager::updateDefaultSpeedBugs(const QList<definitions::ReferenceSpeed> &newBugs)
{
    QDir dataDir(d_dataRoot + "/Definitions");
    QFile file(dataDir.canonicalPath() + d_currentDefinitionKey + ".def");

    d_definitions[d_currentDefinitionKey].refSpeedDefaults = newBugs;

    if (file.open(QFile::WriteOnly | QIODevice::Truncate))
    {
        constexpr definitions::FileVersion version = definitions::FileVersion::V3;
        file.write(reinterpret_cast<const char *>(&version), sizeof(version));

        file.write(d_definitions.at(d_currentDefinitionKey).toBinary());
        file.close();
    }
}