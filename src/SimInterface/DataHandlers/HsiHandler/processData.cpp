#include "common/dataIdentifiers.hpp"
#include "common/simEnums.hpp"
#include "HsiHandler.hpp"

#include <cmath>
#include <QDebug>

namespace hsi
{

std::string HsiHandler::processData(unsigned long *raw)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));

    std::string dataToSend;


    if (std::abs(d_previous.rotation - newData.rotation) >= 0.0009)
    {
        d_previous.rotation = newData.rotation;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::ROTATION) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.rotation), sizeof(newData.rotation));
    }
    if (std::abs(d_previous.heading - newData.heading) >= 0.0009)
    {
        d_previous.heading = newData.heading;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::HEADING) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.heading), sizeof(newData.heading));
    }
    if (std::abs(d_previous.turnRate - newData.turnRate) >= 0.0009)
    {
        d_previous.turnRate = newData.turnRate;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::TURN_RATE) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.turnRate), sizeof(newData.turnRate));
    }
    if (std::abs(d_previous.currentTrack - newData.currentTrack) >= 0.0009)
    {
        d_previous.currentTrack = newData.currentTrack;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::CURRENT_TRACK) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.currentTrack), sizeof(newData.currentTrack));
    }

    if (std::abs(d_previous.gpsWpDesiredTrack - newData.gpsWpDesiredTrack) >= 0.009)
    {
        d_previous.gpsWpDesiredTrack = newData.gpsWpDesiredTrack;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::GPS_WP_DTK) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.gpsWpDesiredTrack), sizeof(newData.gpsWpDesiredTrack));
    }

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::COORDINATES) });
    dataToSend.append(reinterpret_cast<const char*>(&newData.currLat), sizeof(newData.currLat));
    dataToSend.append(reinterpret_cast<const char *>(&newData.currLon), sizeof(newData.currLon));

    d_previous.currLat = newData.currLat;
    d_previous.currLon = newData.currLon;

    if (std::abs(d_previous.trueHeading - newData.trueHeading) >= 0.0009)
    {
        d_previous.trueHeading = newData.trueHeading;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::TRUE_HEADING) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.trueHeading), sizeof(newData.trueHeading));
    }

    // qDebug() << "gps drives nav1:" << newData.gpsDrivesNav1 << "approach hold:" << newData.autopilotApproachHold << "approach type:" << newData.gpsApproachApproachType << "selected nav:" << newData.autopilotNavSelected;

    // gps
    if ((newData.gpsDrivesNav1
          && (!newData.autopilotApproachHold || newData.gpsApproachApproachType == simenums::ApproachType::RNAV))
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

    d_previous.autopilotNavSelected = newData.autopilotNavSelected;
    d_previous.gpsDrivesNav1 = newData.gpsDrivesNav1;


    return dataToSend;
}

}  // namespace hsi