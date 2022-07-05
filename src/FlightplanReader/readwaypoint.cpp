#include "flightplanreader.hpp"



FlightPlanWaypoint FlightplanReader::readWaypoint()
{
    FlightPlanWaypoint newWp;
    newWp.ident = flightPlanXml.attributes().value("id").toString();

    bool alt1Set = false;

    while (flightPlanXml.readNextStartElement())
    {
        if (flightPlanXml.name() == QLatin1String("ATCWaypointType"))
        {
            QString wpTypeString = flightPlanXml.readElementText().toLower();
            if (wpTypeString == "airport")
                newWp.wpType = WaypointType::AIRPORT;
            else if (wpTypeString == "intersection")
                newWp.wpType = WaypointType::INTERSECTION;
            else if (wpTypeString == "ndb")
                newWp.wpType = WaypointType::NDB;
            else if (wpTypeString == "vor")
                newWp.wpType = WaypointType::VOR;
            else if (wpTypeString == "user")
                newWp.wpType = WaypointType::USER;
            else if (wpTypeString == "atc")
            {
                newWp.wpType = WaypointType::ATC;

                newWp.ident += " (ATC)";
            }
            else if (wpTypeString == "none")
            {
                newWp.wpType = WaypointType::NONE;
            }
        }
        else if (flightPlanXml.name() == QLatin1String("WorldPosition"))
        {
            QString posString = flightPlanXml.readElementText().simplified().toUpper();

            if (QRegularExpressionMatch match = llaRegExp.match(posString); match.hasMatch())
            {
                bool northLat = match.captured(latDirIdx) != "S";
                int latDeg = match.captured(latDegIdx).toInt();
                int latMin = match.captured(latMinIdx).toInt();
                float latSec = match.captured(latSecIdx).toFloat();

                bool eastLon = match.captured(lonDirIdx) != "W";
                int lonDeg = match.captured(lonDegIdx).toInt();
                int lonMin = match.captured(lonMinIdx).toInt();
                float lonSec = match.captured(lonSecIdx).toFloat();

                double lat = (latDeg + latMin / 60.0 + latSec / 3600.0) * (northLat ? 1.0 : -1.0);
                double lon = (lonDeg + lonMin / 60.0 + lonSec / 3600.0) * (eastLon ? 1.0 : -1.0);
                newWp.position = QGeoCoordinate(lat, lon);
                if (!alt1Set)
                    newWp.alt1 = lround(QString(match.captured(altPosIdx) + match.captured(altIdx)).toFloat());
            }
        }
        else if (flightPlanXml.name() == QLatin1String("AltDescFP"))
        {
            QString altTypeString = flightPlanXml.readElementText().simplified().toUpper();
            if (altTypeString == "AT_OR_ABOVE" || altTypeString == "ALT_DESC_AT_OR_ABOVE")
                newWp.altType = WpAltitudeType::AT_OR_ABOVE;
            else if (altTypeString == "AT_OR_BELOW" || altTypeString == "ALT_DESC_AT_OR_BELOW")
                newWp.altType = WpAltitudeType::AT_OR_BELOW;
            else if (altTypeString == "AT" || altTypeString == "ALT_DESC_AT")
                newWp.altType = WpAltitudeType::AT;
            else if (altTypeString == "IN_BETWEEN" || altTypeString == "ALT_DESC_IN_BETWEEN")
                newWp.altType = WpAltitudeType::BETWEEN;
        }
        else if (flightPlanXml.name() == QLatin1String("Alt1FP"))
        {
            newWp.alt1 = lround(flightPlanXml.readElementText().simplified().toFloat());
            alt1Set = true;
        }
        else if (flightPlanXml.name() == QLatin1String("Alt2FP"))
        {
            newWp.alt2 = lround(flightPlanXml.readElementText().simplified().toFloat());
        }
        else
            flightPlanXml.skipCurrentElement();
    }


    return newWp;
}
