#include "MiscHandler.hpp"
#include "common/dataIdentifiers.hpp"

#include <cmath>

namespace misc
{

QByteArray MiscHandler::processData(unsigned long *raw, bool *wpIdValid)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));

    d_previous.totalFuelQty = newData.totalFuelQty;
    d_previous.totalFuelFlow = newData.totalFuelFlow;
    d_previous.groundSpeed = newData.groundSpeed;

    SimconnectIds id = SimconnectIds::FUEL_TEXT_DATA;
    QByteArray dataToSend(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&newData.totalFuelQty),
                      sizeof(newData.totalFuelQty));
    dataToSend.append(reinterpret_cast<char *>(&newData.totalFuelFlow),
                      sizeof(newData.totalFuelFlow));
    dataToSend.append(reinterpret_cast<char *>(&newData.groundSpeed), sizeof(newData.groundSpeed));


    if (d_previous.hasAp != newData.hasAp)
    {
        d_previous.hasAp = newData.hasAp;
        id = SimconnectIds::AP_AVAILABLE;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.hasAp), sizeof(newData.hasAp));
    }

    if (d_previous.hasCom1 != newData.hasCom1)
    {
        d_previous.hasCom1 = newData.hasCom1;
        id = SimconnectIds::HAS_COM1;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.hasCom1), sizeof(newData.hasCom1));
    }

    if (d_previous.hasCom2 != newData.hasCom2)
    {
        d_previous.hasCom2 = newData.hasCom2;
        id = SimconnectIds::HAS_COM2;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.hasCom2), sizeof(newData.hasCom2));
    }

    if (d_previous.hasNav1 != newData.hasNav1)
    {
        d_previous.hasNav1 = newData.hasNav1;
        id = SimconnectIds::HAS_NAV1;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.hasNav1), sizeof(newData.hasNav1));
    }

    if (d_previous.hasNav2 != newData.hasNav2)
    {
        d_previous.hasNav2 = newData.hasNav2;
        id = SimconnectIds::HAS_NAV2;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.hasNav2), sizeof(newData.hasNav2));
    }

    uint8_t size = 0;
    if (d_previous.gpsNextWpId != newData.gpsNextWpId)
    {
        *wpIdValid = newData.gpsNextWpId == "";
        d_previous.gpsNextWpId = newData.gpsNextWpId;
        id = SimconnectIds::CURRENT_LEG_TO;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        size = newData.gpsNextWpId.size();
        dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
        dataToSend.append(newData.gpsNextWpId.constData(), size);
    }

    if (d_previous.nav1Ident != newData.nav1Ident)
    {
        d_previous.nav1Ident = newData.nav1Ident;
        id = SimconnectIds::NAV1_IDENT;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        size = newData.nav1Ident.size();
        dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
        dataToSend.append(newData.nav1Ident.constData(), size);
    }

    if (d_previous.nav2Ident != newData.nav2Ident)
    {
        d_previous.nav2Ident = newData.nav2Ident;
        id = SimconnectIds::NAV2_IDENT;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        size = newData.nav2Ident.size();
        dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
        dataToSend.append(newData.nav2Ident.constData(), size);
    }

    if (d_previous.gpsPrevWpId != newData.gpsPrevWpId)
    {
        d_previous.gpsPrevWpId = newData.gpsPrevWpId;
        id = SimconnectIds::CURRENT_LEG_FROM;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        size = newData.gpsPrevWpId.size();
        dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
        dataToSend.append(newData.gpsPrevWpId.constData(), size);
    }

    return dataToSend;
}

}  // namespace misc
