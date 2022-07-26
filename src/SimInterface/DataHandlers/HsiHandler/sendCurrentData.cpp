#include "common/dataIdentifiers.hpp"
#include "HsiHandler.hpp"

namespace hsi
{

std::string HsiHandler::sendCurrentData()
{
    std::string dataToSend;
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::ROTATION) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.rotation), sizeof(d_previous.rotation));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::HEADING) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.heading), sizeof(d_previous.heading));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::TURN_RATE) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.turnRate), sizeof(d_previous.turnRate));


    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::CURRENT_TRACK) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.currentTrack), sizeof(d_previous.currentTrack));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::GPS_WP_DTK) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.gpsWpDesiredTrack), sizeof(d_previous.gpsWpDesiredTrack));


    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::COORDINATES) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.currLat), sizeof(d_previous.currLat));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.currLon), sizeof(d_previous.currLon));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::TRUE_HEADING) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.trueHeading), sizeof(d_previous.trueHeading));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::DISPLAY_DEVIATION) });
    dataToSend.append(reinterpret_cast<const char*>(&d_displayDeviation), sizeof(d_displayDeviation));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::NAV_SOURCE) });
    dataToSend.append(reinterpret_cast<const char*>(&d_navSource), sizeof(d_navSource));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE) });
    dataToSend.append(reinterpret_cast<const char*>(&d_course), sizeof(d_course));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE_DEVIATION) });
    dataToSend.append(reinterpret_cast<const char*>(&d_courseDeviation), sizeof(d_courseDeviation));

    switch (d_navSource)
    {
        case HsiNavSource::LOC1:
        case HsiNavSource::VOR1:
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::TO_FROM) });
            dataToSend.append(reinterpret_cast<const char*>(&d_previous.nav1ToFrom), sizeof(d_previous.nav1ToFrom));
            break;
        case HsiNavSource::LOC2:
        case HsiNavSource::VOR2:
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::TO_FROM) });
            dataToSend.append(reinterpret_cast<const char*>(&d_previous.nav2ToFrom), sizeof(d_previous.nav2ToFrom));
            break;
        case HsiNavSource::TCN1:
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::TO_FROM) });
            dataToSend.append(reinterpret_cast<const char*>(&d_previous.nav1TacanToFrom), sizeof(d_previous.nav1TacanToFrom));
            break;
        case HsiNavSource::TCN2:
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::TO_FROM) });
            dataToSend.append(reinterpret_cast<const char*>(&d_previous.nav2TacanToFrom), sizeof(d_previous.nav2TacanToFrom));
            break;
        case HsiNavSource::GPS:
        {
            constexpr int32_t gpsToFromValue = 1;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::TO_FROM) });
            dataToSend.append(reinterpret_cast<const char*>(&gpsToFromValue), sizeof(gpsToFromValue));
            break;

        }
        case HsiNavSource::NONE:
        {
            constexpr int32_t emptyToFromValue = 0;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::TO_FROM) });
            dataToSend.append(reinterpret_cast<const char*>(&emptyToFromValue), sizeof(emptyToFromValue));
            break;

        }
    }

    return dataToSend;
}

}  // namespace hsi
