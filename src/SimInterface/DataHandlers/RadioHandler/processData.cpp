#include "common/dataIdentifiers.hpp"
#include "common/TypeEnums.hpp"
#include "RadioHandler.hpp"

#include <cmath>


namespace radio
{

std::string RadioHandler::processData(unsigned long *raw)
{
    DataStruct newData(*reinterpret_cast<DataStruct *>(raw));

    std::string dataToSend;

    if (std::abs(d_previous.com1Freq - newData.com1Freq) >= 0.0009)
    {
        d_previous.com1Freq = newData.com1Freq;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::COM1_FREQ) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.com1Freq), sizeof(newData.com1Freq));
    }
    if (std::abs(d_previous.com2Freq - newData.com2Freq) >= 0.0009)
    {
        d_previous.com2Freq = newData.com2Freq;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::COM2_FREQ) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.com2Freq), sizeof(newData.com2Freq));
    }
    if (std::abs(d_previous.com3Freq - newData.com3Freq) >= 0.0009)
    {
        d_previous.com3Freq = newData.com3Freq;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::COM3_FREQ) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.com3Freq), sizeof(newData.com3Freq));
    }

    if (std::abs(d_previous.nav1Freq - newData.nav1Freq) >= 0.009)
    {
        d_previous.nav1Freq = newData.nav1Freq;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::NAV1_FREQ) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.nav1Freq), sizeof(newData.nav1Freq));
    }
    if (std::abs(d_previous.nav2Freq - newData.nav2Freq) >= 0.009)
    {
        d_previous.nav2Freq = newData.nav2Freq;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::NAV2_FREQ) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.nav2Freq), sizeof(newData.nav2Freq));
    }

    if (std::abs(d_previous.com1Stby - newData.com1Stby) >= 0.0009)
    {
        d_previous.com1Stby = newData.com1Stby;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::COM1_STBY_FREQ) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.com1Stby), sizeof(newData.com1Stby));
    }
    if (std::abs(d_previous.com2Stby - newData.com2Stby) >= 0.0009)
    {
        d_previous.com2Stby = newData.com2Stby;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::COM2_STBY_FREQ) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.com2Stby), sizeof(newData.com2Stby));
    }
    if (std::abs(d_previous.com3Stby - newData.com3Stby) >= 0.0009)
    {
        d_previous.com3Stby = newData.com3Stby;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::COM3_STBY_FREQ) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.com3Stby), sizeof(newData.com3Stby));
    }

    if (std::abs(d_previous.nav1Stby - newData.nav1Stby) >= 0.009)
    {
        d_previous.nav1Stby = newData.nav1Stby;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::NAV1_STBY_FREQ) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.nav1Stby), sizeof(newData.nav1Stby));
    }
    if (std::abs(d_previous.nav2Stby - newData.nav2Stby) >= 0.009)
    {
        d_previous.nav2Stby = newData.nav2Stby;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::NAV2_STBY_FREQ) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.nav2Stby), sizeof(newData.nav2Stby));
    }

    if (d_previous.xpdrCode != newData.xpdrCode)
    {
        d_previous.xpdrCode = newData.xpdrCode;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::XPDR_CODE) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.xpdrCode), sizeof(newData.xpdrCode));
    }

    if (d_previous.xpdrState != newData.xpdrState)
    {
        d_previous.xpdrState = newData.xpdrState;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::XPDR_STATE) });
        dataToSend.push_back(static_cast<char>(static_cast<TransponderState>(newData.xpdrState)));
    }

    return dataToSend;
}

}  // namespace radio
