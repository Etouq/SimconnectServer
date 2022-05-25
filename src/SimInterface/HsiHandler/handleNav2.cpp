#include "common/dataIdentifiers.hpp"
#include "HsiHandler.hpp"

#include <cmath>

namespace hsi
{

void HsiHandler::handleNav2(QByteArray &dataToSend, const DataStruct &newData)
{

    SimconnectIds id = SimconnectIds::DISPLAY_DEVIATION;

    if (d_displayDeviation != newData.nav2HasNav)
    {
        d_displayDeviation = newData.nav2HasNav;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&d_displayDeviation), sizeof(d_displayDeviation));
    }

    if (newData.nav2HasLoc)
    {
        if (d_navSource != HsiNavSource::LOC1)
        {
            d_navSource = HsiNavSource::LOC1;
            id = SimconnectIds::NAV_SOURCE;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&d_navSource), sizeof(d_navSource));

            // nav source changed so update course
            d_course = newData.nav2Loc;
            id = SimconnectIds::COURSE;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&d_course), sizeof(d_course));

            // update cdi and toFrom as well
            d_previous.nav2Cdi = newData.nav2Cdi;
            d_courseDeviation = newData.nav2Cdi / 127.0;
            id = SimconnectIds::COURSE_DEVIATION;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&d_courseDeviation), sizeof(d_courseDeviation));

            d_previous.nav2ToFrom = newData.nav2ToFrom;
            id = SimconnectIds::TO_FROM;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&newData.nav2ToFrom), sizeof(newData.nav2ToFrom));

            return;
        }

        if (std::abs(d_course - newData.nav2Loc) >= 0.0009)
        {
            d_course = newData.nav2Loc;
            id = SimconnectIds::COURSE;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&d_course), sizeof(d_course));
        }
    }
    else
    {
        if (d_navSource != HsiNavSource::VOR1)
        {
            d_navSource = HsiNavSource::VOR1;
            id = SimconnectIds::NAV_SOURCE;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&d_navSource), sizeof(d_navSource));

            // nav source changed so update course
            d_course = newData.nav2Obs;
            id = SimconnectIds::COURSE;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&d_course), sizeof(d_course));

            // update cdi and toFrom as well
            d_previous.nav2Cdi = newData.nav2Cdi;
            d_courseDeviation = newData.nav2Cdi / 127.0;
            id = SimconnectIds::COURSE_DEVIATION;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&d_courseDeviation), sizeof(d_courseDeviation));

            d_previous.nav2ToFrom = newData.nav2ToFrom;
            id = SimconnectIds::TO_FROM;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&newData.nav2ToFrom), sizeof(newData.nav2ToFrom));

            return;
        }

        if (std::abs(d_course - newData.nav2Obs) >= 0.0009)
        {
            d_course = newData.nav2Obs;
            id = SimconnectIds::COURSE;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&d_course), sizeof(d_course));
        }
    }

    if (std::abs(d_previous.nav2Cdi - newData.nav2Cdi) >= 0.3)
    {
        d_previous.nav2Cdi = newData.nav2Cdi;
        d_courseDeviation = newData.nav2Cdi / 127.0;
        id = SimconnectIds::COURSE_DEVIATION;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&d_courseDeviation), sizeof(d_courseDeviation));
    }

    if (d_previous.nav2ToFrom != newData.nav2ToFrom)
    {
        d_previous.nav2ToFrom = newData.nav2ToFrom;
        id = SimconnectIds::TO_FROM;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav2ToFrom), sizeof(newData.nav2ToFrom));
    }
}

}  // namespace hsi