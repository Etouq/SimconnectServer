#include "flightplanreader.h"
#include "common/dataIdentifiers.h"
#include <QFile>

FlightplanReader::FlightplanReader()
{

}


FlightPlanWaypoint FlightplanReader::readWaypoint()
{
    FlightPlanWaypoint newWp;
    newWp.ident = flightPlanXml.attributes().value("id").toString();

    bool alt1Set = false;

    while (flightPlanXml.readNextStartElement())
    {
        if (flightPlanXml.name() == "ATCWaypointType")
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
        else if (flightPlanXml.name() == "WorldPosition")
        {
            QString posString = flightPlanXml.readElementText().simplified().toUpper();

            if(QRegularExpressionMatch match = llaRegExp.match(posString); match.hasMatch())
            {
                bool northLat = match.captured(1) != "S";
                int latDeg = match.captured(2).toInt();
                int latMin = match.captured(3).toInt();
                float latSec = match.captured(4).toFloat();

                bool eastLon = match.captured(5) != "W";
                int lonDeg = match.captured(6).toInt();
                int lonMin = match.captured(7).toInt();
                float lonSec = match.captured(8).toFloat();

                double lat = (latDeg + latMin / 60.0 + latSec / 3600.0) * (northLat ? 1.0 : -1.0);
                double lon = (lonDeg + lonMin / 60.0 + lonSec / 3600.0) * (eastLon ? 1.0 : -1.0);
                newWp.position = QGeoCoordinate(lat, lon);
                if (!alt1Set)
                    newWp.alt1 = lround(QString(match.captured(9) + match.captured(10)).toFloat());

            }
        }
        else if (flightPlanXml.name() == "AltDescFP")
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
        else if (flightPlanXml.name() == "Alt1FP")
        {
            newWp.alt1 = lround(flightPlanXml.readElementText().simplified().toFloat());
            alt1Set = true;
        }
        else if (flightPlanXml.name() == "Alt2FP")
        {
            newWp.alt2 = lround(flightPlanXml.readElementText().simplified().toFloat());
        }
        else
            flightPlanXml.skipCurrentElement();
    }



    return newWp;
}



QList<FlightPlanWaypoint> FlightplanReader::readFlightPlanFile(QFile &file)
{
    flightPlanXml.setDevice(&file);

    QList<FlightPlanWaypoint> flightPlanList;

    while (!flightPlanXml.atEnd())
    {
        if(flightPlanXml.readNextStartElement())
        {
            if (flightPlanXml.name() == "FlightPlan.FlightPlan")
            {
                while (flightPlanXml.readNextStartElement()) {
                    if (flightPlanXml.name() == "ATCWaypoint")
                        flightPlanList.append(readWaypoint());
                    else
                        flightPlanXml.skipCurrentElement();
                }
            }
            /*else
                flightPlanXml.skipCurrentElement();*/
        }
    }


    return flightPlanList;
}



































