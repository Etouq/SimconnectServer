#include "WindInfoHandler.hpp"
#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"

#include <cmath>

namespace windinfo
{

QByteArray WindInfoHandler::processData(unsigned long *raw)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));

    QByteArray dataToSend;

    if (std::abs(d_previous.windVelocity - newData.windVelocity) >= 0.1)
    {
        d_previous.windVelocity = newData.windVelocity;
        util::appendData(PfdIdentifier::WIND_STRENGTH, newData.windVelocity, dataToSend);
    }
    if (std::abs(d_previous.windTrueDirection - newData.windTrueDirection) >= 0.1)
    {
        d_previous.windTrueDirection = newData.windTrueDirection;
        util::appendData(PfdIdentifier::WIND_TRUE_DIRECTION, newData.windTrueDirection, dataToSend);
    }
    if (std::abs(d_previous.windDirection - newData.windDirection) >= 0.1)
    {
        d_previous.windDirection = newData.windDirection;
        util::appendData(PfdIdentifier::WIND_DIRECTION, newData.windDirection, dataToSend);
    }

    return dataToSend;
}

}  // namespace windinfo
