#include "AirspeedHandler.hpp"
#include "common/dataIdentifiers.hpp"

#include <cmath>

namespace airspeed
{

QByteArray AirspeedHandler::processData(unsigned long *raw)
{
    DataStruct newData(*reinterpret_cast<DataStruct *>(raw));
    SimconnectIds id = SimconnectIds::AIRSPEED;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));

    d_previous.airspeed = newData.airspeed;
    dataToSend.append(reinterpret_cast<const char *>(&newData.airspeed), sizeof(newData.airspeed));

    if (std::abs(d_previous.maxSpeed - newData.maxSpeed) >= 0.09)
    {
        d_previous.maxSpeed = newData.maxSpeed;
        id = SimconnectIds::MAX_SPEED;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.maxSpeed), sizeof(newData.maxSpeed));
    }

    if (d_previous.trueAirspeed != newData.trueAirspeed)
    {
        d_previous.trueAirspeed = newData.trueAirspeed;
        id = SimconnectIds::TRUE_AIRSPEED;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.trueAirspeed), sizeof(newData.trueAirspeed));
    }

    if (d_previous.refSpeed != newData.refSpeed)
    {
        d_previous.refSpeed = newData.refSpeed;
        id = SimconnectIds::REF_SPEED;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.refSpeed), sizeof(newData.refSpeed));
    }

    return dataToSend;
}

}  // namespace airspeed
