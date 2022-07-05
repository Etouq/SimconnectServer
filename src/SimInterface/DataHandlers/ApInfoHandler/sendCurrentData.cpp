#include "ApInfoHandler.hpp"
#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"

namespace apinfo
{

QByteArray ApInfoHandler::sendCurrentData()
{
    QByteArray dataToSend;
    util::appendData(PfdIdentifier::AP_STATUS, d_apMaster, dataToSend);

    util::appendData(PfdIdentifier::AP_YD_STATUS, d_yawDamper, dataToSend);

    util::appendData(PfdIdentifier::AP_FLC, d_flc, dataToSend);

    util::appendData(PfdIdentifier::AP_VERTICAL_ACTIVE, d_verticalActive, dataToSend);

    util::appendData(PfdIdentifier::AP_MODE_REFERENCE, d_modeReference, dataToSend);


    util::appendData(PfdIdentifier::AP_ARMED, d_armed, dataToSend);

    util::appendData(PfdIdentifier::AP_ARMED_REFERENCE, d_armedReference, dataToSend);


    util::appendData(PfdIdentifier::AP_LATERAL_ACTIVE, d_lateralActive, dataToSend);

    util::appendData(PfdIdentifier::AP_LATERAL_ARMED, d_lateralArmed, dataToSend);


    return dataToSend;
}

}  // namespace apinfo
