#include "common/dataIdentifiers.hpp"
#include "RadioHandler.hpp"

#include <cmath>


namespace radio
{

QByteArray RadioHandler::processData(unsigned long *raw)
{
    DataStruct newData(*reinterpret_cast<DataStruct *>(raw));

    SimconnectIds id = SimconnectIds::COM1_FREQ;
    QByteArray dataToSend;

    if (std::abs(d_previous.com1Freq - newData.com1Freq) >= 0.0009)
    {
        d_previous.com1Freq = newData.com1Freq;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.com1Freq), sizeof(newData.com1Freq));
    }
    if (std::abs(d_previous.com2Freq - newData.com2Freq) >= 0.0009)
    {
        d_previous.com2Freq = newData.com2Freq;
        id = SimconnectIds::COM2_FREQ;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.com2Freq), sizeof(newData.com2Freq));
    }

    if (std::abs(d_previous.nav1Freq - newData.nav1Freq) >= 0.009)
    {
        d_previous.nav1Freq = newData.nav1Freq;
        id = SimconnectIds::NAV1_FREQ;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav1Freq), sizeof(newData.nav1Freq));
    }
    if (std::abs(d_previous.nav2Freq - newData.nav2Freq) >= 0.009)
    {
        d_previous.nav2Freq = newData.nav2Freq;
        id = SimconnectIds::NAV2_FREQ;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav2Freq), sizeof(newData.nav2Freq));
    }

    if (std::abs(d_previous.com1Stby - newData.com1Stby) >= 0.0009)
    {
        d_previous.com1Stby = newData.com1Stby;
        id = SimconnectIds::COM1_STBY;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.com1Stby), sizeof(newData.com1Stby));
    }
    if (std::abs(d_previous.com2Stby - newData.com2Stby) >= 0.0009)
    {
        d_previous.com2Stby = newData.com2Stby;
        id = SimconnectIds::COM2_STBY;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.com2Stby), sizeof(newData.com2Stby));
    }

    if (std::abs(d_previous.nav1Stby - newData.nav1Stby) >= 0.009)
    {
        d_previous.nav1Stby = newData.nav1Stby;
        id = SimconnectIds::NAV1_STBY;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav1Stby), sizeof(newData.nav1Stby));
    }
    if (std::abs(d_previous.nav2Stby - newData.nav2Stby) >= 0.009)
    {
        d_previous.nav2Stby = newData.nav2Stby;
        id = SimconnectIds::NAV2_STBY;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav2Stby), sizeof(newData.nav2Stby));
    }

    if (d_previous.xpdrCode != newData.xpdrCode)
    {
        d_previous.xpdrCode = newData.xpdrCode;
        id = SimconnectIds::XPDR_CODE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.xpdrCode), sizeof(newData.xpdrCode));
    }

    if (d_previous.xpdrState != newData.xpdrState)
    {
        d_previous.xpdrState = newData.xpdrState;
        id = SimconnectIds::XPDR_STATE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.xpdrState), sizeof(newData.xpdrState));
    }

    return dataToSend;
}

}  // namespace radio
