#include "MiscHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace misc
{

QByteArray MiscHandler::sendCurrentData()
{
    SimconnectIds id = SimconnectIds::FUEL_TEXT_DATA;

    QByteArray dataToSend(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&d_previous.totalFuelQty), sizeof(d_previous.totalFuelQty));
    dataToSend.append(reinterpret_cast<char *>(&d_previous.totalFuelFlow), sizeof(d_previous.totalFuelFlow));
    dataToSend.append(reinterpret_cast<char *>(&d_previous.groundSpeed), sizeof(d_previous.groundSpeed));

    id = SimconnectIds::AP_AVAILABLE;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&d_previous.hasAp), sizeof(d_previous.hasAp));


    id = SimconnectIds::HAS_COM1;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&d_previous.hasCom1), sizeof(d_previous.hasCom1));

    id = SimconnectIds::HAS_COM2;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&d_previous.hasCom2), sizeof(d_previous.hasCom2));

    id = SimconnectIds::HAS_NAV1;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&d_previous.hasNav1), sizeof(d_previous.hasNav1));

    id = SimconnectIds::HAS_NAV2;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&d_previous.hasNav2), sizeof(d_previous.hasNav2));


    id = SimconnectIds::CURRENT_LEG_TO;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    uint8_t size = d_previous.gpsNextWpId.size();
    dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
    dataToSend.append(d_previous.gpsNextWpId.constData(), size);

    id = SimconnectIds::NAV1_IDENT;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    size = d_previous.nav1Ident.size();
    dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
    dataToSend.append(d_previous.nav1Ident.constData(), size);

    id = SimconnectIds::NAV2_IDENT;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    size = d_previous.nav2Ident.size();
    dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
    dataToSend.append(d_previous.nav2Ident.constData(), size);

    id = SimconnectIds::CURRENT_LEG_FROM;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    size = d_previous.gpsPrevWpId.size();
    dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
    dataToSend.append(d_previous.gpsPrevWpId.constData(), size);


    return dataToSend;
}

}  // namespace misc
