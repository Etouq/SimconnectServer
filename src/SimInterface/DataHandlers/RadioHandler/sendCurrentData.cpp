#include "common/dataIdentifiers.hpp"
#include "RadioHandler.hpp"

namespace radio
{

QByteArray RadioHandler::sendCurrentData()
{
    SimconnectIds id = SimconnectIds::COM1_FREQ;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.com1Freq), sizeof(d_previous.com1Freq));

    id = SimconnectIds::COM2_FREQ;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.com2Freq), sizeof(d_previous.com2Freq));

    id = SimconnectIds::NAV1_FREQ;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.nav1Freq), sizeof(d_previous.nav1Freq));

    id = SimconnectIds::NAV2_FREQ;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.nav2Freq), sizeof(d_previous.nav2Freq));

    id = SimconnectIds::COM1_STBY;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.com1Stby), sizeof(d_previous.com1Stby));

    id = SimconnectIds::COM2_STBY;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.com2Stby), sizeof(d_previous.com2Stby));

    id = SimconnectIds::NAV1_STBY;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.nav1Stby), sizeof(d_previous.nav1Stby));

    id = SimconnectIds::NAV2_STBY;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.nav2Stby), sizeof(d_previous.nav2Stby));

    id = SimconnectIds::XPDR_CODE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.xpdrCode), sizeof(d_previous.xpdrCode));

    id = SimconnectIds::XPDR_STATE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.xpdrState), sizeof(d_previous.xpdrState));


    return dataToSend;
}

}  // namespace radio
