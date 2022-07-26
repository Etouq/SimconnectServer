#include "common/dataIdentifiers.hpp"
#include "HsiBrgHandler.hpp"


namespace hsibrg
{

std::string HsiBrgHandler::sendCurrentData()
{
    std::string dataToSend;
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::NAV1_DME) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.nav1Dme), sizeof(d_previous.nav1Dme));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::NAV1_BEARING) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.nav1Radial), sizeof(d_previous.nav1Radial));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::NAV1_HAS_NAV) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.nav1HasNav), sizeof(d_previous.nav1HasNav));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::NAV1_HAS_SIGNAL) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.nav1HasSignal), sizeof(d_previous.nav1HasSignal));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::NAV1_HAS_DME) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.nav1HasDme), sizeof(d_previous.nav1HasDme));


    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::NAV2_DME) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.nav2Dme), sizeof(d_previous.nav2Dme));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::NAV2_BEARING) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.nav2Radial), sizeof(d_previous.nav2Radial));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::NAV2_HAS_NAV) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.nav2HasNav), sizeof(d_previous.nav2HasNav));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::NAV2_HAS_SIGNAL) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.nav2HasSignal), sizeof(d_previous.nav2HasSignal));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::NAV2_HAS_DME) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.nav2HasDme), sizeof(d_previous.nav2HasDme));


    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::GPS_DISTANCE) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.gpsNextWpDist), sizeof(d_previous.gpsNextWpDist));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::GPS_BEARING) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.gpsNextWpBearing), sizeof(d_previous.gpsNextWpBearing));


    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::ADF_HAS_SIGNAL) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.adfHasSignal), sizeof(d_previous.adfHasSignal));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::ADF_FREQ) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.adfActiveFreq), sizeof(d_previous.adfActiveFreq));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::ADF_RADIAL) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.adfRadial), sizeof(d_previous.adfRadial));


    return dataToSend;
}

}  // namespace hsibrg
