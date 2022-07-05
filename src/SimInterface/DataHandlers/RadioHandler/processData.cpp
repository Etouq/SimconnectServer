#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"
#include "common/TypeEnums.hpp"
#include "RadioHandler.hpp"

#include <cmath>


namespace radio
{

QByteArray RadioHandler::processData(unsigned long *raw)
{
    DataStruct newData(*reinterpret_cast<DataStruct *>(raw));

    QByteArray dataToSend;

    if (std::abs(d_previous.com1Freq - newData.com1Freq) >= 0.0009)
    {
        d_previous.com1Freq = newData.com1Freq;
        util::appendData(TscIdentifier::COM1_FREQ, newData.com1Freq, dataToSend);
    }
    if (std::abs(d_previous.com2Freq - newData.com2Freq) >= 0.0009)
    {
        d_previous.com2Freq = newData.com2Freq;
        util::appendData(TscIdentifier::COM2_FREQ, newData.com2Freq, dataToSend);
    }
    if (std::abs(d_previous.com3Freq - newData.com3Freq) >= 0.0009)
    {
        d_previous.com3Freq = newData.com3Freq;
        util::appendData(TscIdentifier::COM3_FREQ, newData.com3Freq, dataToSend);
    }

    if (std::abs(d_previous.nav1Freq - newData.nav1Freq) >= 0.009)
    {
        d_previous.nav1Freq = newData.nav1Freq;
        util::appendData(TscIdentifier::NAV1_FREQ, newData.nav1Freq, dataToSend);
    }
    if (std::abs(d_previous.nav2Freq - newData.nav2Freq) >= 0.009)
    {
        d_previous.nav2Freq = newData.nav2Freq;
        util::appendData(TscIdentifier::NAV2_FREQ, newData.nav2Freq, dataToSend);
    }

    if (std::abs(d_previous.com1Stby - newData.com1Stby) >= 0.0009)
    {
        d_previous.com1Stby = newData.com1Stby;
        util::appendData(TscIdentifier::COM1_STBY_FREQ, newData.com1Stby, dataToSend);
    }
    if (std::abs(d_previous.com2Stby - newData.com2Stby) >= 0.0009)
    {
        d_previous.com2Stby = newData.com2Stby;
        util::appendData(TscIdentifier::COM2_STBY_FREQ, newData.com2Stby, dataToSend);
    }
    if (std::abs(d_previous.com3Stby - newData.com3Stby) >= 0.0009)
    {
        d_previous.com3Stby = newData.com3Stby;
        util::appendData(TscIdentifier::COM3_STBY_FREQ, newData.com3Stby, dataToSend);
    }

    if (std::abs(d_previous.nav1Stby - newData.nav1Stby) >= 0.009)
    {
        d_previous.nav1Stby = newData.nav1Stby;
        util::appendData(TscIdentifier::NAV1_STBY_FREQ, newData.nav1Stby, dataToSend);
    }
    if (std::abs(d_previous.nav2Stby - newData.nav2Stby) >= 0.009)
    {
        d_previous.nav2Stby = newData.nav2Stby;
        util::appendData(TscIdentifier::NAV2_STBY_FREQ, newData.nav2Stby, dataToSend);
    }

    if (d_previous.xpdrCode != newData.xpdrCode)
    {
        d_previous.xpdrCode = newData.xpdrCode;
        util::appendData(TscIdentifier::XPDR_CODE, newData.xpdrCode, dataToSend);
    }

    if (d_previous.xpdrState != newData.xpdrState)
    {
        d_previous.xpdrState = newData.xpdrState;
        util::appendData(TscIdentifier::XPDR_STATE, static_cast<TransponderState>(newData.xpdrState), dataToSend);
    }

    return dataToSend;
}

}  // namespace radio
