#include "FlightplanManager.hpp"

#include <limits>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

void FlightplanManager::readFromJson()
{
    qDebug() << "read from json called";
    QDir dataDir(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
                 + "/AppData/Roaming/MKootstra/Simconnect Server");

    if (!dataDir.exists("flightplan.json"))
    {
        qDebug() << "file does not exist";
        return;
    }


    QFile file(dataDir.canonicalPath() + "/flightplan.json");

    if (file.open(QFile::ReadOnly))
    {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        if (!doc.isArray())
        {
            qDebug() << "file is not an array";
            return;
        }

        std::vector<FlightPlanWaypoint> waypoints;

        QJsonArray jsonWaypoints = doc.array();

        for (const QJsonValue &entry : jsonWaypoints)
        {
            if (!entry.isObject())
            {
                qDebug() << "entry is not an object";
                return;
            }

            const QJsonObject &waypoint = entry.toObject();

            if (!waypoint.contains("position") || !waypoint["position"].isObject())
            {
                qDebug() << "entry does not contain an object 'position'";
                return;
            }

            const QJsonObject &position = waypoint["position"].toObject();

            if (!position.contains("latitude")
                || !position.contains("longitude")
                || !waypoint.contains("alt1")
                || !waypoint.contains("alt2")
                || !waypoint.contains("ident")
                || !waypoint.contains("wpType")
                || !waypoint.contains("altType")
                || !waypoint.contains("speed")
                || !position["latitude"].isDouble()
                || !position["longitude"].isDouble()
                || !waypoint["alt1"].isDouble()
                || !waypoint["alt2"].isDouble()
                || !waypoint["ident"].isString()
                || !waypoint["wpType"].isDouble()
                || !waypoint["altType"].isDouble()
                || !waypoint["speed"].isDouble())
            {
                qDebug() << "missing or incorrect properties";
                return;
            }

            const double latitude = position["latitude"].toDouble();
            const double longitude = position["longitude"].toDouble();
            const int32_t alt1 = waypoint["alt1"].toInt(std::numeric_limits<int32_t>::min());
            const int32_t alt2 = waypoint["alt2"].toInt(std::numeric_limits<int32_t>::min());
            const int wpTypeInt = waypoint["wpType"].toInt(-1);
            const int altTypeInt = waypoint["altType"].toInt(-1);
            const int speedInt = waypoint["speed"].toInt(std::numeric_limits<int32_t>::max());

            if (latitude > 90 || latitude < -90
                || longitude > 180 || longitude < -180
                || alt1 == std::numeric_limits<int32_t>::min()
                || alt2 == std::numeric_limits<int32_t>::min()
                || wpTypeInt < 0 || wpTypeInt > 6
                || altTypeInt < 0 || altTypeInt > 4
                || speedInt == std::numeric_limits<int16_t>::max())
            {
                qDebug() << "incorrect property values";
                return;
            }

            waypoints.emplace_back(FlightPlanWaypoint{ QGeoCoordinate(latitude, longitude),
                                                       alt1,
                                                       alt2,
                                                       waypoint["ident"].toString(),
                                                       static_cast<WaypointType>(wpTypeInt),
                                                       static_cast<WpAltitudeType>(altTypeInt),
                                                       static_cast<int16_t>(speedInt) });
        }

        d_wpModel.overwrite(waypoints);
    }
}
