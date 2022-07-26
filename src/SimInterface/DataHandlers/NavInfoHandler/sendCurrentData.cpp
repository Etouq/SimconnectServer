#include "common/dataIdentifiers.hpp"
#include "NavInfoHandler.hpp"


namespace navinfo
{

std::string NavInfoHandler::sendCurrentData()
{
    std::string dataToSend;
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::GPS_IS_ACTIVE_FLIGHTPLAN) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.gpsIsActiveFlightplan), sizeof(d_previous.gpsIsActiveFlightplan));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::LEG_IS_DIRECT_TO) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.gpsIsDirectTo), sizeof(d_previous.gpsIsDirectTo));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::GPS_WP_ETE) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.gpsWpEte), sizeof(d_previous.gpsWpEte));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::GPS_DEST_ETE) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.gpsEte), sizeof(d_previous.gpsEte));


    return dataToSend;
}

}  // namespace navinfo
