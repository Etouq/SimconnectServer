#include "WindInfoHandler.hpp"
#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"

namespace windinfo
{

QByteArray WindInfoHandler::sendCurrentData()
{
    QByteArray dataToSend;
    util::appendData(PfdIdentifier::WIND_STRENGTH, d_previous.windVelocity, dataToSend);

    util::appendData(PfdIdentifier::WIND_TRUE_DIRECTION, d_previous.windTrueDirection, dataToSend);

    util::appendData(PfdIdentifier::WIND_DIRECTION, d_previous.windDirection, dataToSend);

    return dataToSend;
}

}  // namespace windinfo
