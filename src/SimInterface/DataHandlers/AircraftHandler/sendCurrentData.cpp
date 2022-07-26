#include "AircraftHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace handler::aircraft
{

std::string AircraftHandler::sendCurrentData()
{
    std::string dataToSend;

    if (d_fuelQtyByWeight)
    {
        double gaugeData = d_previous.fuelLeftQty * d_previous.fuelDensity;
        dataToSend.append(
          { static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::FUEL_LEFT_QTY) });
        dataToSend.append(reinterpret_cast<const char *>(&gaugeData), sizeof(gaugeData));

        if (!d_singleTank)
        {
            gaugeData = d_previous.fuelRightQty * d_previous.fuelDensity;
            dataToSend.append(
              { static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::FUEL_RIGHT_QTY) });
            dataToSend.append(reinterpret_cast<const char *>(&gaugeData), sizeof(gaugeData));
        }
    }
    else
    {
        dataToSend.append(
          { static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::FUEL_LEFT_QTY) });
        dataToSend.append(reinterpret_cast<const char *>(&d_previous.fuelLeftQty), sizeof(d_previous.fuelLeftQty));

        if (!d_singleTank)
        {
            dataToSend.append(
              { static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::FUEL_RIGHT_QTY) });
            dataToSend.append(reinterpret_cast<const char *>(&d_previous.fuelRightQty),
                              sizeof(d_previous.fuelRightQty));
        }
    }

    dataToSend.append(
      { static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::FLAPS_ANGLE) });
    dataToSend.append(reinterpret_cast<const char *>(&d_flapsAngle), sizeof(d_flapsAngle));
    dataToSend.append(
      { static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::SPOILERS_PCT) });
    dataToSend.append(reinterpret_cast<const char *>(&d_spoilersPct), sizeof(d_spoilersPct));

    dataToSend.append(
      { static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::ELEV_TRIM_POSITION) });
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.elevTrimPct), sizeof(d_previous.elevTrimPct));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.elevTrimAngle), sizeof(d_previous.elevTrimAngle));

    dataToSend.append(
      { static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::AIL_TRIM_POSITION) });
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.ailTrimPct), sizeof(d_previous.ailTrimPct));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.ailTrimAngle), sizeof(d_previous.ailTrimAngle));

    dataToSend.append(
      { static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::RUDD_TRIM_POSITION) });
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.ruddTrimPct), sizeof(d_previous.ruddTrimPct));
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.ruddTrimAngle), sizeof(d_previous.ruddTrimAngle));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::APU_N1) });
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.apuN1), sizeof(d_previous.apuN1));

    return dataToSend;
}

}  // namespace handler::aircraft
