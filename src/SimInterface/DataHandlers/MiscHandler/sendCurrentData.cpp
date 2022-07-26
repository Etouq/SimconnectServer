#include "MiscHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace misc
{

std::string MiscHandler::sendCurrentData()
{
    std::string dataToSend;
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::FUEL_TEXT_DATA) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.totalFuelQty), sizeof(d_previous.totalFuelQty));
    dataToSend.append(reinterpret_cast<char *>(&d_previous.totalFuelFlow), sizeof(d_previous.totalFuelFlow));
    dataToSend.append(reinterpret_cast<char *>(&d_previous.groundSpeed), sizeof(d_previous.groundSpeed));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::AP_AVAILABLE) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.hasAp), sizeof(d_previous.hasAp));


    dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::COM1_AVAIL) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.com1Avail), sizeof(d_previous.com1Avail));
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::COM2_AVAIL) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.com2Avail), sizeof(d_previous.com2Avail));
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::COM3_AVAIL) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.com3Avail), sizeof(d_previous.com3Avail));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::NAV1_AVAIL) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.nav1Avail), sizeof(d_previous.nav1Avail));
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::NAV2_AVAIL) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.nav2Avail), sizeof(d_previous.nav2Avail));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::XPDR_AVAIL) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.xpdrAvail), sizeof(d_previous.xpdrAvail));


    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::CURRENT_LEG_TO) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.gpsNextWpId), sizeof(d_previous.gpsNextWpId));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::NAV1_IDENT) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.nav1Ident), sizeof(d_previous.nav1Ident));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::NAV2_IDENT) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.nav2Ident), sizeof(d_previous.nav2Ident));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::PFD_DATA), static_cast<char>(PfdIdentifier::CURRENT_LEG_FROM) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.gpsPrevWpId), sizeof(d_previous.gpsPrevWpId));


    return dataToSend;
}

}  // namespace misc
