#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"
#include "common/TypeEnums.hpp"
#include "RadioHandler.hpp"

namespace radio
{

QByteArray RadioHandler::sendCurrentData()
{
    QByteArray dataToSend;

    util::appendData(TscIdentifier::COM1_FREQ, d_previous.com1Freq, dataToSend);
    util::appendData(TscIdentifier::COM2_FREQ, d_previous.com2Freq, dataToSend);
    util::appendData(TscIdentifier::COM3_FREQ, d_previous.com3Freq, dataToSend);

    util::appendData(TscIdentifier::NAV1_FREQ, d_previous.nav1Freq, dataToSend);

    util::appendData(TscIdentifier::NAV2_FREQ, d_previous.nav2Freq, dataToSend);

    util::appendData(TscIdentifier::COM1_STBY_FREQ, d_previous.com1Stby, dataToSend);

    util::appendData(TscIdentifier::COM2_STBY_FREQ, d_previous.com2Stby, dataToSend);
    util::appendData(TscIdentifier::COM3_STBY_FREQ, d_previous.com3Stby, dataToSend);

    util::appendData(TscIdentifier::NAV1_STBY_FREQ, d_previous.nav1Stby, dataToSend);

    util::appendData(TscIdentifier::NAV2_STBY_FREQ, d_previous.nav2Stby, dataToSend);

    util::appendData(TscIdentifier::XPDR_CODE, d_previous.xpdrCode, dataToSend);

    util::appendData(TscIdentifier::XPDR_STATE, static_cast<TransponderState>(d_previous.xpdrState), dataToSend);


    return dataToSend;
}

}  // namespace radio
