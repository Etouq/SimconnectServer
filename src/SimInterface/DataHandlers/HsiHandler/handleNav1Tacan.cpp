#include "common/dataIdentifiers.hpp"
#include "HsiHandler.hpp"

#include <cmath>

namespace hsi
{

void HsiHandler::handleNav1Tacan(QByteArray &dataToSend, const DataStruct &newData)
{

    SimconnectIds id = SimconnectIds::NAV_SOURCE;


    if (d_navSource != HsiNavSource::TCN1)
    {
        d_navSource = HsiNavSource::TCN1;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&d_navSource), sizeof(d_navSource));

        // nav source changed so we need to update everything
        d_displayDeviation = newData.tacanDrivesNav1;
        id = SimconnectIds::DISPLAY_DEVIATION;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&d_displayDeviation), sizeof(d_displayDeviation));

        d_course = newData.nav1TacanObs;
        id = SimconnectIds::COURSE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&d_course), sizeof(d_course));

        d_previous.nav1TacanCdi = newData.nav1TacanCdi;
        d_courseDeviation = newData.nav1TacanCdi / 127.0;
        id = SimconnectIds::COURSE_DEVIATION;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&d_courseDeviation), sizeof(d_courseDeviation));

        d_previous.nav1TacanToFrom = newData.nav1TacanToFrom;
        id = SimconnectIds::TO_FROM;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav1TacanToFrom), sizeof(newData.nav1TacanToFrom));

        return;
    }

    if (d_displayDeviation != newData.tacanDrivesNav1)
    {
        d_displayDeviation = newData.tacanDrivesNav1;
        id = SimconnectIds::DISPLAY_DEVIATION;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&d_displayDeviation), sizeof(d_displayDeviation));
    }

    if (std::abs(d_course - newData.nav1TacanObs) >= 0.0009)
    {
        d_course = newData.nav1TacanObs;
        id = SimconnectIds::COURSE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&d_course), sizeof(d_course));
    }

    if (std::abs(d_previous.nav1TacanCdi - newData.nav1TacanCdi) >= 0.3)
    {
        d_previous.nav1TacanCdi = newData.nav1TacanCdi;
        d_courseDeviation = newData.nav1TacanCdi / 127.0;
        id = SimconnectIds::COURSE_DEVIATION;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&d_courseDeviation), sizeof(d_courseDeviation));
    }

    if (d_previous.nav1TacanToFrom != newData.nav1TacanToFrom)
    {
        d_previous.nav1TacanToFrom = newData.nav1TacanToFrom;
        id = SimconnectIds::TO_FROM;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav1ToFrom), sizeof(newData.nav1ToFrom));
    }
}

}  // namespace hsi