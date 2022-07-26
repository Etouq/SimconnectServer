#include "AltitudeHandler.hpp"

#include <cmath>

namespace altitude
{

std::string AltitudeHandler::processData(unsigned long *raw)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));
    std::string dataToSend;

    if (std::abs(d_previous.altitude - newData.altitude) >= 0.09)
    {
        d_previous.altitude = newData.altitude;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::ALTITUDE) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.altitude), sizeof(newData.altitude));
    }

    if (std::abs(d_previous.radarAltitude - newData.radarAltitude) >= 0.09)
    {
        d_previous.radarAltitude = newData.radarAltitude;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::RADAR_ALTITUDE) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.radarAltitude), sizeof(newData.radarAltitude));
    }

    if (d_previous.refAltitude != newData.refAltitude)
    {
        d_previous.refAltitude = newData.refAltitude;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::REF_ALTITUDE) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.refAltitude), sizeof(newData.refAltitude));
    }

    if (std::abs(d_previous.pressure - newData.pressure) >= 0.009)
    {
        d_previous.pressure = newData.pressure;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::PRESSURE) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.pressure), sizeof(newData.pressure));
    }


    if (std::abs(d_previous.vspeed - newData.vspeed) >= 0.009)
    {
        d_previous.vspeed = newData.vspeed;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::VSPEED) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.vspeed), sizeof(newData.vspeed));
    }

    if (d_previous.refVspeed != newData.refVspeed)
    {
        d_previous.refVspeed = newData.refVspeed;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::REF_VSPEED) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.refVspeed), sizeof(newData.refVspeed));
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
