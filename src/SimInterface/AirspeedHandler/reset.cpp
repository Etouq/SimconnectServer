#include "../SimInterface.hpp"
#include "AirspeedHandler.hpp"
#include "common/dataIdentifiers.hpp"

void AirspeedHandler::reset()
{
    d_previous = DataStruct();

    SimconnectIds id = SimconnectIds::AIRSPEED;
    QByteArray dataToSend(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.airspeed), sizeof(d_previous.airspeed));

    id = SimconnectIds::MAX_SPEED;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.max_speed), sizeof(d_previous.max_speed));

    id = SimconnectIds::TRUE_AIRSPEED;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.true_airspeed), sizeof(d_previous.true_airspeed));

    id = SimconnectIds::REF_SPEED;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.ref_speed), sizeof(d_previous.ref_speed));

    emit d_parent->sendData(dataToSend);
}
