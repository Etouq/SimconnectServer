#include "AltitudeHandler.hpp"
#include "common/appendData.hpp"

#include <cmath>

namespace altitude
{

QByteArray AltitudeHandler::processData(unsigned long *raw)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));
    QByteArray dataToSend;

    if (std::abs(d_previous.altitude - newData.altitude) >= 0.09)
    {
        d_previous.altitude = newData.altitude;
        util::appendData(PfdIdentifier::ALTITUDE, newData.altitude, dataToSend);
    }

    if (std::abs(d_previous.radarAltitude - newData.radarAltitude) >= 0.09)
    {
        d_previous.radarAltitude = newData.radarAltitude;
        util::appendData(PfdIdentifier::RADAR_ALTITUDE, newData.radarAltitude, dataToSend);
    }

    if (d_previous.refAltitude != newData.refAltitude)
    {
        d_previous.refAltitude = newData.refAltitude;
        util::appendData(PfdIdentifier::REF_ALTITUDE, newData.refAltitude, dataToSend);
    }

    if (std::abs(d_previous.pressure - newData.pressure) >= 0.009)
    {
        d_previous.pressure = newData.pressure;
        util::appendData(PfdIdentifier::PRESSURE, newData.pressure, dataToSend);
    }


    if (std::abs(d_previous.vspeed - newData.vspeed) >= 0.009)
    {
        d_previous.vspeed = newData.vspeed;
        util::appendData(PfdIdentifier::VSPEED, newData.vspeed, dataToSend);
    }

    if (d_previous.refVspeed != newData.refVspeed)
    {
        d_previous.refVspeed = newData.refVspeed;
        util::appendData(PfdIdentifier::REF_VSPEED, newData.refVspeed, dataToSend);
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
