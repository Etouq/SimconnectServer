#include "EngineHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace handler::engine
{

std::string EngineHandler::sendCurrentData()
{
    std::string dataToSend;

    double gaugeValue = d_gauge1IsPowerPct ? d_previous.firstGauge : d_previous.firstGauge / d_maxPower;
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::ENGINE_FIRST_GAUGE), static_cast<char>(d_engineIdx) });
    dataToSend.append(reinterpret_cast<const char*>(&gaugeValue), sizeof(gaugeValue));

    gaugeValue = d_gauge2IsPowerPct ? d_previous.secondGauge : d_previous.secondGauge / d_maxPower;
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::ENGINE_SECOND_GAUGE), static_cast<char>(d_engineIdx) });
    dataToSend.append(reinterpret_cast<const char*>(&gaugeValue), sizeof(gaugeValue));

    gaugeValue = d_gauge3IsPowerPct ? d_previous.thirdGauge : d_previous.thirdGauge / d_maxPower;
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::ENGINE_THIRD_GAUGE), static_cast<char>(d_engineIdx) });
    dataToSend.append(reinterpret_cast<const char*>(&gaugeValue), sizeof(gaugeValue));

    gaugeValue = d_gauge4IsPowerPct ? d_previous.fourthGauge : d_previous.fourthGauge / d_maxPower;
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::ENGINE_FOURTH_GAUGE), static_cast<char>(d_engineIdx) });
    dataToSend.append(reinterpret_cast<const char*>(&gaugeValue), sizeof(gaugeValue));


    gaugeValue = d_previous.fuelFlow * (d_fuelFlowByWeight ? 3600.0 : 3.785411784);
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::ENGINE_FUEL_FLOW), static_cast<char>(d_engineIdx) });
    dataToSend.append(reinterpret_cast<const char*>(&gaugeValue), sizeof(gaugeValue));


    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::ENGINE_OIL_TEMP), static_cast<char>(d_engineIdx) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.oilTemp), sizeof(d_previous.oilTemp));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::ENGINE_SECONDARY_TEMP), static_cast<char>(d_engineIdx) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.secondaryEngineTemp), sizeof(d_previous.secondaryEngineTemp));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::ENGINE_OIL_PRESS), static_cast<char>(d_engineIdx) });
    dataToSend.append(reinterpret_cast<const char*>(&d_previous.oilPress), sizeof(d_previous.oilPress));

    return dataToSend;
}

}  // namespace handler::engine
