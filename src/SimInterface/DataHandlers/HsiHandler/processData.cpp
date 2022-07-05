#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"
#include "common/simEnums.hpp"
#include "HsiHandler.hpp"

#include <cmath>

namespace hsi
{

QByteArray HsiHandler::processData(unsigned long *raw)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));

    QByteArray dataToSend;


    if (std::abs(d_previous.rotation - newData.rotation) >= 0.0009)
    {
        d_previous.rotation = newData.rotation;
        util::appendData(PfdIdentifier::ROTATION, newData.rotation, dataToSend);
    }
    if (std::abs(d_previous.heading - newData.heading) >= 0.0009)
    {
        d_previous.heading = newData.heading;
        util::appendData(PfdIdentifier::HEADING, newData.heading, dataToSend);
    }
    if (std::abs(d_previous.turnRate - newData.turnRate) >= 0.0009)
    {
        d_previous.turnRate = newData.turnRate;
        util::appendData(PfdIdentifier::TURN_RATE, newData.turnRate, dataToSend);
    }
    if (std::abs(d_previous.currentTrack - newData.currentTrack) >= 0.0009)
    {
        d_previous.currentTrack = newData.currentTrack;
        util::appendData(PfdIdentifier::CURRENT_TRACK, newData.currentTrack, dataToSend);
    }

    if (std::abs(d_previous.gpsWpDesiredTrack - newData.gpsWpDesiredTrack) >= 0.009)
    {
        d_previous.gpsWpDesiredTrack = newData.gpsWpDesiredTrack;
        util::appendData(MfdIdentifier::GPS_WP_DTK, newData.gpsWpDesiredTrack, dataToSend);
    }

    util::appendData(MfdIdentifier::COORDINATES, newData.currLat, dataToSend);
    dataToSend.append(reinterpret_cast<const char *>(&newData.currLon), sizeof(newData.currLon));

    d_previous.currLat = newData.currLat;
    d_previous.currLon = newData.currLon;

    if (std::abs(d_previous.trueHeading - newData.trueHeading) >= 0.0009)
    {
        d_previous.trueHeading = newData.trueHeading;
        util::appendData(MfdIdentifier::TRUE_HEADING, newData.trueHeading, dataToSend);
    }


    // gps
    if (newData.gpsDrivesNav1
          && (!newData.autopilotApproachHold || newData.gpsApproachApproachType == simenums::ApproachType::RNAV)
        || newData.autopilotNavSelected == 0) [[likely]]
    {
        handleGps(dataToSend, newData);
    }
    else if (newData.autopilotNavSelected == 1)  // nav1
    {
        if (newData.tacanDrivesNav1)
        {
            handleNav1Tacan(dataToSend, newData);
        }
        else
        {
            handleNav1(dataToSend, newData);
        }
    }
    else [[unlikely]]  // nav2
    {
        if (newData.tacanDrivesNav1)
        {
            handleNav2Tacan(dataToSend, newData);
        }
        else
        {
            handleNav2(dataToSend, newData);
        }
    }


    return dataToSend;
}

}  // namespace hsi