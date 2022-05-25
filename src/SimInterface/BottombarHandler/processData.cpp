#include "../SimInterface.hpp"
#include "BottombarHandler.hpp"
#include "common/dataIdentifiers.hpp"

#include <cmath>

namespace bottombar
{

void BottombarHandler::processData(unsigned long *raw)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));

    SimconnectIds id = SimconnectIds::ZULU_SECONDS;
    QByteArray dataToSend;


    if (d_previous.zuluSeconds != newData.zuluSeconds)
    {
        d_previous.zuluSeconds = newData.zuluSeconds;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.zuluSeconds),
                          sizeof(newData.zuluSeconds));
    }
    if (d_previous.localSeconds != newData.localSeconds)
    {
        d_previous.localSeconds = newData.localSeconds;
        id = SimconnectIds::LOCAL_SECONDS;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.localSeconds),
                          sizeof(newData.localSeconds));
    }

    if (d_previous.groundSpeed != newData.groundSpeed)
    {
        d_previous.groundSpeed = newData.groundSpeed;
        id = SimconnectIds::GROUND_SPEED;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.groundSpeed),
                          sizeof(newData.groundSpeed));
    }
    if (std::abs(d_previous.totalAirTemp - newData.totalAirTemp) >= 0.25)
    {
        d_previous.totalAirTemp = newData.totalAirTemp;
        id = SimconnectIds::TOTAL_AIR_TEMP;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.totalAirTemp),
                          sizeof(newData.totalAirTemp));
    }
    if (std::abs(d_previous.outsideAirTemp - newData.outsideAirTemp) >= 0.25)
    {
        d_previous.outsideAirTemp = newData.outsideAirTemp;
        id = SimconnectIds::OUTSIDE_AIR_TEMP;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.outsideAirTemp),
                          sizeof(newData.outsideAirTemp));
    }
    if (std::abs(d_previous.isaAirTemp - newData.isaAirTemp) >= 0.25)
    {
        d_previous.isaAirTemp = newData.isaAirTemp;
        id = SimconnectIds::ISA_AIR_TEMP;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.isaAirTemp),
                          sizeof(newData.isaAirTemp));
    }

    if (!dataToSend.isEmpty())
        emit d_parent->sendData(dataToSend);
}

}  // namespace bottombar
