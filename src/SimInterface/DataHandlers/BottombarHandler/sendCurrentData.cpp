#include "BottombarHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace bottombar
{

QByteArray BottombarHandler::sendCurrentData()
{
    SimconnectIds id = SimconnectIds::ZULU_SECONDS;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.zuluSeconds), sizeof(d_previous.zuluSeconds));

    id = SimconnectIds::LOCAL_SECONDS;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.localSeconds), sizeof(d_previous.localSeconds));

    id = SimconnectIds::GROUND_SPEED;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.groundSpeed), sizeof(d_previous.groundSpeed));

    id = SimconnectIds::TOTAL_AIR_TEMP;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.totalAirTemp), sizeof(d_previous.totalAirTemp));

    id = SimconnectIds::OUTSIDE_AIR_TEMP;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.outsideAirTemp), sizeof(d_previous.outsideAirTemp));

    id = SimconnectIds::ISA_AIR_TEMP;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.isaAirTemp), sizeof(d_previous.isaAirTemp));

    return dataToSend;
}

}  // namespace bottombar
