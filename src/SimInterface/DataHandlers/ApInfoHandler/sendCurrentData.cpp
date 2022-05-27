#include "ApInfoHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace apinfo
{

QByteArray ApInfoHandler::sendCurrentData()
{
    SimconnectIds id = SimconnectIds::AP_STATUS;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_apMaster), sizeof(d_apMaster));

    id = SimconnectIds::AP_YD_STATUS;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_yawDamper), sizeof(d_yawDamper));

    uint8_t size = d_verticalActive.size();
    id = SimconnectIds::AP_VERTICAL_ACTIVE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
    dataToSend.append(d_verticalActive.constData(), size);

    size = d_modeReference.size();
    id = SimconnectIds::AP_MODE_REFERENCE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
    dataToSend.append(d_modeReference.constData(), size);


    size = d_armed.size();
    id = SimconnectIds::AP_ARMED;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
    dataToSend.append(d_armed.constData(), size);

    size = d_armedReference.size();
    id = SimconnectIds::AP_ARMED_REFERENCE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
    dataToSend.append(d_armedReference.constData(), size);


    size = d_lateralActive.size();
    id = SimconnectIds::AP_LATERAL_ACTIVE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
    dataToSend.append(d_lateralActive.constData(), size);

    size = d_lateralArmed.size();
    id = SimconnectIds::AP_LATERAL_ARMED;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
    dataToSend.append(d_lateralArmed.constData(), size);


    return dataToSend;
}

}  // namespace apinfo
