#include "common/dataIdentifiers.hpp"
#include "NavInfoHandler.hpp"


namespace navinfo
{

QByteArray NavInfoHandler::sendCurrentData()
{
    SimconnectIds id = SimconnectIds::GPS_IS_ACTIVE_FLIGHTPLAN;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.gpsIsActiveFlightplan),
                      sizeof(d_previous.gpsIsActiveFlightplan));

    id = SimconnectIds::LEG_IS_DIRECT_TO;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.gpsIsDirectTo), sizeof(d_previous.gpsIsDirectTo));

    id = SimconnectIds::GPS_WP_ETE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.gpsWpEte), sizeof(d_previous.gpsWpEte));

    id = SimconnectIds::GPS_ETE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.gpsEte), sizeof(d_previous.gpsEte));


    return dataToSend;
}

}  // namespace navinfo
