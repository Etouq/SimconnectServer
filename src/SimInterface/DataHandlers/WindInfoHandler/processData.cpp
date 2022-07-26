#include "WindInfoHandler.hpp"
#include "common/dataIdentifiers.hpp"

#include <cmath>

namespace windinfo
{

std::string WindInfoHandler::processData(unsigned long *raw)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));

    std::string dataToSend;

    if (std::abs(d_previous.windVelocity - newData.windVelocity) >= 0.1)
    {
        d_previous.windVelocity = newData.windVelocity;
        dataToSend.append({static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::WIND_STRENGTH)});
        dataToSend.append(reinterpret_cast<const char*>(&newData.windVelocity), sizeof(newData.windVelocity));
    }
    if (std::abs(d_previous.windTrueDirection - newData.windTrueDirection) >= 0.1)
    {
        d_previous.windTrueDirection = newData.windTrueDirection;
        dataToSend.append({static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::WIND_TRUE_DIRECTION)});
        dataToSend.append(reinterpret_cast<const char*>(&newData.windTrueDirection), sizeof(newData.windTrueDirection));
    }
    if (std::abs(d_previous.windDirection - newData.windDirection) >= 0.1)
    {
        d_previous.windDirection = newData.windDirection;
        dataToSend.append({static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::WIND_DIRECTION)});
        dataToSend.append(reinterpret_cast<const char*>(&newData.windDirection), sizeof(newData.windDirection));
    }

    return dataToSend;
}

}  // namespace windinfo
