#include "BottombarHandler.hpp"
#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"

namespace bottombar
{

QByteArray BottombarHandler::sendCurrentData()
{
    QByteArray dataToSend;
    util::appendData(PfdIdentifier::ZULU_SECONDS, d_previous.zuluSeconds, dataToSend);

    util::appendData(PfdIdentifier::LOCAL_SECONDS, d_previous.localSeconds, dataToSend);

    util::appendData(PfdIdentifier::GROUND_SPEED, d_previous.groundSpeed, dataToSend);

    util::appendData(PfdIdentifier::TOTAL_AIR_TEMP, d_previous.totalAirTemp, dataToSend);

    util::appendData(PfdIdentifier::OUTSIDE_AIR_TEMP, d_previous.outsideAirTemp, dataToSend);

    util::appendData(PfdIdentifier::ISA_AIR_TEMP, d_previous.isaAirTemp, dataToSend);

    return dataToSend;
}

}  // namespace bottombar
