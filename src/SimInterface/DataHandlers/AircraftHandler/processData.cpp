#include "AircraftHandler.hpp"
#include "common/appendData.hpp"
#include "common/dataIdentifiers.hpp"

namespace handler::aircraft
{

QByteArray AircraftHandler::processData(const unsigned long *raw)
{
    DataStruct newData(*reinterpret_cast<const DataStruct *>(raw));
    QByteArray dataToSend;

    d_previous.fuelDensity = newData.fuelDensity;

    if (std::abs(d_previous.fuelLeftQty - newData.fuelLeftQty) >= d_fuelQtyEps)
    {
        d_previous.fuelLeftQty = newData.fuelLeftQty;
        if (d_fuelQtyByWeight)
            newData.fuelLeftQty *= newData.fuelDensity;
        util::appendData(MfdIdentifier::FUEL_LEFT_QTY, newData.fuelLeftQty, dataToSend);
    }

    if (!d_singleTank && std::abs(d_previous.fuelRightQty - newData.fuelRightQty) >= d_fuelQtyEps)
    {
        d_previous.fuelRightQty = newData.fuelRightQty;
        if (d_fuelQtyByWeight)
            newData.fuelRightQty *= newData.fuelDensity;
        util::appendData(MfdIdentifier::FUEL_RIGHT_QTY, newData.fuelRightQty, dataToSend);
    }

    if (d_checkFlaps) [[likely]]
    {
        if (const double avgAngle = (newData.flapsLeftAngle + newData.flapsRightAngle) / 2;
            std::abs(avgAngle - d_flapsAngle) >= 1.0) [[unlikely]]
        {
            d_flapsAngle = avgAngle;
            util::appendData(MfdIdentifier::FLAPS_ANGLE, d_flapsAngle, dataToSend);
        }

        if (d_checkSpoilers) [[unlikely]]
        {
            if (const double avgPct = (newData.spoilerLeftPos + newData.spoilerRightPos) / 2;
                std::abs(avgPct - d_spoilersPct) >= 1.0) [[unlikely]]
            {
                d_spoilersPct = avgPct;
                util::appendData(MfdIdentifier::SPOILERS_PCT, d_spoilersPct, dataToSend);
            }
        }
    }

    if (d_checkElevTrim && (std::abs(d_previous.elevTrimPct - newData.elevTrimPct) >= 0.002 || d_previous.elevTrimAngle != newData.elevTrimAngle)) [[unlikely]]
    {
        d_previous.elevTrimPct = newData.elevTrimPct;
        d_previous.elevTrimAngle = newData.elevTrimAngle;
        util::appendData(MfdIdentifier::ELEV_TRIM_POSITION, newData.elevTrimPct, dataToSend);
        dataToSend.append(reinterpret_cast<const char *>(&newData.elevTrimAngle), sizeof(newData.elevTrimAngle));
    }

    if (d_checkAilTrim && (std::abs(d_previous.ailTrimPct - newData.ailTrimPct) >= 0.002 || d_previous.ailTrimAngle != newData.ailTrimAngle)) [[unlikely]]
    {
        d_previous.ailTrimPct = newData.ailTrimPct;
        d_previous.ailTrimAngle = newData.ailTrimAngle;
        util::appendData(MfdIdentifier::AIL_TRIM_POSITION, newData.ailTrimPct, dataToSend);
        dataToSend.append(reinterpret_cast<const char *>(&newData.ailTrimAngle), sizeof(newData.ailTrimAngle));
    }

    if (d_checkRuddTrim && (std::abs(d_previous.ruddTrimPct - newData.ruddTrimPct) >= 0.002 || d_previous.ruddTrimAngle != newData.ruddTrimAngle)) [[unlikely]]
    {
        d_previous.ruddTrimPct = newData.ruddTrimPct;
        d_previous.ruddTrimAngle = newData.ruddTrimAngle;
        util::appendData(MfdIdentifier::RUDD_TRIM_POSITION, newData.ruddTrimPct, dataToSend);
        dataToSend.append(reinterpret_cast<const char *>(&newData.ruddTrimAngle), sizeof(newData.ruddTrimAngle));
    }

    if (d_checkApu && std::abs(d_previous.apuN1 - newData.apuN1) >= 0.4) [[unlikely]]
    {
        d_previous.apuN1 = newData.apuN1;
        util::appendData(MfdIdentifier::APU_N1, newData.apuN1, dataToSend);
    }

    return dataToSend;
}

}
