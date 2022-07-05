#include "MiscHandler.hpp"
#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"

#include <cmath>

namespace misc
{

QByteArray MiscHandler::processData(unsigned long *raw, bool *wpIdValid)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));

    d_previous.totalFuelQty = newData.totalFuelQty;
    d_previous.totalFuelFlow = newData.totalFuelFlow;
    d_previous.groundSpeed = newData.groundSpeed;

    QByteArray dataToSend;
    util::appendData(MfdIdentifier::FUEL_TEXT_DATA, newData.totalFuelQty, dataToSend);
    dataToSend.append(reinterpret_cast<char *>(&newData.totalFuelFlow),
                      sizeof(newData.totalFuelFlow));
    dataToSend.append(reinterpret_cast<char *>(&newData.groundSpeed), sizeof(newData.groundSpeed));


    if (d_previous.hasAp != newData.hasAp)
    {
        d_previous.hasAp = newData.hasAp;
        util::appendData(PfdIdentifier::AP_AVAILABLE, newData.hasAp, dataToSend);
    }

    if (d_previous.com1Avail != newData.com1Avail)
    {
        d_previous.com1Avail = newData.com1Avail;
        util::appendData(TscIdentifier::COM1_AVAIL, newData.com1Avail, dataToSend);
    }

    if (d_previous.com2Avail != newData.com2Avail)
    {
        d_previous.com2Avail = newData.com2Avail;
        util::appendData(TscIdentifier::COM2_AVAIL, newData.com2Avail, dataToSend);
    }
    if (d_previous.com3Avail != newData.com3Avail)
    {
        d_previous.com3Avail = newData.com3Avail;
        util::appendData(TscIdentifier::COM3_AVAIL, newData.com3Avail, dataToSend);
    }

    if (d_previous.nav1Avail != newData.nav1Avail)
    {
        d_previous.nav1Avail = newData.nav1Avail;
        util::appendData(TscIdentifier::NAV1_AVAIL, newData.nav1Avail, dataToSend);
    }

    if (d_previous.nav2Avail != newData.nav2Avail)
    {
        d_previous.nav2Avail = newData.nav2Avail;
        util::appendData(TscIdentifier::NAV2_AVAIL, newData.nav2Avail, dataToSend);
    }
    if (d_previous.xpdrAvail != newData.xpdrAvail)
    {
        d_previous.xpdrAvail = newData.xpdrAvail;
        util::appendData(TscIdentifier::XPDR_AVAIL, newData.xpdrAvail, dataToSend);
    }

    uint8_t size = 0;
    if (d_previous.gpsNextWpId != newData.gpsNextWpId)
    {
        *wpIdValid = newData.gpsNextWpId == "";
        d_previous.gpsNextWpId = newData.gpsNextWpId;
        util::appendData(PfdIdentifier::CURRENT_LEG_TO, newData.gpsNextWpId, dataToSend);
    }

    if (d_previous.nav1Ident != newData.nav1Ident)
    {
        d_previous.nav1Ident = newData.nav1Ident;
        util::appendData(PfdIdentifier::NAV1_IDENT, newData.nav1Ident, dataToSend);
    }

    if (d_previous.nav2Ident != newData.nav2Ident)
    {
        d_previous.nav2Ident = newData.nav2Ident;
        util::appendData(PfdIdentifier::NAV2_IDENT, newData.nav2Ident, dataToSend);
    }

    if (d_previous.gpsPrevWpId != newData.gpsPrevWpId)
    {
        d_previous.gpsPrevWpId = newData.gpsPrevWpId;
        util::appendData(PfdIdentifier::CURRENT_LEG_FROM, newData.gpsPrevWpId, dataToSend);
    }

    return dataToSend;
}

}  // namespace misc
