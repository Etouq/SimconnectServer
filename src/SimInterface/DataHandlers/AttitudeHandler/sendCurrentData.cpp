#include "AttitudeHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace attitude
{

std::string AttitudeHandler::sendCurrentData()
{
    std::string dataToSend;

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::ATTITUDE) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.bank), sizeof(d_previous.bank));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.pitch), sizeof(d_previous.pitch));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.slipskid), sizeof(d_previous.slipskid));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::ANGLE_OF_ATTACK) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.angleOfAttack), sizeof(d_previous.angleOfAttack));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AP_FD_STATUS) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.fdState), sizeof(d_previous.fdState));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::FD_ATTITUDE) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.fdBank), sizeof(d_previous.fdBank));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.fdPitch), sizeof(d_previous.fdPitch));


    return dataToSend;
}

}  // namespace attitude
