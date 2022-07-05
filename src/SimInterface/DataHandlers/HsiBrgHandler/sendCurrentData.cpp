#include "common/dataIdentifiers.hpp"
#include "HsiBrgHandler.hpp"
#include "common/appendData.hpp"


namespace hsibrg
{

QByteArray HsiBrgHandler::sendCurrentData()
{
    QByteArray dataToSend;
    util::appendData(PfdIdentifier::NAV1_DME, d_previous.nav1Dme, dataToSend);

    util::appendData(PfdIdentifier::NAV1_BEARING, d_previous.nav1Radial, dataToSend);

    util::appendData(PfdIdentifier::NAV1_HAS_NAV, d_previous.nav1HasNav, dataToSend);

    util::appendData(PfdIdentifier::NAV1_HAS_SIGNAL, d_previous.nav1HasSignal, dataToSend);

    util::appendData(PfdIdentifier::NAV1_HAS_DME, d_previous.nav1HasDme, dataToSend);


    util::appendData(PfdIdentifier::NAV2_DME, d_previous.nav2Dme, dataToSend);

    util::appendData(PfdIdentifier::NAV2_BEARING, d_previous.nav2Radial, dataToSend);

    util::appendData(PfdIdentifier::NAV2_HAS_NAV, d_previous.nav2HasNav, dataToSend);

    util::appendData(PfdIdentifier::NAV2_HAS_SIGNAL, d_previous.nav2HasSignal, dataToSend);

    util::appendData(PfdIdentifier::NAV2_HAS_DME, d_previous.nav2HasDme, dataToSend);


    util::appendData(PfdIdentifier::GPS_DISTANCE, d_previous.gpsNextWpDist, dataToSend);

    util::appendData(PfdIdentifier::GPS_BEARING, d_previous.gpsNextWpBearing, dataToSend);


    util::appendData(PfdIdentifier::ADF_HAS_SIGNAL, d_previous.adfHasSignal, dataToSend);

    util::appendData(PfdIdentifier::ADF_FREQ, d_previous.adfActiveFreq, dataToSend);

    util::appendData(PfdIdentifier::ADF_RADIAL, d_previous.adfRadial, dataToSend);


    return dataToSend;
}

}  // namespace hsibrg
