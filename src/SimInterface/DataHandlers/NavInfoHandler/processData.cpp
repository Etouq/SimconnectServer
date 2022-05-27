#include "common/dataIdentifiers.hpp"
#include "NavInfoHandler.hpp"

#include <cmath>

namespace navinfo
{

QByteArray NavInfoHandler::processData(unsigned long *raw)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));

    SimconnectIds id = SimconnectIds::GPS_IS_ACTIVE_FLIGHTPLAN;
    QByteArray dataToSend;


    if (d_previous.gpsIsActiveFlightplan != newData.gpsIsActiveFlightplan)
    {
        d_previous.gpsIsActiveFlightplan = newData.gpsIsActiveFlightplan;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.gpsIsActiveFlightplan),
                          sizeof(newData.gpsIsActiveFlightplan));
    }
    if (d_previous.gpsIsDirectTo != newData.gpsIsDirectTo)
    {
        d_previous.gpsIsDirectTo = newData.gpsIsDirectTo;
        id = SimconnectIds::LEG_IS_DIRECT_TO;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.gpsIsDirectTo), sizeof(newData.gpsIsDirectTo));
    }


    if (d_previous.gpsWpEte != newData.gpsWpEte)
    {
        d_previous.gpsWpEte = newData.gpsWpEte;
        id = SimconnectIds::GPS_WP_ETE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.gpsWpEte), sizeof(newData.gpsWpEte));
    }

    if (d_previous.gpsEte != newData.gpsEte)
    {
        d_previous.gpsEte = newData.gpsEte;
        id = SimconnectIds::GPS_ETE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.gpsEte), sizeof(newData.gpsEte));
    }

    return dataToSend;
}

}  // namespace navinfo
