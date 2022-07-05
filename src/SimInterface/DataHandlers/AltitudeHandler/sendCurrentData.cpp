#include "AltitudeHandler.hpp"
#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"

namespace altitude
{

QByteArray AltitudeHandler::sendCurrentData()
{
    QByteArray dataToSend;
    util::appendData(PfdIdentifier::ALTITUDE, d_previous.altitude, dataToSend);
    util::appendData(PfdIdentifier::RADAR_ALTITUDE, d_previous.radarAltitude, dataToSend);
    util::appendData(PfdIdentifier::REF_ALTITUDE, d_previous.refAltitude, dataToSend);

    d_previous.pressure = d_previous.pressure;
    util::appendData(PfdIdentifier::PRESSURE, d_previous.pressure, dataToSend);

    util::appendData(PfdIdentifier::VSPEED, d_previous.vspeed, dataToSend);

    d_previous.refVspeed = d_previous.refVspeed;
    util::appendData(PfdIdentifier::REF_VSPEED, d_previous.refVspeed, dataToSend);

    util::appendData(PfdIdentifier::VERT_DEV_MODE, d_vertDevMode, dataToSend);
    util::appendData(PfdIdentifier::VERT_DEV_VALUE, d_deviation, dataToSend);

    return dataToSend;
}

}  // namespace altitude
