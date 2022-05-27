#include "common/dataIdentifiers.hpp"
#include "HsiBrgHandler.hpp"

#include <cmath>


namespace hsibrg

{

QByteArray HsiBrgHandler::processData(unsigned long *raw)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));

    SimconnectIds id = SimconnectIds::NAV1_DME;
    QByteArray dataToSend;


    // nav1
    if (std::abs(d_previous.nav1Dme - newData.nav1Dme) >= 0.09)
    {
        d_previous.nav1Dme = newData.nav1Dme;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav1Dme),
                          sizeof(newData.nav1Dme));
    }
    if (std::abs(d_previous.nav1Radial - newData.nav1Radial) >= 0.0009)
    {
        d_previous.nav1Radial = newData.nav1Radial;
        id = SimconnectIds::NAV1_BEARING;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav1Radial),
                          sizeof(newData.nav1Radial));
    }
    if (d_previous.nav1HasNav != newData.nav1HasNav)
    {
        d_previous.nav1HasNav = newData.nav1HasNav;
        id = SimconnectIds::NAV1_HAS_NAV;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav1HasNav),
                          sizeof(newData.nav1HasNav));
    }
    if (d_previous.nav1HasSignal != newData.nav1HasSignal)
    {
        d_previous.nav1HasSignal = newData.nav1HasSignal;
        id = SimconnectIds::NAV1_HAS_SIGNAL;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav1HasSignal),
                          sizeof(newData.nav1HasSignal));
    }
    if (d_previous.nav1HasDme != newData.nav1HasDme)
    {
        d_previous.nav1HasDme = newData.nav1HasDme;
        id = SimconnectIds::NAV1_HAS_DME;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav1HasDme),
                          sizeof(newData.nav1HasDme));
    }

    // nav2
    if (std::abs(d_previous.nav2Dme - newData.nav2Dme) >= 0.09)
    {
        d_previous.nav2Dme = newData.nav2Dme;
        id = SimconnectIds::NAV2_DME;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav2Dme),
                          sizeof(newData.nav2Dme));
    }
    if (std::abs(d_previous.nav2Radial - newData.nav2Radial) >= 0.0009)
    {
        d_previous.nav2Radial = newData.nav2Radial;
        id = SimconnectIds::NAV2_BEARING;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav2Radial),
                          sizeof(newData.nav2Radial));
    }
    if (d_previous.nav2HasNav != newData.nav2HasNav)
    {
        d_previous.nav2HasNav = newData.nav2HasNav;
        id = SimconnectIds::NAV2_HAS_NAV;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav2HasNav),
                          sizeof(newData.nav2HasNav));
    }
    if (d_previous.nav2HasSignal != newData.nav2HasSignal)
    {
        d_previous.nav2HasSignal = newData.nav2HasSignal;
        id = SimconnectIds::NAV2_HAS_SIGNAL;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav2HasSignal),
                          sizeof(newData.nav2HasSignal));
    }
    if (d_previous.nav2HasDme != newData.nav2HasDme)
    {
        d_previous.nav2HasDme = newData.nav2HasDme;
        id = SimconnectIds::NAV2_HAS_DME;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav2HasDme),
                          sizeof(newData.nav2HasDme));
    }

    // gps
    if (std::abs(d_previous.gpsNextWpDist - newData.gpsNextWpDist) >= 0.09)
    {
        d_previous.gpsNextWpDist = newData.gpsNextWpDist;
        id = SimconnectIds::GPS_DISTANCE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.gpsNextWpDist),
                          sizeof(newData.gpsNextWpDist));
    }
    if (std::abs(d_previous.gpsNextWpBearing - newData.gpsNextWpBearing) >= 0.0009)
    {
        d_previous.gpsNextWpBearing = newData.gpsNextWpBearing;
        id = SimconnectIds::GPS_BEARING;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.gpsNextWpBearing),
                          sizeof(newData.gpsNextWpBearing));
    }

    // adf
    if (d_previous.adfHasSignal != newData.adfHasSignal)
    {
        d_previous.adfHasSignal = newData.adfHasSignal;
        id = SimconnectIds::ADF_HAS_SIGNAL;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.adfHasSignal),
                          sizeof(newData.adfHasSignal));
    }
    if (std::abs(d_previous.adfActiveFreq - newData.adfActiveFreq) >= 0.09)
    {
        d_previous.adfActiveFreq = newData.adfActiveFreq;
        id = SimconnectIds::ADF_FREQ;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.adfActiveFreq),
                          sizeof(newData.adfActiveFreq));
    }
    if (std::abs(d_previous.adfRadial - newData.adfRadial) >= 0.0009)
    {
        d_previous.adfRadial = newData.adfRadial;
        id = SimconnectIds::ADF_RADIAL;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.adfRadial),
                          sizeof(newData.adfRadial));
    }


    return dataToSend;
}

}  // namespace hsibrg
