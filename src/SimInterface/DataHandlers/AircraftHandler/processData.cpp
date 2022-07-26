#include "AircraftHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace handler::aircraft
{

std::string AircraftHandler::processData(const unsigned long *raw)
{
    DataStruct newData(*reinterpret_cast<const DataStruct *>(raw));
    std::string dataToSend;

    d_previous.fuelDensity = newData.fuelDensity;

    if (std::abs(d_previous.fuelLeftQty - newData.fuelLeftQty) >= d_fuelQtyEps)
    {
        d_previous.fuelLeftQty = newData.fuelLeftQty;
        if (d_fuelQtyByWeight)
            newData.fuelLeftQty *= newData.fuelDensity;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::FUEL_LEFT_QTY) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.fuelLeftQty), sizeof(newData.fuelLeftQty));
    }

    if (!d_singleTank && std::abs(d_previous.fuelRightQty - newData.fuelRightQty) >= d_fuelQtyEps)
    {
        d_previous.fuelRightQty = newData.fuelRightQty;
        if (d_fuelQtyByWeight)
            newData.fuelRightQty *= newData.fuelDensity;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::FUEL_RIGHT_QTY) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.fuelRightQty), sizeof(newData.fuelRightQty));
    }

    if (d_checkFlaps) [[likely]]
    {
        if (const double avgAngle = (newData.flapsLeftAngle + newData.flapsRightAngle) / 2;
            std::abs(avgAngle - d_flapsAngle) >= 1.0) [[unlikely]]
        {
            d_flapsAngle = avgAngle;
            dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::FLAPS_ANGLE) });
            dataToSend.append(reinterpret_cast<const char*>(&d_flapsAngle), sizeof(d_flapsAngle));
        }

        if (d_checkSpoilers) [[unlikely]]
        {
            if (const double avgPct = (newData.spoilerLeftPos + newData.spoilerRightPos) / 2;
                std::abs(avgPct - d_spoilersPct) >= 1.0) [[unlikely]]
            {
                d_spoilersPct = avgPct;
                dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::SPOILERS_PCT) });
                dataToSend.append(reinterpret_cast<const char*>(&d_spoilersPct), sizeof(d_spoilersPct));
            }
        }
    }

    if (d_checkElevTrim && (std::abs(d_previous.elevTrimPct - newData.elevTrimPct) >= 0.002 || d_previous.elevTrimAngle != newData.elevTrimAngle)) [[unlikely]]
    {
        d_previous.elevTrimPct = newData.elevTrimPct;
        d_previous.elevTrimAngle = newData.elevTrimAngle;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::ELEV_TRIM_POSITION) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.elevTrimPct), sizeof(newData.elevTrimPct));
        dataToSend.append(reinterpret_cast<const char *>(&newData.elevTrimAngle), sizeof(newData.elevTrimAngle));
    }

    if (d_checkAilTrim && (std::abs(d_previous.ailTrimPct - newData.ailTrimPct) >= 0.002 || d_previous.ailTrimAngle != newData.ailTrimAngle)) [[unlikely]]
    {
        d_previous.ailTrimPct = newData.ailTrimPct;
        d_previous.ailTrimAngle = newData.ailTrimAngle;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::AIL_TRIM_POSITION) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.ailTrimPct), sizeof(newData.ailTrimPct));
        dataToSend.append(reinterpret_cast<const char *>(&newData.ailTrimAngle), sizeof(newData.ailTrimAngle));
    }

    if (d_checkRuddTrim && (std::abs(d_previous.ruddTrimPct - newData.ruddTrimPct) >= 0.002 || d_previous.ruddTrimAngle != newData.ruddTrimAngle)) [[unlikely]]
    {
        d_previous.ruddTrimPct = newData.ruddTrimPct;
        d_previous.ruddTrimAngle = newData.ruddTrimAngle;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::RUDD_TRIM_POSITION) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.ruddTrimPct), sizeof(newData.ruddTrimPct));
        dataToSend.append(reinterpret_cast<const char *>(&newData.ruddTrimAngle), sizeof(newData.ruddTrimAngle));
    }

    if (d_checkApu && std::abs(d_previous.apuN1 - newData.apuN1) >= 0.4) [[unlikely]]
    {
        d_previous.apuN1 = newData.apuN1;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::APU_N1) });
        dataToSend.append(reinterpret_cast<const char*>(&newData.apuN1), sizeof(newData.apuN1));
    }

    return dataToSend;
}

}
