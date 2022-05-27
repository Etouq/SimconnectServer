#include "AttitudeHandler.hpp"
#include "common/dataIdentifiers.hpp"

#include <cmath>

namespace attitude
{

QByteArray AttitudeHandler::processData(unsigned long *raw)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));

    d_previous.bank = newData.bank;
    d_previous.pitch = newData.pitch;
    d_previous.slipskid = newData.slipskid;

    SimconnectIds id = SimconnectIds::BANK;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&newData.bank), sizeof(newData.bank));

    id = SimconnectIds::PITCH;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&newData.pitch), sizeof(newData.pitch));

    id = SimconnectIds::SLIPSKID;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&newData.slipskid), sizeof(newData.slipskid));

    if (std::abs(d_previous.angleOfAttack - newData.angleOfAttack) >= 0.25)
    {
        d_previous.angleOfAttack = newData.angleOfAttack;
        id = SimconnectIds::ANGLE_OF_ATTACK;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.angleOfAttack),
                          sizeof(newData.angleOfAttack));
    }

    if (d_previous.fdState != newData.fdState)
    {
        d_previous.fdState = newData.fdState;
        id = SimconnectIds::AP_FD_STATUS;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.fdState), sizeof(newData.fdState));
    }

    if (newData.fdState)
    {
        d_previous.fdBank = newData.fdBank;
        d_previous.fdPitch = newData.fdPitch;

        id = SimconnectIds::FD_BANK;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.fdBank), sizeof(newData.fdBank));

        id = SimconnectIds::FD_PITCH;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.fdPitch), sizeof(newData.fdPitch));
    }

    return dataToSend;
}

}  // namespace attitude