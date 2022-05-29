#include "flightplanreader.hpp"



FlightPlanWaypoint FlightplanReader::readWaypoint()
{
    FlightPlanWaypoint newWp;
    newWp.ident = flightPlanXml.attributes().value("id").toString();

    bool alt1Set = false;

    while (flightPlanXml.readNextStartElement())
    {
        if (flightPlanXml.name().toUtf8() == "ATCWaypointType")
        {
            QString wpTypeString = flightPlanXml.readElementText().toLower();
            if (wpTypeString == "airport")
                newWp.wpType = 0;
            else if (wpTypeString == "intersection")
                newWp.wpType = 1;
            else if (wpTypeString == "ndb")
                newWp.wpType = 2;
            else if (wpTypeString == "vor")
                newWp.wpType = 4;
            else if (wpTypeString == "user")
                newWp.wpType = 3;
            else if (wpTypeString == "atc")
            {
                newWp.wpType = 3;

                newWp.ident += " (ATC)";
            }
            else if (wpTypeString == "none")
            {
                newWp.wpType = 3;
            }
        }
        else if (flightPlanXml.name().toUtf8() == "WorldPosition")
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
        else if (flightPlanXml.name().toUtf8() == "AltDescFP")
        {
            QString altTypeString = flightPlanXml.readElementText().simplified().toUpper();
            if (altTypeString == "AT_OR_ABOVE" || altTypeString == "ALT_DESC_AT_OR_ABOVE")
                newWp.altType = 1;
            else if (altTypeString == "AT_OR_BELOW" || altTypeString == "ALT_DESC_AT_OR_BELOW")
                newWp.altType = 2;
            else if (altTypeString == "AT" || altTypeString == "ALT_DESC_AT")
                newWp.altType = 0;
            else if (altTypeString == "IN_BETWEEN" || altTypeString == "ALT_DESC_IN_BETWEEN")
                newWp.altType = 3;
        }
        else if (flightPlanXml.name().toUtf8() == "Alt1FP")
        {
            newWp.alt1 = lround(flightPlanXml.readElementText().simplified().toFloat());
            alt1Set = true;
        }
        else if (flightPlanXml.name().toUtf8() == "Alt2FP")
        {
            newWp.alt2 = lround(flightPlanXml.readElementText().simplified().toFloat());
        }
        else
            flightPlanXml.skipCurrentElement();
    }


    return newWp;
}
