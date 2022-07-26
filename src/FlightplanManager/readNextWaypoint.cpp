#include "FlightplanManager.hpp"
#include <QXmlStreamReader>


void FlightplanManager::readNextWaypoint(QXmlStreamReader &xml)
{
    FlightPlanWaypoint newWp;

    newWp.ident = xml.attributes().value("id").toString();

    bool alt1Set = false;

    while (xml.readNextStartElement())
    {
        if (xml.name() == QLatin1String("ATCWaypointType"))
        {
            QString wpTypeString = xml.readElementText().simplified().toUpper();
            if (wpTypeString == "AIRPORT")
                newWp.wpType = WaypointType::AIRPORT;
            else if (wpTypeString == "INTERSECTION")
                newWp.wpType = WaypointType::INTERSECTION;
            else if (wpTypeString == "NDB")
                newWp.wpType = WaypointType::NDB;
            else if (wpTypeString == "VOR")
                newWp.wpType = WaypointType::VOR;
            else if (wpTypeString == "USER")
                newWp.wpType = WaypointType::USER;
            else if (wpTypeString == "ATC")
                newWp.wpType = WaypointType::ATC;
            else if (wpTypeString == "NONE")
                newWp.wpType = WaypointType::NONE;
        }
        else if (xml.name() == QLatin1String("WorldPosition"))
        {
            double wpAlt = 0;
            std::tie(newWp.position, wpAlt) = parsePosition(xml.readElementText().simplified().toUpper());

            if (!alt1Set)
                newWp.alt1 = std::lround(wpAlt);

        }
        else if (xml.name() == QLatin1String("ICAO"))
        {
            while (xml.readNextStartElement())
            {
                // icao overwrites id
                if (xml.name() == QLatin1String("ICAOIdent"))
                {
                    newWp.ident = xml.readElementText();
                    xml.skipCurrentElement();
                    break;
                }
            }

        }
        else if (xml.name() == QLatin1String("AltDescFP"))
        {
            QString altTypeString = xml.readElementText().simplified().toUpper();
            if (altTypeString == "AT_OR_ABOVE" || altTypeString == "ALT_DESC_AT_OR_ABOVE")
                newWp.altType = WpAltitudeType::AT_OR_ABOVE;
            else if (altTypeString == "AT_OR_BELOW" || altTypeString == "ALT_DESC_AT_OR_BELOW")
                newWp.altType = WpAltitudeType::AT_OR_BELOW;
            else if (altTypeString == "AT" || altTypeString == "ALT_DESC_AT")
                newWp.altType = WpAltitudeType::AT;
            else if (altTypeString == "IN_BETWEEN" || altTypeString == "ALT_DESC_IN_BETWEEN")
                newWp.altType = WpAltitudeType::BETWEEN;
        }
        else if (xml.name() == QLatin1String("Alt1FP"))
        {
            newWp.alt1 = lround(xml.readElementText().simplified().toDouble());
            alt1Set = true;
        }
        else if (xml.name() == QLatin1String("Alt2FP"))
        {
            newWp.alt2 = lround(xml.readElementText().simplified().toDouble());
        }
        else if (xml.name() == QLatin1String("SpeedMaxFP"))
        {
            newWp.speed = lround(xml.readElementText().simplified().toDouble());
        }
        else
            xml.skipCurrentElement();
    }

    if (newWp.wpType == WaypointType::ATC)
        newWp.ident += " (ATC)";

    d_waypoints.append(newWp);
}
