#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"
#include "NavInfoHandler.hpp"

#include <cmath>

namespace navinfo
{

QByteArray NavInfoHandler::processData(unsigned long *raw)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));

    QByteArray dataToSend;

    if (d_previous.gpsIsActiveFlightplan != newData.gpsIsActiveFlightplan)
    {
        d_previous.gpsIsActiveFlightplan = newData.gpsIsActiveFlightplan;
        util::appendData(PfdIdentifier::GPS_IS_ACTIVE_FLIGHTPLAN, newData.gpsIsActiveFlightplan, dataToSend);
    }
    if (d_previous.gpsIsDirectTo != newData.gpsIsDirectTo)
    {
        d_previous.gpsIsDirectTo = newData.gpsIsDirectTo;
        util::appendData(PfdIdentifier::LEG_IS_DIRECT_TO, newData.gpsIsDirectTo, dataToSend);
    }


    if (d_previous.gpsWpEte != newData.gpsWpEte)
    {
        d_previous.gpsWpEte = newData.gpsWpEte;
        util::appendData(MfdIdentifier::GPS_WP_ETE, newData.gpsWpEte, dataToSend);
    }

    if (d_previous.gpsEte != newData.gpsEte)
    {
        d_previous.gpsEte = newData.gpsEte;
        util::appendData(MfdIdentifier::GPS_DEST_ETE, newData.gpsEte, dataToSend);
    }

    return dataToSend;
}

}  // namespace navinfo
