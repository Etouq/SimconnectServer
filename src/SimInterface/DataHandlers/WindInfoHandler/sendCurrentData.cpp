#include "WindInfoHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace windinfo
{

QByteArray WindInfoHandler::sendCurrentData()
{
    SimconnectIds id = SimconnectIds::WIND_STRENGTH;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.windVelocity), sizeof(d_previous.windVelocity));

    id = SimconnectIds::WIND_TRUE_DIRECTION;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.windTrueDirection),
                      sizeof(d_previous.windTrueDirection));

    id = SimconnectIds::WIND_DIRECTION;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.windDirection), sizeof(d_previous.windDirection));

    return dataToSend;
}

}  // namespace windinfo
