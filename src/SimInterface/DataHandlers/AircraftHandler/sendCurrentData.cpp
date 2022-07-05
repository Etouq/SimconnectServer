#include "AircraftHandler.hpp"
#include "common/appendData.hpp"
#include "common/dataIdentifiers.hpp"

namespace handler::aircraft
{

QByteArray AircraftHandler::sendCurrentData()
{
    QByteArray dataToSend;

    if (d_fuelQtyByWeight)
    {
        util::appendData(MfdIdentifier::FUEL_LEFT_QTY, d_previous.fuelLeftQty * d_previous.fuelDensity, dataToSend);

        if (!d_singleTank)
            util::appendData(MfdIdentifier::FUEL_RIGHT_QTY, d_previous.fuelRightQty * d_previous.fuelDensity, dataToSend);
    }
    else
    {
        util::appendData(MfdIdentifier::FUEL_LEFT_QTY, d_previous.fuelLeftQty, dataToSend);

        if (!d_singleTank)
            util::appendData(MfdIdentifier::FUEL_RIGHT_QTY, d_previous.fuelRightQty, dataToSend);
    }

    util::appendData(MfdIdentifier::FLAPS_ANGLE, d_flapsAngle, dataToSend);
    util::appendData(MfdIdentifier::SPOILERS_PCT, d_spoilersPct, dataToSend);

    util::appendData(MfdIdentifier::ELEV_TRIM_POSITION, d_previous.elevTrimPct, dataToSend);
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.elevTrimAngle), sizeof(d_previous.elevTrimAngle));

    util::appendData(MfdIdentifier::AIL_TRIM_POSITION, d_previous.ailTrimPct, dataToSend);
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.ailTrimAngle), sizeof(d_previous.ailTrimAngle));

    util::appendData(MfdIdentifier::RUDD_TRIM_POSITION, d_previous.ruddTrimPct, dataToSend);
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.ruddTrimAngle), sizeof(d_previous.ruddTrimAngle));

    util::appendData(MfdIdentifier::APU_N1, d_previous.apuN1, dataToSend);

    return dataToSend;
}

}
