#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"
#include "HsiHandler.hpp"

#include <cmath>

namespace hsi
{

void HsiHandler::handleNav1Tacan(QByteArray &dataToSend, const DataStruct &newData)
{


    if (d_navSource != HsiNavSource::TCN1)
    {
        d_navSource = HsiNavSource::TCN1;
        util::appendData(PfdIdentifier::NAV_SOURCE, d_navSource, dataToSend);

        // nav source changed so we need to update everything
        d_displayDeviation = newData.tacanDrivesNav1;
        util::appendData(PfdIdentifier::DISPLAY_DEVIATION, d_displayDeviation, dataToSend);

        d_course = newData.nav1TacanObs;
        util::appendData(PfdIdentifier::COURSE, d_course, dataToSend);

        d_previous.nav1TacanCdi = newData.nav1TacanCdi;
        d_courseDeviation = newData.nav1TacanCdi / 127.0;
        util::appendData(PfdIdentifier::COURSE_DEVIATION, d_courseDeviation, dataToSend);

        d_previous.nav1TacanToFrom = newData.nav1TacanToFrom;
        util::appendData(PfdIdentifier::TO_FROM, newData.nav1TacanToFrom, dataToSend);

        return;
    }

    if (d_displayDeviation != newData.tacanDrivesNav1)
    {
        d_displayDeviation = newData.tacanDrivesNav1;
        util::appendData(PfdIdentifier::DISPLAY_DEVIATION, d_displayDeviation, dataToSend);
    }

    if (std::abs(d_course - newData.nav1TacanObs) >= 0.0009)
    {
        d_course = newData.nav1TacanObs;
        util::appendData(PfdIdentifier::COURSE, d_course, dataToSend);
    }

    if (std::abs(d_previous.nav1TacanCdi - newData.nav1TacanCdi) >= 0.3)
    {
        d_previous.nav1TacanCdi = newData.nav1TacanCdi;
        d_courseDeviation = newData.nav1TacanCdi / 127.0;
        util::appendData(PfdIdentifier::COURSE_DEVIATION, d_courseDeviation, dataToSend);
    }

    if (d_previous.nav1TacanToFrom != newData.nav1TacanToFrom)
    {
        d_previous.nav1TacanToFrom = newData.nav1TacanToFrom;
        util::appendData(PfdIdentifier::TO_FROM, newData.nav1ToFrom, dataToSend);
    }
}

}  // namespace hsi