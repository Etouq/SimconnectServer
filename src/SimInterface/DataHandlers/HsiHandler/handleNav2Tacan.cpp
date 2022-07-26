#include "common/dataIdentifiers.hpp"
#include "HsiHandler.hpp"

#include <cmath>

namespace hsi
{

void HsiHandler::handleNav2Tacan(std::string &dataToSend, const DataStruct &newData)
{

    if (d_navSource != HsiNavSource::TCN2)
    {
        d_navSource = HsiNavSource::TCN2;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::NAV_SOURCE) });
        dataToSend.append(reinterpret_cast<const char*>(&d_navSource), sizeof(d_navSource));

        // nav source changed so we need to update everything
        d_displayDeviation = newData.tacanDrivesNav1;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::DISPLAY_DEVIATION) });
        dataToSend.append(reinterpret_cast<const char*>(&d_displayDeviation), sizeof(d_displayDeviation));

        d_course = newData.nav2TacanObs;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE) });
        dataToSend.append(reinterpret_cast<const char*>(&d_course), sizeof(d_course));

        d_previous.nav2TacanCdi = newData.nav2TacanCdi;
        d_courseDeviation = newData.nav2TacanCdi / 127.0;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE_DEVIATION) });
        dataToSend.append(reinterpret_cast<const char*>(&d_courseDeviation), sizeof(d_courseDeviation));

        d_previous.nav2TacanToFrom = newData.nav2TacanToFrom;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::TO_FROM) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.nav2TacanToFrom), sizeof(newData.nav2TacanToFrom));

        return;
    }

    if (d_displayDeviation != newData.tacanDrivesNav1)
    {
        d_displayDeviation = newData.tacanDrivesNav1;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::DISPLAY_DEVIATION) });
        dataToSend.append(reinterpret_cast<const char*>(&d_displayDeviation), sizeof(d_displayDeviation));
    }

    if (std::abs(d_course - newData.nav2TacanObs) >= 0.0009)
    {
        d_course = newData.nav2TacanObs;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE) });
        dataToSend.append(reinterpret_cast<const char*>(&d_course), sizeof(d_course));
    }

    if (std::abs(d_previous.nav2TacanCdi - newData.nav2TacanCdi) >= 0.3)
    {
        d_previous.nav2TacanCdi = newData.nav2TacanCdi;
        d_courseDeviation = newData.nav2TacanCdi / 127.0;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE_DEVIATION) });
        dataToSend.append(reinterpret_cast<const char*>(&d_courseDeviation), sizeof(d_courseDeviation));
    }

    if (d_previous.nav2TacanToFrom != newData.nav2TacanToFrom)
    {
        d_previous.nav2TacanToFrom = newData.nav2TacanToFrom;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::TO_FROM) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.nav2ToFrom), sizeof(newData.nav2ToFrom));
    }
}

}  // namespace hsi