#include "AircraftHandler.hpp"
#include "windows.h"
#include "common/dataIdentifiers.hpp"
#include "../../../enums.hpp"

#include <string>

#include "C:/MSFS SDK/SimConnect SDK/include/SimConnect.h"

namespace aircraft::base
{

void AircraftHandler::setupEngineCommon(HANDLE simConnectHandle, const AircraftConfig &config, const uint8_t idx)
{


    std::string id = std::to_string(idx);

    std::string datumName = d_fuelFlowByWeight ? "ENG FUEL FLOW PPH:" : "ENG FUEL FLOW GPH:";
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                   (datumName + id).c_str(),
                                   d_fuelFlowByWeight ? "kilograms per second" : "gallon per hour",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_fuelFlowEps);

    switch (config.egtGaugeType)
    {
        case TemperatureGaugeType::EGT:
            datumName = "GENERAL ENG EXHAUST GAS TEMPERATURE:";
            break;
        case TemperatureGaugeType::CHT:
            datumName = "RECIP ENG CYLINDER HEAD TEMPERATURE:";
            break;
        case TemperatureGaugeType::ITT:
            datumName = "TURB ENG ITT:";
            break;
    }

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                   (datumName + id).c_str(),
                                   "celsius",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_egtEps);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                   ("GENERAL ENG OIL TEMPERATURE:" + id).c_str(),
                                   "celsius",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_oilTempEps);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                   ("GENERAL ENG OIL PRESSURE:" + id).c_str(),
                                   "kpa",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_oilPressEps);
}

}  // namespace aircraft::base
