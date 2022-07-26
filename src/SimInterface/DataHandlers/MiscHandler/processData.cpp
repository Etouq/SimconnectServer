#include "MiscHandler.hpp"
#include "common/dataIdentifiers.hpp"

#include <cmath>

namespace misc
{

std::string MiscHandler::processData(unsigned long *raw, bool *wpIdValid)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));

    d_previous.totalFuelQty = newData.totalFuelQty;
    d_previous.totalFuelFlow = newData.totalFuelFlow;
    d_previous.groundSpeed = newData.groundSpeed;

    std::string dataToSend;
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::FUEL_TEXT_DATA) });
    dataToSend.append(reinterpret_cast<const char*>(&newData.totalFuelQty), sizeof(newData.totalFuelQty));
    dataToSend.append(reinterpret_cast<char *>(&newData.totalFuelFlow),
                      sizeof(newData.totalFuelFlow));
    dataToSend.append(reinterpret_cast<char *>(&newData.groundSpeed), sizeof(newData.groundSpeed));


    if (d_previous.hasAp != newData.hasAp)
    {
        d_previous.hasAp = newData.hasAp;
        static constexpr DataGroupIdentifier groupId = DataGroupIdentifier::PFD_DATA;
        static constexpr PfdIdentifier id = PfdIdentifier::AP_AVAILABLE;
        dataToSend.append(reinterpret_cast<const char*>(&groupId), sizeof(groupId));
        dataToSend.append(reinterpret_cast<const char*>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char*>(&newData.hasAp), sizeof(newData.hasAp));
    }

    if (d_previous.com1Avail != newData.com1Avail)
    {
        d_previous.com1Avail = newData.com1Avail;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::COM1_AVAIL) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.com1Avail), sizeof(newData.com1Avail));
    }

    if (d_previous.com2Avail != newData.com2Avail)
    {
        d_previous.com2Avail = newData.com2Avail;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::COM2_AVAIL) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.com2Avail), sizeof(newData.com2Avail));
    }
    if (d_previous.com3Avail != newData.com3Avail)
    {
        d_previous.com3Avail = newData.com3Avail;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::COM3_AVAIL) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.com3Avail), sizeof(newData.com3Avail));
    }

    if (d_previous.nav1Avail != newData.nav1Avail)
    {
        d_previous.nav1Avail = newData.nav1Avail;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::NAV1_AVAIL) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.nav1Avail), sizeof(newData.nav1Avail));
    }

    if (d_previous.nav2Avail != newData.nav2Avail)
    {
        d_previous.nav2Avail = newData.nav2Avail;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::NAV2_AVAIL) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.nav2Avail), sizeof(newData.nav2Avail));
    }
    if (d_previous.xpdrAvail != newData.xpdrAvail)
    {
        d_previous.xpdrAvail = newData.xpdrAvail;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::TSC_DATA), static_cast<char>(TscIdentifier::XPDR_AVAIL) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.xpdrAvail), sizeof(newData.xpdrAvail));
    }

    uint8_t size = 0;
    if (d_previous.gpsNextWpId != newData.gpsNextWpId)
    {
        *wpIdValid = newData.gpsNextWpId == "";
        d_previous.gpsNextWpId = newData.gpsNextWpId;
        static constexpr DataGroupIdentifier groupId = DataGroupIdentifier::PFD_DATA;
        static constexpr PfdIdentifier id = PfdIdentifier::CURRENT_LEG_TO;
        dataToSend.append(reinterpret_cast<const char*>(&groupId), sizeof(groupId));
        dataToSend.append(reinterpret_cast<const char*>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char*>(&newData.gpsNextWpId), sizeof(newData.gpsNextWpId));
    }

    if (d_previous.nav1Ident != newData.nav1Ident)
    {
        d_previous.nav1Ident = newData.nav1Ident;
        static constexpr DataGroupIdentifier groupId = DataGroupIdentifier::PFD_DATA;
        static constexpr PfdIdentifier id = PfdIdentifier::NAV1_IDENT;
        dataToSend.append(reinterpret_cast<const char*>(&groupId), sizeof(groupId));
        dataToSend.append(reinterpret_cast<const char*>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char*>(&newData.nav1Ident), sizeof(newData.nav1Ident));
    }

    if (d_previous.nav2Ident != newData.nav2Ident)
    {
        d_previous.nav2Ident = newData.nav2Ident;
        static constexpr DataGroupIdentifier groupId = DataGroupIdentifier::PFD_DATA;
        static constexpr PfdIdentifier id = PfdIdentifier::NAV2_IDENT;
        dataToSend.append(reinterpret_cast<const char*>(&groupId), sizeof(groupId));
        dataToSend.append(reinterpret_cast<const char*>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char*>(&newData.nav2Ident), sizeof(newData.nav2Ident));
    }

    if (d_previous.gpsPrevWpId != newData.gpsPrevWpId)
    {
        d_previous.gpsPrevWpId = newData.gpsPrevWpId;
        static constexpr DataGroupIdentifier groupId = DataGroupIdentifier::PFD_DATA;
        static constexpr PfdIdentifier id = PfdIdentifier::CURRENT_LEG_FROM;
        dataToSend.append(reinterpret_cast<const char*>(&groupId), sizeof(groupId));
        dataToSend.append(reinterpret_cast<const char*>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char*>(&newData.gpsPrevWpId), sizeof(newData.gpsPrevWpId));
    }

    return dataToSend;
}

}  // namespace misc
