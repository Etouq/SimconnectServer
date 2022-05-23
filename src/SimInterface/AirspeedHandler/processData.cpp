#include "../SimInterface.hpp"
#include "AirspeedHandler.hpp"
#include "common/dataIdentifiers.hpp"

#include <cmath>

void AirspeedHandler::processData(unsigned long *raw)
{
    DataStruct newData(*reinterpret_cast<DataStruct *>(raw));
    SimconnectIds id = SimconnectIds::AIRSPEED;
    QByteArray dataToSend(reinterpret_cast<char *>(&id), sizeof(id));

    d_previous.airspeed = newData.airspeed;
    dataToSend.append(reinterpret_cast<const char *>(&newData.airspeed), sizeof(d_previous.airspeed));

    if (std::abs(d_previous.max_speed - newData.max_speed) >= 0.09)
    {
        d_previous.max_speed = newData.max_speed;
        id = SimconnectIds::MAX_SPEED;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.max_speed), sizeof(newData.max_speed));
    }

    if (d_previous.true_airspeed != newData.true_airspeed)
    {
        d_previous.true_airspeed = newData.true_airspeed;
        id = SimconnectIds::TRUE_AIRSPEED;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.true_airspeed), sizeof(newData.true_airspeed));
    }

    if (d_previous.ref_speed != newData.ref_speed)
    {
        d_previous.ref_speed = newData.ref_speed;
        id = SimconnectIds::REF_SPEED;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.ref_speed), sizeof(newData.ref_speed));
    }

    emit d_parent->sendData(dataToSend);
}
