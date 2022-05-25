#include "../SimInterface.hpp"
#include "AttitudeHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace attitude
{

void AttitudeHandler::sendCurrentData()
{
    SimconnectIds id = SimconnectIds::BANK;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.bank), sizeof(d_previous.bank));

    id = SimconnectIds::PITCH;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.pitch), sizeof(d_previous.pitch));

    id = SimconnectIds::SLIPSKID;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.slipskid), sizeof(d_previous.slipskid));

    id = SimconnectIds::ANGLE_OF_ATTACK;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.angleOfAttack), sizeof(d_previous.angleOfAttack));


    id = SimconnectIds::AP_FD_STATUS;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.fdState), sizeof(d_previous.fdState));

    id = SimconnectIds::FD_BANK;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.fdBank), sizeof(d_previous.fdBank));

    id = SimconnectIds::FD_PITCH;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.fdPitch), sizeof(d_previous.fdPitch));


    emit d_parent->sendData(dataToSend);
}

}  // namespace attitude
