#include "FlightplanManager.hpp"

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

void FlightplanManager::storeFlightplan()
{
    QDir dataDir(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
                 + "/AppData/Roaming/MKootstra/Simconnect Server");

    const std::vector<FlightPlanWaypoint> &waypoints = d_wpModel.data();

    if (waypoints.empty())
    {
        if (dataDir.exists("flightplan.json"))
        {
            dataDir.remove("flightplan.json");
        }
        return;
    }

    QJsonArray jsonWaypoints;

    for (const FlightPlanWaypoint &wp : waypoints)
    {
        jsonWaypoints.append(QJsonObject(
          { { "position", QJsonObject({
                { "latitude", wp.position.latitude() },
                { "longitude", wp.position.longitude() } }) },
            { "alt1", wp.alt1 },
            { "alt2", wp.alt2 },
            { "ident", wp.ident },
            { "wpType", static_cast<int>(wp.wpType) },
            { "altType", static_cast<int>(wp.altType) },
            { "speed", wp.speed } }));
    }

    QFile file(dataDir.canonicalPath() + "/flightplan.json");

    if (file.open(QFile::WriteOnly | QFile::Truncate))
    {
        file.write(QJsonDocument(jsonWaypoints).toJson(QJsonDocument::Indented));

        file.close();
    }
}