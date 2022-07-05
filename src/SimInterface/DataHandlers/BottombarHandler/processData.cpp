#include "BottombarHandler.hpp"
#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"

#include <cmath>

namespace bottombar
{

QByteArray BottombarHandler::processData(unsigned long *raw)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));

    QByteArray dataToSend;

    if (d_previous.zuluSeconds != newData.zuluSeconds)
    {
        d_previous.zuluSeconds = newData.zuluSeconds;
        util::appendData(PfdIdentifier::ZULU_SECONDS, newData.zuluSeconds, dataToSend);
    }
    if (d_previous.localSeconds != newData.localSeconds)
    {
        d_previous.localSeconds = newData.localSeconds;
        util::appendData(PfdIdentifier::LOCAL_SECONDS, newData.localSeconds, dataToSend);
    }

    if (d_previous.groundSpeed != newData.groundSpeed)
    {
        d_previous.groundSpeed = newData.groundSpeed;
        util::appendData(PfdIdentifier::GROUND_SPEED, newData.groundSpeed, dataToSend);
    }
    if (std::abs(d_previous.totalAirTemp - newData.totalAirTemp) >= 0.25)
    {
        d_previous.totalAirTemp = newData.totalAirTemp;
        util::appendData(PfdIdentifier::TOTAL_AIR_TEMP, newData.totalAirTemp, dataToSend);
    }
    if (std::abs(d_previous.outsideAirTemp - newData.outsideAirTemp) >= 0.25)
    {
        d_previous.outsideAirTemp = newData.outsideAirTemp;
        util::appendData(PfdIdentifier::OUTSIDE_AIR_TEMP, newData.outsideAirTemp, dataToSend);
    }
    if (std::abs(d_previous.isaAirTemp - newData.isaAirTemp) >= 0.25)
    {
        d_previous.isaAirTemp = newData.isaAirTemp;
        util::appendData(PfdIdentifier::ISA_AIR_TEMP, newData.isaAirTemp, dataToSend);
    }

    return dataToSend;
}

}  // namespace bottombar
