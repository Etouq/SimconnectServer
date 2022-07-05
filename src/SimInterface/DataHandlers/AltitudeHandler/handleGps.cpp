#include "AltitudeHandler.hpp"
#include "common/dataIdentifiers.hpp"
#include "common/simEnums.hpp"
#include "common/appendData.hpp"

#include <cmath>

namespace altitude
{

void AltitudeHandler::handleGps(QByteArray &dataToSend, const DataStruct &newData)
{
    if ((newData.gpsApproachActive || newData.apApproachActive)
        && newData.gpsApproachApproachType == simenums::ApproachType::RNAV) [[unlikely]]
    {
        if (d_vertDevMode != VerticalDeviationMode::GP) [[unlikely]]
        {
            d_vertDevMode = VerticalDeviationMode::GP;
            util::appendData(PfdIdentifier::VERT_DEV_MODE, d_vertDevMode, dataToSend);

            // update deviation as well
            d_previous.gpsVertError = newData.gpsVertError;
            d_deviation = newData.gpsVertError / 150.0;
            util::appendData(PfdIdentifier::VERT_DEV_VALUE, d_deviation, dataToSend);
        }
        else if (std::abs(d_previous.gpsVertError - newData.gpsVertError) >= 0.1) [[likely]]
        {
            d_previous.gpsVertError = newData.gpsVertError;
            d_deviation = newData.gpsVertError / 150.0;
            util::appendData(PfdIdentifier::VERT_DEV_VALUE, d_deviation, dataToSend);
        }
    }
    else if (newData.nav1HasGlideslope) [[unlikely]]
    {
        if (d_vertDevMode != VerticalDeviationMode::GSPREVIEW) [[unlikely]]
        {
            d_vertDevMode = VerticalDeviationMode::GSPREVIEW;
            util::appendData(PfdIdentifier::VERT_DEV_MODE, d_vertDevMode, dataToSend);

            // update deviation as well
            d_previous.nav1Gsi = newData.nav1Gsi;
            d_deviation = newData.nav1Gsi / 127.0;
            util::appendData(PfdIdentifier::VERT_DEV_VALUE, d_deviation, dataToSend);
        }
        else if (std::abs(d_previous.nav1Gsi - newData.nav1Gsi) >= 0.1) [[likely]]
        {
            d_previous.nav1Gsi = newData.nav1Gsi;
            d_deviation = newData.nav1Gsi / 127.0;
            util::appendData(PfdIdentifier::VERT_DEV_VALUE, d_deviation, dataToSend);
        }
    }
    else if (newData.nav2HasGlideslope) [[unlikely]]
    {
        if (d_vertDevMode != VerticalDeviationMode::GSPREVIEW) [[unlikely]]
        {
            d_vertDevMode = VerticalDeviationMode::GSPREVIEW;
            util::appendData(PfdIdentifier::VERT_DEV_MODE, d_vertDevMode, dataToSend);

            // update deviation as well
            d_previous.nav2Gsi = newData.nav2Gsi;
            d_deviation = newData.nav2Gsi / 127.0;
            util::appendData(PfdIdentifier::VERT_DEV_VALUE, d_deviation, dataToSend);
        }
        else if (std::abs(d_previous.nav2Gsi - newData.nav2Gsi) >= 0.1) [[likely]]
        {
            d_previous.nav2Gsi = newData.nav2Gsi;
            d_deviation = newData.nav2Gsi / 127.0;
            util::appendData(PfdIdentifier::VERT_DEV_VALUE, d_deviation, dataToSend);
        }
    }
    else if (d_vertDevMode != VerticalDeviationMode::NONE) [[unlikely]]
    {
        d_vertDevMode = VerticalDeviationMode::NONE;
        util::appendData(PfdIdentifier::VERT_DEV_MODE, d_vertDevMode, dataToSend);
    }
}

}  // namespace altitude
