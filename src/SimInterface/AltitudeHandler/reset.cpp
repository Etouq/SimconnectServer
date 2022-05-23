#include "../SimInterface.hpp"
#include "AltitudeHandler.hpp"
#include "common/dataIdentifiers.hpp"

void AltitudeHandler::reset()
{
    d_previous = DataStruct();

    SimconnectIds id = SimconnectIds::ALTITUDE;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.altitude), sizeof(d_previous.altitude));

    id = SimconnectIds::RADAR_ALTITUDE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.radar_altitude), sizeof(d_previous.radar_altitude));

    id = SimconnectIds::REF_ALTITUDE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.ref_altitude), sizeof(d_previous.ref_altitude));

    d_previous.pressure = d_previous.pressure;
    id = SimconnectIds::PRESSURE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.pressure), sizeof(d_previous.pressure));

    id = SimconnectIds::VSPEED;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.vspeed), sizeof(d_previous.vspeed));

    d_previous.ref_vspeed = d_previous.ref_vspeed;
    id = SimconnectIds::REF_VSPEED;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.ref_vspeed), sizeof(d_previous.ref_vspeed));


    d_lastVertMode = 0;
    id = SimconnectIds::VERT_DEV_MODE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastVertMode), sizeof(d_lastVertMode));

    id = SimconnectIds::VERT_DEV_VALUE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.nav1_gsi), sizeof(d_previous.nav1_gsi));

    emit d_parent->sendData(dataToSend);
}
