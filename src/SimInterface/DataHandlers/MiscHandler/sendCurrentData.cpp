#include "MiscHandler.hpp"
#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"

namespace misc
{

QByteArray MiscHandler::sendCurrentData()
{
    QByteArray dataToSend;
    util::appendData(MfdIdentifier::FUEL_TEXT_DATA, d_previous.totalFuelQty, dataToSend);
    dataToSend.append(reinterpret_cast<char *>(&d_previous.totalFuelFlow), sizeof(d_previous.totalFuelFlow));
    dataToSend.append(reinterpret_cast<char *>(&d_previous.groundSpeed), sizeof(d_previous.groundSpeed));

    util::appendData(PfdIdentifier::AP_AVAILABLE, d_previous.hasAp, dataToSend);


    util::appendData(TscIdentifier::COM1_AVAIL, d_previous.com1Avail, dataToSend);
    util::appendData(TscIdentifier::COM2_AVAIL, d_previous.com2Avail, dataToSend);
    util::appendData(TscIdentifier::COM3_AVAIL, d_previous.com3Avail, dataToSend);

    util::appendData(TscIdentifier::NAV1_AVAIL, d_previous.nav1Avail, dataToSend);
    util::appendData(TscIdentifier::NAV2_AVAIL, d_previous.nav2Avail, dataToSend);

    util::appendData(TscIdentifier::XPDR_AVAIL, d_previous.xpdrAvail, dataToSend);


    util::appendData(PfdIdentifier::CURRENT_LEG_TO, d_previous.gpsNextWpId, dataToSend);

    util::appendData(PfdIdentifier::NAV1_IDENT, d_previous.nav1Ident, dataToSend);

    util::appendData(PfdIdentifier::NAV2_IDENT, d_previous.nav2Ident, dataToSend);

    util::appendData(PfdIdentifier::CURRENT_LEG_FROM, d_previous.gpsPrevWpId, dataToSend);


    return dataToSend;
}

}  // namespace misc
