#include "common/dataIdentifiers.hpp"
#include "HsiHandler.hpp"

#include <cmath>

namespace hsi
{

void HsiHandler::handleNav1(std::string &dataToSend, const DataStruct &newData)
{

    if (d_displayDeviation != newData.nav1HasNav)
    {
        d_displayDeviation = newData.nav1HasNav;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::DISPLAY_DEVIATION) });
        dataToSend.append(reinterpret_cast<const char*>(&d_displayDeviation), sizeof(d_displayDeviation));
    }

    if (newData.nav1HasLoc)
    {
        if (d_navSource != HsiNavSource::LOC1)
        {
            d_navSource = HsiNavSource::LOC1;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::NAV_SOURCE) });
            dataToSend.append(reinterpret_cast<const char*>(&d_navSource), sizeof(d_navSource));

            // nav source changed so update course
            d_course = newData.nav1Loc;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE) });
            dataToSend.append(reinterpret_cast<const char*>(&d_course), sizeof(d_course));

            // update cdi and toFrom as well
            d_previous.nav1Cdi = newData.nav1Cdi;
            d_courseDeviation = newData.nav1Cdi / 127.0;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE_DEVIATION) });
            dataToSend.append(reinterpret_cast<const char*>(&d_courseDeviation), sizeof(d_courseDeviation));

            d_previous.nav1ToFrom = newData.nav1ToFrom;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::TO_FROM) });
            dataToSend.append(reinterpret_cast<const char*>(&newData.nav1ToFrom), sizeof(newData.nav1ToFrom));

            return;
        }

        if (std::abs(d_course - newData.nav1Loc) >= 0.0009)
        {
            d_course = newData.nav1Loc;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE) });
            dataToSend.append(reinterpret_cast<const char*>(&d_course), sizeof(d_course));
        }
    }
    else
    {
        if (d_navSource != HsiNavSource::VOR1)
        {
            d_navSource = HsiNavSource::VOR1;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::NAV_SOURCE) });
            dataToSend.append(reinterpret_cast<const char*>(&d_navSource), sizeof(d_navSource));

            // nav source changed so update course
            d_course = newData.nav1Obs;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE) });
            dataToSend.append(reinterpret_cast<const char*>(&d_course), sizeof(d_course));

            // update cdi and toFrom as well
            d_previous.nav1Cdi = newData.nav1Cdi;
            d_courseDeviation = newData.nav1Cdi / 127.0;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE_DEVIATION) });
            dataToSend.append(reinterpret_cast<const char*>(&d_courseDeviation), sizeof(d_courseDeviation));

            d_previous.nav1ToFrom = newData.nav1ToFrom;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::TO_FROM) });
            dataToSend.append(reinterpret_cast<const char*>(&newData.nav1ToFrom), sizeof(newData.nav1ToFrom));

            return;
        }

        if (std::abs(d_course - newData.nav1Obs) >= 0.0009)
        {
            d_course = newData.nav1Obs;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE) });
            dataToSend.append(reinterpret_cast<const char*>(&d_course), sizeof(d_course));
        }
    }

    if (std::abs(d_previous.nav1Cdi - newData.nav1Cdi) >= 0.3)
    {
        d_previous.nav1Cdi = newData.nav1Cdi;
        d_courseDeviation = newData.nav1Cdi / 127.0;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::COURSE_DEVIATION) });
        dataToSend.append(reinterpret_cast<const char*>(&d_courseDeviation), sizeof(d_courseDeviation));
    }

    if (d_previous.nav1ToFrom != newData.nav1ToFrom)
    {
        d_previous.nav1ToFrom = newData.nav1ToFrom;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::TO_FROM) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.nav1ToFrom), sizeof(newData.nav1ToFrom));
    }
}

}  // namespace hsi