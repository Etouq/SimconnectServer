#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"
#include "HsiHandler.hpp"

#include <cmath>

namespace hsi
{

void HsiHandler::handleNav2(QByteArray &dataToSend, const DataStruct &newData)
{

    if (d_displayDeviation != newData.nav2HasNav)
    {
        d_displayDeviation = newData.nav2HasNav;
        util::appendData(PfdIdentifier::DISPLAY_DEVIATION, d_displayDeviation, dataToSend);
    }

    if (newData.nav2HasLoc)
    {
        if (d_navSource != HsiNavSource::LOC1)
        {
            d_navSource = HsiNavSource::LOC1;
            util::appendData(PfdIdentifier::NAV_SOURCE, d_navSource, dataToSend);

            // nav source changed so update course
            d_course = newData.nav2Loc;
            util::appendData(PfdIdentifier::COURSE, d_course, dataToSend);

            // update cdi and toFrom as well
            d_previous.nav2Cdi = newData.nav2Cdi;
            d_courseDeviation = newData.nav2Cdi / 127.0;
            util::appendData(PfdIdentifier::COURSE_DEVIATION, d_courseDeviation, dataToSend);

            d_previous.nav2ToFrom = newData.nav2ToFrom;
            util::appendData(PfdIdentifier::TO_FROM, newData.nav2ToFrom, dataToSend);

            return;
        }

        if (std::abs(d_course - newData.nav2Loc) >= 0.0009)
        {
            d_course = newData.nav2Loc;
            util::appendData(PfdIdentifier::COURSE, d_course, dataToSend);
        }
    }
    else
    {
        if (d_navSource != HsiNavSource::VOR1)
        {
            d_navSource = HsiNavSource::VOR1;
            util::appendData(PfdIdentifier::NAV_SOURCE, d_navSource, dataToSend);

            // nav source changed so update course
            d_course = newData.nav2Obs;
            util::appendData(PfdIdentifier::COURSE, d_course, dataToSend);

            // update cdi and toFrom as well
            d_previous.nav2Cdi = newData.nav2Cdi;
            d_courseDeviation = newData.nav2Cdi / 127.0;
            util::appendData(PfdIdentifier::COURSE_DEVIATION, d_courseDeviation, dataToSend);

            d_previous.nav2ToFrom = newData.nav2ToFrom;
            util::appendData(PfdIdentifier::TO_FROM, newData.nav2ToFrom, dataToSend);

            return;
        }

        if (std::abs(d_course - newData.nav2Obs) >= 0.0009)
        {
            d_course = newData.nav2Obs;
            util::appendData(PfdIdentifier::COURSE, d_course, dataToSend);
        }
    }

    if (std::abs(d_previous.nav2Cdi - newData.nav2Cdi) >= 0.3)
    {
        d_previous.nav2Cdi = newData.nav2Cdi;
        d_courseDeviation = newData.nav2Cdi / 127.0;
        util::appendData(PfdIdentifier::COURSE_DEVIATION, d_courseDeviation, dataToSend);
    }

    if (d_previous.nav2ToFrom != newData.nav2ToFrom)
    {
        d_previous.nav2ToFrom = newData.nav2ToFrom;
        util::appendData(PfdIdentifier::TO_FROM, newData.nav2ToFrom, dataToSend);
    }
}

}  // namespace hsi