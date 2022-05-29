#include "AircraftHandler.hpp"
#include "common/dataIdentifiers.hpp"

#include <cmath>

namespace aircraft::base
{

QByteArray AircraftHandler::processDataBase(const unsigned long *raw)
{
    QByteArray dataToSend;

    DataStruct newData(*reinterpret_cast<const DataStruct *>(raw));
    SimconnectIds id = SimconnectIds::FLAPS_ANGLE;

    if (d_checkFlaps) [[likely]]
    {
        if (const double avgAngle = (newData.flapsLeftAngle + newData.flapsRightAngle) / 2;
            std::abs(avgAngle - d_flapsAngle) >= 1.0) [[unlikely]]
        {
            d_flapsAngle = avgAngle;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&d_flapsAngle), sizeof(d_flapsAngle));
        }

        if (d_checkSpoilers) [[unlikely]]
        {
            if (const double avgPct = (newData.spoilerLeftPos + newData.spoilerRightPos) / 2;
                std::abs(avgPct - d_spoilersPct) >= 1.0) [[unlikely]]
            {
                d_spoilersPct = avgPct;
                id = SimconnectIds::SPOILERS_PCT;
                dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<const char *>(&d_spoilersPct), sizeof(d_spoilersPct));
            }
        }
    }

    if (d_checkElevTrim && std::abs(d_previous.elevTrim - newData.elevTrim) >= 0.002) [[unlikely]]
    {
        d_previous.elevTrim = newData.elevTrim;
        id = SimconnectIds::ELEV_TRIM_PCT;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.elevTrim), sizeof(newData.elevTrim));
    }

    if (d_checkAilTrim && std::abs(d_previous.ailTrim - newData.ailTrim) >= 0.002) [[unlikely]]
    {
        d_previous.ailTrim = newData.ailTrim;
        id = SimconnectIds::AIL_TRIM_PCT;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.ailTrim), sizeof(newData.ailTrim));
    }

    if (d_checkRuddTrim && std::abs(d_previous.ruddTrim - newData.ruddTrim) >= 0.002) [[unlikely]]
    {
        d_previous.ruddTrim = newData.ruddTrim;
        id = SimconnectIds::RUDD_TRIM_PCT;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.ruddTrim), sizeof(newData.ruddTrim));
    }

    d_previous.fuelDensity = newData.fuelDensity;

    if (d_singleTank) [[unlikely]]
    {
        if (std::abs(d_previous.fuelTotalQty - newData.fuelTotalQty) >= d_fuelQtyEps) [[unlikely]]
        {
            d_previous.fuelTotalQty = newData.fuelTotalQty;
            if (d_fuelQtyByWeight)
                newData.fuelTotalQty *= newData.fuelDensity;

            id = SimconnectIds::FUEL_TOTAL_QTY;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&newData.fuelTotalQty), sizeof(newData.fuelTotalQty));
        }
    }
    else [[likely]]
    {
        if (std::abs(d_previous.fuelLeftQty - newData.fuelLeftQty) >= d_fuelQtyEps) [[unlikely]]
        {
            d_previous.fuelLeftQty = newData.fuelLeftQty;
            if (d_fuelQtyByWeight)
                newData.fuelLeftQty *= newData.fuelDensity;

            id = SimconnectIds::FUEL_LEFT_QTY;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&newData.fuelLeftQty), sizeof(newData.fuelLeftQty));
        }

        if (std::abs(d_previous.fuelRightQty - newData.fuelRightQty) >= d_fuelQtyEps) [[unlikely]]
        {
            d_previous.fuelRightQty = newData.fuelRightQty;
            if (d_fuelQtyByWeight)
                newData.fuelRightQty *= newData.fuelDensity;

            id = SimconnectIds::FUEL_RIGHT_QTY;
            dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<const char *>(&newData.fuelRightQty), sizeof(newData.fuelRightQty));
        }
    }

    if (d_checkApu && std::abs(d_previous.apuN1 - newData.apuN1) >= 0.5) [[unlikely]]
    {
        d_previous.apuN1 = newData.apuN1;
        id = SimconnectIds::APU_RPM_PCT;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.apuN1), sizeof(newData.apuN1));
    }


    return dataToSend;
}

}  // namespace aircraft::base
