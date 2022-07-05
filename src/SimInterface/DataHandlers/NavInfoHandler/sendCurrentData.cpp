#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"
#include "NavInfoHandler.hpp"


namespace navinfo
{

QByteArray NavInfoHandler::sendCurrentData()
{
    QByteArray dataToSend;
    util::appendData(PfdIdentifier::GPS_IS_ACTIVE_FLIGHTPLAN, d_previous.gpsIsActiveFlightplan, dataToSend);

    util::appendData(PfdIdentifier::LEG_IS_DIRECT_TO, d_previous.gpsIsDirectTo, dataToSend);

    util::appendData(MfdIdentifier::GPS_WP_ETE, d_previous.gpsWpEte, dataToSend);

    util::appendData(MfdIdentifier::GPS_DEST_ETE, d_previous.gpsEte, dataToSend);


    return dataToSend;
}

}  // namespace navinfo
