#include "AltitudeHandler.hpp"
#include "common/simEnums.hpp"

#include <cmath>

namespace altitude
{

QByteArray AltitudeHandler::processData(unsigned long *raw)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));
    SimconnectIds id = SimconnectIds::ALTITUDE;
    QByteArray dataToSend;

    if (std::abs(d_previous.altitude - newData.altitude) >= 0.09)
    {
        d_previous.altitude = newData.altitude;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.altitude), sizeof(newData.altitude));
    }

    if (std::abs(d_previous.radarAltitude - newData.radarAltitude) >= 0.09)
    {
        d_previous.radarAltitude = newData.radarAltitude;
        id = SimconnectIds::RADAR_ALTITUDE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.radarAltitude), sizeof(newData.radarAltitude));
    }

    if (d_previous.refAltitude != newData.refAltitude)
    {
        d_previous.refAltitude = newData.refAltitude;
        id = SimconnectIds::REF_ALTITUDE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.refAltitude), sizeof(newData.refAltitude));
    }

    if (std::abs(d_previous.pressure - newData.pressure) >= 0.009)
    {
        d_previous.pressure = newData.pressure;
        id = SimconnectIds::PRESSURE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.pressure), sizeof(newData.pressure));
    }


    if (std::abs(d_previous.vspeed - newData.vspeed) >= 0.009)
    {
        d_previous.vspeed = newData.vspeed;
        id = SimconnectIds::VSPEED;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.vspeed), sizeof(newData.vspeed));
    }

    if (d_previous.refVspeed != newData.refVspeed)
    {
        d_previous.refVspeed = newData.refVspeed;
        id = SimconnectIds::REF_VSPEED;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.refVspeed), sizeof(newData.refVspeed));
    }

    if (newData.gpsDrivesNav1) [[likely]]  // gps
        handleGps(dataToSend, newData);
    else if (newData.autopilotNavSelected == 1)  // nav 1
        handleNav1(dataToSend, newData);
    else [[unlikely]]  // nav 2
        handleNav2(dataToSend, newData);


    return dataToSend;
}

}  // namespace altitude
