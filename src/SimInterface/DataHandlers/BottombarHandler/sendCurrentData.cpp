#include "BottombarHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace bottombar
{

std::string BottombarHandler::sendCurrentData()
{
    std::string dataToSend;
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::ZULU_SECONDS) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.zuluSeconds), sizeof(d_previous.zuluSeconds));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::LOCAL_SECONDS) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.localSeconds), sizeof(d_previous.localSeconds));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::GROUND_SPEED) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.groundSpeed), sizeof(d_previous.groundSpeed));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::TOTAL_AIR_TEMP) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.totalAirTemp), sizeof(d_previous.totalAirTemp));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::OUTSIDE_AIR_TEMP) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.outsideAirTemp), sizeof(d_previous.outsideAirTemp));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::ISA_AIR_TEMP) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.isaAirTemp), sizeof(d_previous.isaAirTemp));

    return dataToSend;
}

}  // namespace bottombar
