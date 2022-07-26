#include "BottombarHandler.hpp"
#include "common/dataIdentifiers.hpp"

#include <cmath>

namespace bottombar
{

std::string BottombarHandler::processData(unsigned long *raw)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));

    std::string dataToSend;

    if (d_previous.zuluSeconds != newData.zuluSeconds)
    {
        d_previous.zuluSeconds = newData.zuluSeconds;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::ZULU_SECONDS) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.zuluSeconds), sizeof(newData.zuluSeconds));
    }
    if (d_previous.localSeconds != newData.localSeconds)
    {
        d_previous.localSeconds = newData.localSeconds;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::LOCAL_SECONDS) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.localSeconds), sizeof(newData.localSeconds));
    }

    if (d_previous.groundSpeed != newData.groundSpeed)
    {
        d_previous.groundSpeed = newData.groundSpeed;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::GROUND_SPEED) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.groundSpeed), sizeof(newData.groundSpeed));
    }
    if (std::abs(d_previous.totalAirTemp - newData.totalAirTemp) >= 0.25)
    {
        d_previous.totalAirTemp = newData.totalAirTemp;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::TOTAL_AIR_TEMP) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.totalAirTemp), sizeof(newData.totalAirTemp));
    }
    if (std::abs(d_previous.outsideAirTemp - newData.outsideAirTemp) >= 0.25)
    {
        d_previous.outsideAirTemp = newData.outsideAirTemp;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::OUTSIDE_AIR_TEMP) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.outsideAirTemp), sizeof(newData.outsideAirTemp));
    }
    if (std::abs(d_previous.isaAirTemp - newData.isaAirTemp) >= 0.25)
    {
        d_previous.isaAirTemp = newData.isaAirTemp;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::ISA_AIR_TEMP) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.isaAirTemp), sizeof(newData.isaAirTemp));
    }

    return dataToSend;
}

}  // namespace bottombar
