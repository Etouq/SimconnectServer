#include "AirspeedHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace airspeed
{

std::string AirspeedHandler::sendCurrentData()
{
    std::string dataToSend;
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AIRSPEED) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.airspeed), sizeof(d_previous.airspeed));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::MAX_SPEED) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.maxSpeed), sizeof(d_previous.maxSpeed));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::TRUE_AIRSPEED) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.trueAirspeed), sizeof(d_previous.trueAirspeed));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::REF_SPEED) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.refSpeed), sizeof(d_previous.refSpeed));

    return dataToSend;
}

}  // namespace airspeed
