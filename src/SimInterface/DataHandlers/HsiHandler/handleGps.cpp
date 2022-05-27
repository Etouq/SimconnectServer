#include "common/dataIdentifiers.hpp"
#include "common/simEnums.hpp"
#include "HsiHandler.hpp"

#include <cmath>

namespace hsi
{

void HsiHandler::handleGps(QByteArray &dataToSend, const DataStruct &newData)
{

    SimconnectIds id = SimconnectIds::DISPLAY_DEVIATION;

    if (d_displayDeviation != d_nextGpsWpIdValid)
    {
        d_displayDeviation = d_nextGpsWpIdValid;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&d_displayDeviation), sizeof(d_displayDeviation));
    }

    if (d_navSource != HsiNavSource::GPS)
    {
        d_navSource = HsiNavSource::GPS;
        id = SimconnectIds::NAV_SOURCE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id))
          .append(reinterpret_cast<const char *>(&d_navSource), sizeof(d_navSource));

        // source changed so update to/from
        id = SimconnectIds::TO_FROM;
        static const int32_t toFromValue = 1;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&toFromValue), sizeof(toFromValue));
    }

    if (d_displayDeviation) [[likely]]
    {
        if (std::abs(d_course - newData.gpsWpDesiredTrack) >= 0.0009)
        {
            d_course = newData.gpsWpDesiredTrack;
            id = SimconnectIds::COURSE;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&d_course), sizeof(d_course));
        }

        if (std::abs(d_courseDeviation - newData.gpsWpCrossTrack) >= 0.002)
        {
            d_courseDeviation = newData.gpsWpCrossTrack;
            id = SimconnectIds::COURSE_DEVIATION;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&d_courseDeviation), sizeof(d_courseDeviation));
        }

        return;
    }

    if (std::abs(d_course) >= 0.0009)
    {
        d_course = 0.0;
        id = SimconnectIds::COURSE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&d_course), sizeof(d_course));
    }

    if (std::abs(d_courseDeviation) >= 0.0009)
    {
        d_courseDeviation = 0.0;
        id = SimconnectIds::COURSE_DEVIATION;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&d_courseDeviation), sizeof(d_courseDeviation));
    }
}

}  // namespace hsi