#include "common/dataIdentifiers.hpp"
#include "HsiHandler.hpp"

#include <cmath>

namespace hsi
{

void HsiHandler::handleGps(std::string &dataToSend, const DataStruct &newData)
{
    if (d_displayDeviation != d_nextGpsWpIdValid)
    {
        d_displayDeviation = d_nextGpsWpIdValid;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::DISPLAY_DEVIATION) });
        dataToSend.append(reinterpret_cast<const char*>(&d_displayDeviation), sizeof(d_displayDeviation));
    }

    if (d_navSource != HsiNavSource::GPS)
    {
        d_navSource = HsiNavSource::GPS;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::NAV_SOURCE) });
        dataToSend.append(reinterpret_cast<const char*>(&d_navSource), sizeof(d_navSource));

        // source changed so update to/from
        static constexpr int32_t toFromValue = 1;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::TO_FROM) });
        dataToSend.append(reinterpret_cast<const char*>(&toFromValue), sizeof(toFromValue));
    }

    if (d_displayDeviation) [[likely]]
    {
        if (std::abs(d_course - newData.gpsWpDesiredTrack) >= 0.0009)
        {
            d_course = newData.gpsWpDesiredTrack;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE) });
            dataToSend.append(reinterpret_cast<const char*>(&d_course), sizeof(d_course));
        }

        if (std::abs(d_courseDeviation - newData.gpsWpCrossTrack) >= 0.002)
        {
            d_courseDeviation = newData.gpsWpCrossTrack;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE_DEVIATION) });
            dataToSend.append(reinterpret_cast<const char*>(&d_courseDeviation), sizeof(d_courseDeviation));
        }

        return;
    }

    if (std::abs(d_course) >= 0.0009)
    {
        d_course = 0.0;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE) });
        dataToSend.append(reinterpret_cast<const char*>(&d_course), sizeof(d_course));
    }

    if (std::abs(d_courseDeviation) >= 0.0009)
    {
        d_courseDeviation = 0.0;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE_DEVIATION) });
        dataToSend.append(reinterpret_cast<const char*>(&d_courseDeviation), sizeof(d_courseDeviation));
    }
}

}  // namespace hsi