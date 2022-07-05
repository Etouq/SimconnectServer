#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"
#include "HsiHandler.hpp"

namespace hsi
{

QByteArray HsiHandler::sendCurrentData()
{
    QByteArray dataToSend;
    util::appendData(PfdIdentifier::ROTATION, d_previous.rotation, dataToSend);

    util::appendData(PfdIdentifier::HEADING, d_previous.heading, dataToSend);

    util::appendData(PfdIdentifier::TURN_RATE, d_previous.turnRate, dataToSend);


    util::appendData(PfdIdentifier::CURRENT_TRACK, d_previous.currentTrack, dataToSend);

    util::appendData(MfdIdentifier::GPS_WP_DTK, d_previous.gpsWpDesiredTrack, dataToSend);


    util::appendData(MfdIdentifier::COORDINATES, d_previous.currLat, dataToSend);
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.currLon), sizeof(d_previous.currLon));

    util::appendData(MfdIdentifier::TRUE_HEADING, d_previous.trueHeading, dataToSend);

    util::appendData(PfdIdentifier::DISPLAY_DEVIATION, d_displayDeviation, dataToSend);

    util::appendData(PfdIdentifier::NAV_SOURCE, d_navSource, dataToSend);

    util::appendData(PfdIdentifier::COURSE, d_course, dataToSend);

    util::appendData(PfdIdentifier::COURSE_DEVIATION, d_courseDeviation, dataToSend);

    switch (d_navSource)
    {
        case HsiNavSource::LOC1:
        case HsiNavSource::VOR1:
            util::appendData(PfdIdentifier::TO_FROM, d_previous.nav1ToFrom, dataToSend);
            break;
        case HsiNavSource::LOC2:
        case HsiNavSource::VOR2:
            util::appendData(PfdIdentifier::TO_FROM, d_previous.nav2ToFrom, dataToSend);
            break;
        case HsiNavSource::TCN1:
            util::appendData(PfdIdentifier::TO_FROM, d_previous.nav1TacanToFrom, dataToSend);
            break;
        case HsiNavSource::TCN2:
            util::appendData(PfdIdentifier::TO_FROM, d_previous.nav2TacanToFrom, dataToSend);
            break;
        case HsiNavSource::GPS:
        {
            constexpr int32_t gpsToFromValue = 1;
            util::appendData(PfdIdentifier::TO_FROM, gpsToFromValue, dataToSend);
            break;

        }
        case HsiNavSource::NONE:
        {
            constexpr int32_t emptyToFromValue = 0;
            util::appendData(PfdIdentifier::TO_FROM, emptyToFromValue, dataToSend);
            break;

        }
    }

    return dataToSend;
}

}  // namespace hsi
