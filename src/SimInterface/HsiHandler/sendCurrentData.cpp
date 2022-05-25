#include "../SimInterface.hpp"
#include "common/dataIdentifiers.hpp"
#include "HsiHandler.hpp"

namespace hsi
{

void HsiHandler::sendCurrentData()
{
    SimconnectIds id = SimconnectIds::ROTATION;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.rotation), sizeof(d_previous.rotation));

    id = SimconnectIds::HEADING;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id))
      .append(reinterpret_cast<const char *>(&d_previous.heading), sizeof(d_previous.heading));

    id = SimconnectIds::TURN_RATE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id))
      .append(reinterpret_cast<const char *>(&d_previous.turnRate), sizeof(d_previous.turnRate));


    id = SimconnectIds::CURRENT_TRACK;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id))
      .append(reinterpret_cast<const char *>(&d_previous.currentTrack), sizeof(d_previous.currentTrack));

    id = SimconnectIds::GPS_WP_DTK;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id))
      .append(reinterpret_cast<const char *>(&d_previous.gpsWpDesiredTrack), sizeof(d_previous.gpsWpDesiredTrack));


    id = SimconnectIds::COORDINATES;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.currLat), sizeof(d_previous.currLat));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.currLon), sizeof(d_previous.currLon));

    id = SimconnectIds::TRUE_HEADING;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.trueHeading), sizeof(d_previous.trueHeading));

    id = SimconnectIds::DISPLAY_DEVIATION;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_displayDeviation), sizeof(d_displayDeviation));

    id = SimconnectIds::NAV_SOURCE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_navSource), sizeof(d_navSource));

    id = SimconnectIds::COURSE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_course), sizeof(d_course));

    id = SimconnectIds::COURSE_DEVIATION;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_courseDeviation), sizeof(d_courseDeviation));


    id = SimconnectIds::TO_FROM;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    switch (d_navSource)
    {
        case HsiNavSource::LOC1:
        case HsiNavSource::VOR1:
            dataToSend.append(reinterpret_cast<const char *>(&d_previous.nav1ToFrom), sizeof(d_previous.nav1ToFrom));
            break;
        case HsiNavSource::LOC2:
        case HsiNavSource::VOR2:
            dataToSend.append(reinterpret_cast<const char *>(&d_previous.nav2ToFrom), sizeof(d_previous.nav2ToFrom));
            break;
        case HsiNavSource::TCN1:
            dataToSend.append(reinterpret_cast<const char *>(&d_previous.nav1TacanToFrom),
                              sizeof(d_previous.nav1TacanToFrom));
            break;
        case HsiNavSource::TCN2:
            dataToSend.append(reinterpret_cast<const char *>(&d_previous.nav2TacanToFrom),
                              sizeof(d_previous.nav2TacanToFrom));
            break;
        case HsiNavSource::GPS:
            static const int32_t gpsToFromValue = 1;
            dataToSend.append(reinterpret_cast<const char *>(&gpsToFromValue), sizeof(gpsToFromValue));
            break;
        case HsiNavSource::NONE:
            static const int32_t emptyToFromValue = 0;
            dataToSend.append(reinterpret_cast<const char *>(&emptyToFromValue), sizeof(emptyToFromValue));
            break;
    }

    emit d_parent->sendData(dataToSend);
}

}  // namespace hsi
