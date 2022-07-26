#include "common/dataIdentifiers.hpp"
#include "NavInfoHandler.hpp"

#include <cmath>

namespace navinfo
{

std::string NavInfoHandler::processData(unsigned long *raw)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));

    std::string dataToSend;

    if (d_previous.gpsIsActiveFlightplan != newData.gpsIsActiveFlightplan)
    {
        d_previous.gpsIsActiveFlightplan = newData.gpsIsActiveFlightplan;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::GPS_IS_ACTIVE_FLIGHTPLAN) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.gpsIsActiveFlightplan), sizeof(newData.gpsIsActiveFlightplan));
    }
    if (d_previous.gpsIsDirectTo != newData.gpsIsDirectTo)
    {
        d_previous.gpsIsDirectTo = newData.gpsIsDirectTo;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::LEG_IS_DIRECT_TO) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.gpsIsDirectTo), sizeof(newData.gpsIsDirectTo));
    }


    if (d_previous.gpsWpEte != newData.gpsWpEte)
    {
        d_previous.gpsWpEte = newData.gpsWpEte;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::GPS_WP_ETE) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.gpsWpEte), sizeof(newData.gpsWpEte));
    }

    if (d_previous.gpsEte != newData.gpsEte)
    {
        d_previous.gpsEte = newData.gpsEte;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::GPS_DEST_ETE) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.gpsEte), sizeof(newData.gpsEte));
    }

    return dataToSend;
}

}  // namespace navinfo
