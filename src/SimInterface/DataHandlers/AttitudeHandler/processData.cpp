#include "AttitudeHandler.hpp"
#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"

#include <cmath>

namespace attitude
{

QByteArray AttitudeHandler::processData(unsigned long *raw)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));

    d_previous.bank = newData.bank;
    d_previous.pitch = newData.pitch;
    d_previous.slipskid = newData.slipskid;

    QByteArray dataToSend;

    util::appendData(PfdIdentifier::ATTITUDE, newData.bank, dataToSend);
    dataToSend.append(reinterpret_cast<const char *>(&newData.pitch), sizeof(newData.pitch));
    dataToSend.append(reinterpret_cast<const char *>(&newData.slipskid), sizeof(newData.slipskid));


    if (std::abs(d_previous.angleOfAttack - newData.angleOfAttack) >= 0.25)
    {
        d_previous.angleOfAttack = newData.angleOfAttack;
        util::appendData(PfdIdentifier::ANGLE_OF_ATTACK, newData.angleOfAttack, dataToSend);
    }

    if (d_previous.fdState != newData.fdState)
    {
        d_previous.fdState = newData.fdState;
        util::appendData(PfdIdentifier::AP_FD_STATUS, newData.fdState, dataToSend);
    }

    if (newData.fdState)
    {
        d_previous.fdBank = newData.fdBank;
        d_previous.fdPitch = newData.fdPitch;

        util::appendData(PfdIdentifier::FD_ATTITUDE, newData.fdBank, dataToSend);
        dataToSend.append(reinterpret_cast<const char *>(&newData.fdPitch), sizeof(newData.fdPitch));
    }

    return dataToSend;
}

}  // namespace attitude