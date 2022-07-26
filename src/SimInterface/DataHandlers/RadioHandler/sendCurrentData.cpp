#include "common/dataIdentifiers.hpp"
#include "common/TypeEnums.hpp"
#include "RadioHandler.hpp"

namespace radio
{

std::string RadioHandler::sendCurrentData()
{
    std::string dataToSend;

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::COM1_FREQ) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.com1Freq), sizeof(d_previous.com1Freq));
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::COM2_FREQ) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.com2Freq), sizeof(d_previous.com2Freq));
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::COM3_FREQ) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.com3Freq), sizeof(d_previous.com3Freq));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::NAV1_FREQ) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.nav1Freq), sizeof(d_previous.nav1Freq));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::NAV2_FREQ) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.nav2Freq), sizeof(d_previous.nav2Freq));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::COM1_STBY_FREQ) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.com1Stby), sizeof(d_previous.com1Stby));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::COM2_STBY_FREQ) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.com2Stby), sizeof(d_previous.com2Stby));
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::COM3_STBY_FREQ) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.com3Stby), sizeof(d_previous.com3Stby));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::NAV1_STBY_FREQ) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.nav1Stby), sizeof(d_previous.nav1Stby));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::NAV2_STBY_FREQ) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.nav2Stby), sizeof(d_previous.nav2Stby));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::XPDR_CODE) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.xpdrCode), sizeof(d_previous.xpdrCode));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::XPDR_STATE) });
    dataToSend.push_back(static_cast<char>(static_cast<TransponderState>(d_previous.xpdrState)));


    return dataToSend;
}

}  // namespace radio
