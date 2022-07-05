#include "common/dataIdentifiers.hpp"
#include "HsiBrgHandler.hpp"
#include "common/appendData.hpp"

#include <cmath>


namespace hsibrg

{

QByteArray HsiBrgHandler::processData(unsigned long *raw)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));

    QByteArray dataToSend;

    // nav1
    if (std::abs(d_previous.nav1Dme - newData.nav1Dme) >= 0.09)
    {
        d_previous.nav1Dme = newData.nav1Dme;
        util::appendData(PfdIdentifier::NAV1_DME, newData.nav1Dme, dataToSend);
    }
    if (std::abs(d_previous.nav1Radial - newData.nav1Radial) >= 0.0009)
    {
        d_previous.nav1Radial = newData.nav1Radial;
        util::appendData(PfdIdentifier::NAV1_BEARING, newData.nav1Radial, dataToSend);
    }
    if (d_previous.nav1HasNav != newData.nav1HasNav)
    {
        d_previous.nav1HasNav = newData.nav1HasNav;
        util::appendData(PfdIdentifier::NAV1_HAS_NAV, newData.nav1HasNav, dataToSend);
    }
    if (d_previous.nav1HasSignal != newData.nav1HasSignal)
    {
        d_previous.nav1HasSignal = newData.nav1HasSignal;
        util::appendData(PfdIdentifier::NAV1_HAS_SIGNAL, newData.nav1HasSignal, dataToSend);
    }
    if (d_previous.nav1HasDme != newData.nav1HasDme)
    {
        d_previous.nav1HasDme = newData.nav1HasDme;
        util::appendData(PfdIdentifier::NAV1_HAS_DME, newData.nav1HasDme, dataToSend);
    }

    // nav2
    if (std::abs(d_previous.nav2Dme - newData.nav2Dme) >= 0.09)
    {
        d_previous.nav2Dme = newData.nav2Dme;
        util::appendData(PfdIdentifier::NAV2_DME, newData.nav2Dme, dataToSend);
    }
    if (std::abs(d_previous.nav2Radial - newData.nav2Radial) >= 0.0009)
    {
        d_previous.nav2Radial = newData.nav2Radial;
        util::appendData(PfdIdentifier::NAV2_BEARING, newData.nav2Radial, dataToSend);
    }
    if (d_previous.nav2HasNav != newData.nav2HasNav)
    {
        d_previous.nav2HasNav = newData.nav2HasNav;
        util::appendData(PfdIdentifier::NAV2_HAS_NAV, newData.nav2HasNav, dataToSend);
    }
    if (d_previous.nav2HasSignal != newData.nav2HasSignal)
    {
        d_previous.nav2HasSignal = newData.nav2HasSignal;
        util::appendData(PfdIdentifier::NAV2_HAS_SIGNAL, newData.nav2HasSignal, dataToSend);
    }
    if (d_previous.nav2HasDme != newData.nav2HasDme)
    {
        d_previous.nav2HasDme = newData.nav2HasDme;
        util::appendData(PfdIdentifier::NAV2_HAS_DME, newData.nav2HasDme, dataToSend);
    }

    // gps
    if (std::abs(d_previous.gpsNextWpDist - newData.gpsNextWpDist) >= 0.09)
    {
        d_previous.gpsNextWpDist = newData.gpsNextWpDist;
        util::appendData(PfdIdentifier::GPS_DISTANCE, newData.gpsNextWpDist, dataToSend);
    }
    if (std::abs(d_previous.gpsNextWpBearing - newData.gpsNextWpBearing) >= 0.0009)
    {
        d_previous.gpsNextWpBearing = newData.gpsNextWpBearing;
        util::appendData(PfdIdentifier::GPS_BEARING, newData.gpsNextWpBearing, dataToSend);
    }

    // adf
    if (d_previous.adfHasSignal != newData.adfHasSignal)
    {
        d_previous.adfHasSignal = newData.adfHasSignal;
        util::appendData(PfdIdentifier::ADF_HAS_SIGNAL, newData.adfHasSignal, dataToSend);
    }
    if (std::abs(d_previous.adfActiveFreq - newData.adfActiveFreq) >= 0.09)
    {
        d_previous.adfActiveFreq = newData.adfActiveFreq;
        util::appendData(PfdIdentifier::ADF_FREQ, newData.adfActiveFreq, dataToSend);
    }
    if (std::abs(d_previous.adfRadial - newData.adfRadial) >= 0.0009)
    {
        d_previous.adfRadial = newData.adfRadial;
        util::appendData(PfdIdentifier::ADF_RADIAL, newData.adfRadial, dataToSend);
    }


    return dataToSend;
}

}  // namespace hsibrg
