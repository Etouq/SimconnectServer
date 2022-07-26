#include "AttitudeHandler.hpp"
#include "common/dataIdentifiers.hpp"

#include <cmath>

namespace attitude
{

std::string AttitudeHandler::processData(unsigned long *raw)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));

    d_previous.bank = newData.bank;
    d_previous.pitch = newData.pitch;
    d_previous.slipskid = newData.slipskid;

    std::string dataToSend;

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::ATTITUDE) });
    dataToSend.append(reinterpret_cast<const char*>(&newData.bank), sizeof(newData.bank));
    dataToSend.append(reinterpret_cast<const char *>(&newData.pitch), sizeof(newData.pitch));
    dataToSend.append(reinterpret_cast<const char *>(&newData.slipskid), sizeof(newData.slipskid));


    if (std::abs(d_previous.angleOfAttack - newData.angleOfAttack) >= 0.25)
    {
        d_previous.angleOfAttack = newData.angleOfAttack;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::ANGLE_OF_ATTACK) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.angleOfAttack), sizeof(newData.angleOfAttack));
    }

    if (d_previous.fdState != newData.fdState)
    {
        d_previous.fdState = newData.fdState;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AP_FD_STATUS) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.fdState), sizeof(newData.fdState));
    }

    if (newData.fdState)
    {
        d_previous.fdBank = newData.fdBank;
        d_previous.fdPitch = newData.fdPitch;

        dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::FD_ATTITUDE) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.fdBank), sizeof(newData.fdBank));
        dataToSend.append(reinterpret_cast<const char *>(&newData.fdPitch), sizeof(newData.fdPitch));
    }

    return dataToSend;
}

}  // namespace attitude