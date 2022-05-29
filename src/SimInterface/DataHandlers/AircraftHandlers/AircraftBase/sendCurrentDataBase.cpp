#include "AircraftHandler.hpp"
#include "common/dataIdentifiers.hpp"

#include <cmath>


namespace aircraft::base
{

QByteArray AircraftHandler::sendCurrentDataBase()
{
    SimconnectIds id = SimconnectIds::FLAPS_ANGLE;
    id = SimconnectIds::FLAPS_ANGLE;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_flapsAngle), sizeof(d_flapsAngle));

    id = SimconnectIds::SPOILERS_PCT;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_spoilersPct), sizeof(d_spoilersPct));

    id = SimconnectIds::ELEV_TRIM_PCT;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.elevTrim), sizeof(d_previous.elevTrim));

    id = SimconnectIds::AIL_TRIM_PCT;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.ailTrim), sizeof(d_previous.ailTrim));

    id = SimconnectIds::RUDD_TRIM_PCT;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.ruddTrim), sizeof(d_previous.ruddTrim));


    double transformedValue = 0;
    if (d_singleTank)
    {
        transformedValue = d_fuelQtyByWeight ? d_previous.fuelTotalQty *= d_previous.fuelDensity : d_previous.fuelTotalQty;
        id = SimconnectIds::FUEL_TOTAL_QTY;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&transformedValue), sizeof(transformedValue));
    }
    else
    {
        transformedValue = d_fuelQtyByWeight ? d_previous.fuelLeftQty *= d_previous.fuelDensity : d_previous.fuelLeftQty;
        id = SimconnectIds::FUEL_LEFT_QTY;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&transformedValue), sizeof(transformedValue));

        transformedValue = d_fuelQtyByWeight ? d_previous.fuelRightQty *= d_previous.fuelDensity : d_previous.fuelRightQty;
        id = SimconnectIds::FUEL_RIGHT_QTY;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&transformedValue), sizeof(transformedValue));
    }

    id = SimconnectIds::APU_RPM_PCT;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.apuN1), sizeof(d_previous.apuN1));

    return dataToSend;
}

}  // namespace aircraft::base
