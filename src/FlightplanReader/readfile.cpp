#include "flightplanreader.hpp"

#include <QFile>


QList<FlightPlanWaypoint> FlightplanReader::readFile(QFile &file)
{
    flightPlanXml.setDevice(&file);

    QList<FlightPlanWaypoint> flightPlanList;

    while (!flightPlanXml.atEnd())
    {
        if (flightPlanXml.readNextStartElement())
        {
            if (flightPlanXml.name() == QLatin1String("FlightPlan.FlightPlan"))
            {
                while (flightPlanXml.readNextStartElement())
                {
                    if (flightPlanXml.name() == QLatin1String("ATCWaypoint"))
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
