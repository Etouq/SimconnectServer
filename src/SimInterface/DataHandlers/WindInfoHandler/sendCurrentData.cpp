#include "WindInfoHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace windinfo
{

std::string WindInfoHandler::sendCurrentData()
{
    std::string dataToSend;
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::WIND_STRENGTH) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.windVelocity), sizeof(d_previous.windVelocity));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::WIND_TRUE_DIRECTION) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.windTrueDirection), sizeof(d_previous.windTrueDirection));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::WIND_DIRECTION) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.windDirection), sizeof(d_previous.windDirection));

    return dataToSend;
}

}  // namespace windinfo
