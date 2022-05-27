#include "common/dataIdentifiers.hpp"
#include "HsiBrgHandler.hpp"


namespace hsibrg
{

QByteArray HsiBrgHandler::sendCurrentData()
{
    SimconnectIds id = SimconnectIds::NAV1_DME;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.nav1Dme), sizeof(d_previous.nav1Dme));

    id = SimconnectIds::NAV1_BEARING;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.nav1Radial), sizeof(d_previous.nav1Radial));

    id = SimconnectIds::NAV1_HAS_NAV;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.nav1HasNav), sizeof(d_previous.nav1HasNav));

    id = SimconnectIds::NAV1_HAS_SIGNAL;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.nav1HasSignal), sizeof(d_previous.nav1HasSignal));

    id = SimconnectIds::NAV1_HAS_DME;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.nav1HasDme), sizeof(d_previous.nav1HasDme));


    id = SimconnectIds::NAV2_DME;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.nav2Dme), sizeof(d_previous.nav2Dme));

    id = SimconnectIds::NAV2_BEARING;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.nav2Radial), sizeof(d_previous.nav2Radial));

    id = SimconnectIds::NAV2_HAS_NAV;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.nav2HasNav), sizeof(d_previous.nav2HasNav));

    id = SimconnectIds::NAV2_HAS_SIGNAL;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.nav2HasSignal), sizeof(d_previous.nav2HasSignal));

    id = SimconnectIds::NAV2_HAS_DME;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.nav2HasDme), sizeof(d_previous.nav2HasDme));


    id = SimconnectIds::GPS_DISTANCE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.gpsNextWpDist), sizeof(d_previous.gpsNextWpDist));

    id = SimconnectIds::GPS_BEARING;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.gpsNextWpBearing),
                      sizeof(d_previous.gpsNextWpBearing));


    id = SimconnectIds::ADF_HAS_SIGNAL;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.adfHasSignal), sizeof(d_previous.adfHasSignal));

    id = SimconnectIds::ADF_FREQ;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.adfActiveFreq), sizeof(d_previous.adfActiveFreq));

    id = SimconnectIds::ADF_RADIAL;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.adfRadial), sizeof(d_previous.adfRadial));


    return dataToSend;
}

}  // namespace hsibrg
