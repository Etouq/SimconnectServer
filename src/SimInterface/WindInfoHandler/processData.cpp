#include "../SimInterface.hpp"
#include "common/dataIdentifiers.hpp"
#include "WindInfoHandler.hpp"

#include <cmath>


namespace windinfo
{

void WindInfoHandler::processData(unsigned long *raw)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));

    SimconnectIds id = SimconnectIds::WIND_STRENGTH;
    QByteArray dataToSend;

    if (std::abs(d_previous.windVelocity - newData.windVelocity) >= 0.1)
    {
        d_previous.windVelocity = newData.windVelocity;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.windVelocity), sizeof(newData.windVelocity));
    }
    if (std::abs(d_previous.windTrueDirection - newData.windTrueDirection) >= 0.1)
    {
        d_previous.windTrueDirection = newData.windTrueDirection;
        id = SimconnectIds::WIND_TRUE_DIRECTION;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.windTrueDirection),
                          sizeof(newData.windTrueDirection));
    }
    if (std::abs(d_previous.windDirection - newData.windDirection) >= 0.1)
    {
        d_previous.windDirection = newData.windDirection;
        id = SimconnectIds::WIND_DIRECTION;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.windDirection), sizeof(newData.windDirection));
    }

    if (!dataToSend.isEmpty())
        emit d_parent->sendData(dataToSend);
}

}  // namespace windinfo
