#include "AttitudeHandler.hpp"
#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"

namespace attitude
{

QByteArray AttitudeHandler::sendCurrentData()
{
    QByteArray dataToSend;

    util::appendData(PfdIdentifier::ATTITUDE, d_previous.bank, dataToSend);
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.pitch), sizeof(d_previous.pitch));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.slipskid), sizeof(d_previous.slipskid));

    util::appendData(PfdIdentifier::ANGLE_OF_ATTACK, d_previous.angleOfAttack, dataToSend);

    util::appendData(PfdIdentifier::AP_FD_STATUS, d_previous.fdState, dataToSend);

    util::appendData(PfdIdentifier::FD_ATTITUDE, d_previous.fdBank, dataToSend);
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.fdPitch), sizeof(d_previous.fdPitch));


    return dataToSend;
}

}  // namespace attitude
