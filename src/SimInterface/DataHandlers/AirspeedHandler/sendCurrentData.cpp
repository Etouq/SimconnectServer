#include "AirspeedHandler.hpp"
#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"

namespace airspeed
{

QByteArray AirspeedHandler::sendCurrentData()
{
    QByteArray dataToSend;
    util::appendData(PfdIdentifier::AIRSPEED, d_previous.airspeed, dataToSend);
    util::appendData(PfdIdentifier::MAX_SPEED, d_previous.maxSpeed, dataToSend);
    util::appendData(PfdIdentifier::TRUE_AIRSPEED, d_previous.trueAirspeed, dataToSend);
    util::appendData(PfdIdentifier::REF_SPEED, d_previous.refSpeed, dataToSend);

    return dataToSend;
}

}  // namespace airspeed
