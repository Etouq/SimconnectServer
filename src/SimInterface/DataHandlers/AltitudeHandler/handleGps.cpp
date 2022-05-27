#include "AltitudeHandler.hpp"
#include "common/dataIdentifiers.hpp"
#include "common/simEnums.hpp"

#include <cmath>

namespace altitude
{

void AltitudeHandler::handleGps(QByteArray &dataToSend, const DataStruct &newData)
{
    SimconnectIds id = SimconnectIds::VERT_DEV_MODE;
    if ((newData.gpsApproachActive || newData.apApproachActive)
        && newData.gpsApproachApproachType == ApproachType::RNAV) [[unlikely]]
    {
        if (d_vertDevMode != VerticalDeviationMode::GP) [[unlikely]]
        {
            d_vertDevMode = VerticalDeviationMode::GP;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&d_vertDevMode), sizeof(d_vertDevMode));

            // update deviation as well
            d_previous.gpsVertError = newData.gpsVertError;
            d_deviation = newData.gpsVertError / 150.0;
            id = SimconnectIds::VERT_DEV_VALUE;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&d_deviation), sizeof(d_deviation));
        }
        else if (std::abs(d_previous.gpsVertError - newData.gpsVertError) >= 0.1) [[likely]]
        {
            d_previous.gpsVertError = newData.gpsVertError;
            d_deviation = newData.gpsVertError / 150.0;
            id = SimconnectIds::VERT_DEV_VALUE;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&d_deviation), sizeof(d_deviation));
        }
    }
    else if (newData.nav1HasGlideslope) [[unlikely]]
    {
        if (d_vertDevMode != VerticalDeviationMode::GSPREVIEW) [[unlikely]]
        {
            d_vertDevMode = VerticalDeviationMode::GSPREVIEW;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&d_vertDevMode), sizeof(d_vertDevMode));

            // update deviation as well
            d_previous.nav1Gsi = newData.nav1Gsi;
            d_deviation = newData.nav1Gsi / 127.0;
            id = SimconnectIds::VERT_DEV_VALUE;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&d_deviation), sizeof(d_deviation));
        }
        else if (std::abs(d_previous.nav1Gsi - newData.nav1Gsi) >= 0.1) [[likely]]
        {
            d_previous.nav1Gsi = newData.nav1Gsi;
            d_deviation = newData.nav1Gsi / 127.0;
            id = SimconnectIds::VERT_DEV_VALUE;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&d_deviation), sizeof(d_deviation));
        }
    }
    else if (newData.nav2HasGlideslope) [[unlikely]]
    {
        if (d_vertDevMode != VerticalDeviationMode::GSPREVIEW) [[unlikely]]
        {
            d_vertDevMode = VerticalDeviationMode::GSPREVIEW;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&d_vertDevMode), sizeof(d_vertDevMode));

            // update deviation as well
            d_previous.nav2Gsi = newData.nav2Gsi;
            d_deviation = newData.nav2Gsi / 127.0;
            id = SimconnectIds::VERT_DEV_VALUE;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&d_deviation), sizeof(d_deviation));
        }
        else if (std::abs(d_previous.nav2Gsi - newData.nav2Gsi) >= 0.1) [[likely]]
        {
            d_previous.nav2Gsi = newData.nav2Gsi;
            d_deviation = newData.nav2Gsi / 127.0;
            id = SimconnectIds::VERT_DEV_VALUE;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&d_deviation), sizeof(d_deviation));
        }
    }
    else if (d_vertDevMode != VerticalDeviationMode::NONE) [[unlikely]]
    {
        d_vertDevMode = VerticalDeviationMode::NONE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&d_vertDevMode), sizeof(d_vertDevMode));
    }
}

}  // namespace altitude
