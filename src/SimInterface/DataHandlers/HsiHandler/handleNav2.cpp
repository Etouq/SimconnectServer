#include "common/dataIdentifiers.hpp"
#include "HsiHandler.hpp"

#include <cmath>

namespace hsi
{

void HsiHandler::handleNav2(std::string &dataToSend, const DataStruct &newData)
{

    if (d_displayDeviation != newData.nav2HasNav)
    {
        d_displayDeviation = newData.nav2HasNav;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::DISPLAY_DEVIATION) });
        dataToSend.append(reinterpret_cast<const char*>(&d_displayDeviation), sizeof(d_displayDeviation));
    }

    if (newData.nav2HasLoc)
    {
        if (d_navSource != HsiNavSource::LOC2)
        {
            d_navSource = HsiNavSource::LOC2;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::NAV_SOURCE) });
            dataToSend.append(reinterpret_cast<const char*>(&d_navSource), sizeof(d_navSource));

            // nav source changed so update course
            d_course = newData.nav2Loc;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE) });
            dataToSend.append(reinterpret_cast<const char*>(&d_course), sizeof(d_course));

            // update cdi and toFrom as well
            d_previous.nav2Cdi = newData.nav2Cdi;
            d_courseDeviation = newData.nav2Cdi / 127.0;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE_DEVIATION) });
            dataToSend.append(reinterpret_cast<const char*>(&d_courseDeviation), sizeof(d_courseDeviation));

            d_previous.nav2ToFrom = newData.nav2ToFrom;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::TO_FROM) });
            dataToSend.append(reinterpret_cast<const char*>(&newData.nav2ToFrom), sizeof(newData.nav2ToFrom));

            return;
        }

        if (std::abs(d_course - newData.nav2Loc) >= 0.0009)
        {
            d_course = newData.nav2Loc;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE) });
            dataToSend.append(reinterpret_cast<const char*>(&d_course), sizeof(d_course));
        }
    }
    else
    {
        if (d_navSource != HsiNavSource::VOR2)
        {
            d_navSource = HsiNavSource::VOR2;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::NAV_SOURCE) });
            dataToSend.append(reinterpret_cast<const char*>(&d_navSource), sizeof(d_navSource));

            // nav source changed so update course
            d_course = newData.nav2Obs;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE) });
            dataToSend.append(reinterpret_cast<const char*>(&d_course), sizeof(d_course));

            // update cdi and toFrom as well
            d_previous.nav2Cdi = newData.nav2Cdi;
            d_courseDeviation = newData.nav2Cdi / 127.0;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE_DEVIATION) });
            dataToSend.append(reinterpret_cast<const char*>(&d_courseDeviation), sizeof(d_courseDeviation));

            d_previous.nav2ToFrom = newData.nav2ToFrom;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::TO_FROM) });
            dataToSend.append(reinterpret_cast<const char*>(&newData.nav2ToFrom), sizeof(newData.nav2ToFrom));

            return;
        }

        if (std::abs(d_course - newData.nav2Obs) >= 0.0009)
        {
            d_course = newData.nav2Obs;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE) });
            dataToSend.append(reinterpret_cast<const char*>(&d_course), sizeof(d_course));
        }
    }

    if (std::abs(d_previous.nav2Cdi - newData.nav2Cdi) >= 0.3)
    {
        d_previous.nav2Cdi = newData.nav2Cdi;
        d_courseDeviation = newData.nav2Cdi / 127.0;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE_DEVIATION) });
        dataToSend.append(reinterpret_cast<const char*>(&d_courseDeviation), sizeof(d_courseDeviation));
    }

    if (d_previous.nav2ToFrom != newData.nav2ToFrom)
    {
        d_previous.nav2ToFrom = newData.nav2ToFrom;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::TO_FROM) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.nav2ToFrom), sizeof(newData.nav2ToFrom));
    }
}

}  // namespace hsi
