#include "AltitudeHandler.hpp"
#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"

#include <cmath>

namespace altitude
{

void AltitudeHandler::handleNav2(QByteArray &dataToSend, const DataStruct &newData)
{
    if (newData.nav2HasGlideslope) [[unlikely]]
    {
        if (d_vertDevMode != VerticalDeviationMode::GS) [[unlikely]]
        {
            d_vertDevMode = VerticalDeviationMode::GS;
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
