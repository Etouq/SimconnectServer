#include "AirspeedHandler.hpp"
#include "common/dataIdentifiers.hpp"

#include <cmath>

namespace airspeed
{

std::string AirspeedHandler::processData(unsigned long *raw)
{
    DataStruct newData(*reinterpret_cast<DataStruct *>(raw));
    std::string dataToSend;

    d_previous.airspeed = newData.airspeed;
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AIRSPEED) });
    dataToSend.append(reinterpret_cast<const char*>(&newData.airspeed), sizeof(newData.airspeed));

    if (std::abs(d_previous.maxSpeed - newData.maxSpeed) >= 0.09)
    {
        d_previous.maxSpeed = newData.maxSpeed;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::MAX_SPEED) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.maxSpeed), sizeof(newData.maxSpeed));
    }

    if (d_previous.trueAirspeed != newData.trueAirspeed)
    {
        d_previous.trueAirspeed = newData.trueAirspeed;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::TRUE_AIRSPEED) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.maxSpeed), sizeof(newData.maxSpeed));
    }

    if (d_previous.refSpeed != newData.refSpeed)
    {
        d_previous.refSpeed = newData.refSpeed;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::REF_SPEED) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.maxSpeed), sizeof(newData.maxSpeed));
    }

    return dataToSend;
}

}  // namespace airspeed
