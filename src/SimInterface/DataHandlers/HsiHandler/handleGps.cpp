#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"
#include "HsiHandler.hpp"

#include <cmath>

namespace hsi
{

void HsiHandler::handleGps(QByteArray &dataToSend, const DataStruct &newData)
{
    if (d_displayDeviation != d_nextGpsWpIdValid)
    {
        d_displayDeviation = d_nextGpsWpIdValid;
        util::appendData(PfdIdentifier::DISPLAY_DEVIATION, d_displayDeviation, dataToSend);
    }

    if (d_navSource != HsiNavSource::GPS)
    {
        d_navSource = HsiNavSource::GPS;
        util::appendData(PfdIdentifier::NAV_SOURCE, d_navSource, dataToSend);

        // source changed so update to/from
        static const int32_t toFromValue = 1;
        util::appendData(PfdIdentifier::TO_FROM, toFromValue, dataToSend);
    }

    if (d_displayDeviation) [[likely]]
    {
        if (std::abs(d_course - newData.gpsWpDesiredTrack) >= 0.0009)
        {
            d_course = newData.gpsWpDesiredTrack;
            util::appendData(PfdIdentifier::COURSE, d_course, dataToSend);
        }

        if (std::abs(d_courseDeviation - newData.gpsWpCrossTrack) >= 0.002)
        {
            d_courseDeviation = newData.gpsWpCrossTrack;
            util::appendData(PfdIdentifier::COURSE_DEVIATION, d_courseDeviation, dataToSend);
        }

        return;
    }

    if (std::abs(d_course) >= 0.0009)
    {
        d_course = 0.0;
        util::appendData(PfdIdentifier::COURSE, d_course, dataToSend);
    }

    if (std::abs(d_courseDeviation) >= 0.0009)
    {
        d_courseDeviation = 0.0;
        util::appendData(PfdIdentifier::COURSE_DEVIATION, d_courseDeviation, dataToSend);
    }
}

}  // namespace hsi