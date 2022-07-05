#include "AirspeedHandler.hpp"
#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"

#include <cmath>

namespace airspeed
{

QByteArray AirspeedHandler::processData(unsigned long *raw)
{
    DataStruct newData(*reinterpret_cast<DataStruct *>(raw));
    QByteArray dataToSend;

    d_previous.airspeed = newData.airspeed;
    util::appendData(PfdIdentifier::AIRSPEED, newData.airspeed, dataToSend);

    if (std::abs(d_previous.maxSpeed - newData.maxSpeed) >= 0.09)
    {
        d_previous.maxSpeed = newData.maxSpeed;
        util::appendData(PfdIdentifier::MAX_SPEED, newData.maxSpeed, dataToSend);
    }

    if (d_previous.trueAirspeed != newData.trueAirspeed)
    {
        d_previous.trueAirspeed = newData.trueAirspeed;
        util::appendData(PfdIdentifier::TRUE_AIRSPEED, newData.maxSpeed, dataToSend);
    }

    if (d_previous.refSpeed != newData.refSpeed)
    {
        d_previous.refSpeed = newData.refSpeed;
        util::appendData(PfdIdentifier::REF_SPEED, newData.maxSpeed, dataToSend);
    }

    return dataToSend;
}

}  // namespace airspeed
