#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"
#include "HsiHandler.hpp"

#include <cmath>

namespace hsi
{

void HsiHandler::handleNav2Tacan(QByteArray &dataToSend, const DataStruct &newData)
{

    if (d_navSource != HsiNavSource::TCN2)
    {
        d_navSource = HsiNavSource::TCN2;
        util::appendData(PfdIdentifier::NAV_SOURCE, d_navSource, dataToSend);

        // nav source changed so we need to update everything
        d_displayDeviation = newData.tacanDrivesNav1;
        util::appendData(PfdIdentifier::DISPLAY_DEVIATION, d_displayDeviation, dataToSend);

        d_course = newData.nav2TacanObs;
        util::appendData(PfdIdentifier::COURSE, d_course, dataToSend);

        d_previous.nav2TacanCdi = newData.nav2TacanCdi;
        d_courseDeviation = newData.nav2TacanCdi / 127.0;
        util::appendData(PfdIdentifier::COURSE_DEVIATION, d_courseDeviation, dataToSend);

        d_previous.nav2TacanToFrom = newData.nav2TacanToFrom;
        util::appendData(PfdIdentifier::TO_FROM, newData.nav2TacanToFrom, dataToSend);

        return;
    }

    if (d_displayDeviation != newData.tacanDrivesNav1)
    {
        d_displayDeviation = newData.tacanDrivesNav1;
        util::appendData(PfdIdentifier::DISPLAY_DEVIATION, d_displayDeviation, dataToSend);
    }

    if (std::abs(d_course - newData.nav2TacanObs) >= 0.0009)
    {
        d_course = newData.nav2TacanObs;
        util::appendData(PfdIdentifier::COURSE, d_course, dataToSend);
    }

    if (std::abs(d_previous.nav2TacanCdi - newData.nav2TacanCdi) >= 0.3)
    {
        d_previous.nav2TacanCdi = newData.nav2TacanCdi;
        d_courseDeviation = newData.nav2TacanCdi / 127.0;
        util::appendData(PfdIdentifier::COURSE_DEVIATION, d_courseDeviation, dataToSend);
    }

    if (d_previous.nav2TacanToFrom != newData.nav2TacanToFrom)
    {
        d_previous.nav2TacanToFrom = newData.nav2TacanToFrom;
        util::appendData(PfdIdentifier::TO_FROM, newData.nav2ToFrom, dataToSend);
    }
}

}  // namespace hsi