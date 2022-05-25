#include "../SimInterface.hpp"
#include "AirspeedHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace airspeed
{

void AirspeedHandler::sendCurrentData()
{
    SimconnectIds id = SimconnectIds::AIRSPEED;
    QByteArray dataToSend(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.airspeed), sizeof(d_previous.airspeed));

    id = SimconnectIds::MAX_SPEED;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.maxSpeed), sizeof(d_previous.maxSpeed));

    id = SimconnectIds::TRUE_AIRSPEED;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.trueAirspeed), sizeof(d_previous.trueAirspeed));

    id = SimconnectIds::REF_SPEED;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.refSpeed), sizeof(d_previous.refSpeed));

    emit d_parent->sendData(dataToSend);
}

}  // namespace airspeed
