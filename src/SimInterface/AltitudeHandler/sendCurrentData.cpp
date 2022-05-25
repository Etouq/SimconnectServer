#include "../SimInterface.hpp"
#include "AltitudeHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace altitude
{

void AltitudeHandler::sendCurrentData()
{
    SimconnectIds id = SimconnectIds::ALTITUDE;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.altitude), sizeof(d_previous.altitude));

    id = SimconnectIds::RADAR_ALTITUDE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.radarAltitude), sizeof(d_previous.radarAltitude));

    id = SimconnectIds::REF_ALTITUDE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.refAltitude), sizeof(d_previous.refAltitude));

    d_previous.pressure = d_previous.pressure;
    id = SimconnectIds::PRESSURE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.pressure), sizeof(d_previous.pressure));

    id = SimconnectIds::VSPEED;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.vspeed), sizeof(d_previous.vspeed));

    d_previous.refVspeed = d_previous.refVspeed;
    id = SimconnectIds::REF_VSPEED;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.refVspeed), sizeof(d_previous.refVspeed));

    id = SimconnectIds::VERT_DEV_MODE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastVertMode), sizeof(d_lastVertMode));

    id = SimconnectIds::VERT_DEV_VALUE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_deviation), sizeof(d_deviation));


    emit d_parent->sendData(dataToSend);
}

}  // namespace altitude
