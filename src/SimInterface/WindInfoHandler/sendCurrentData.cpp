#include "../SimInterface.hpp"
#include "common/dataIdentifiers.hpp"
#include "WindInfoHandler.hpp"


namespace windinfo
{

void WindInfoHandler::sendCurrentData()
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

    emit d_parent->sendData(dataToSend);
}

}  // namespace windinfo
