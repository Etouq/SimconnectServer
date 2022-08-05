#include "EngineHandler.hpp"
#include "windows.h"
#include "SimInterface/enums.hpp"

#include "C:/MSFS SDK/SimConnect SDK/include/SimConnect.h"


namespace handler::engine
{

void EngineHandler::setupData(HANDLE simConnectHandle, const AircraftConfig &config)
{
    d_gauge1IsPowerPct = config.gauge1Type == SwitchingGaugeType::POWER_PCT;
    d_gauge2IsPowerPct = config.gauge2Type == SwitchingGaugeType::POWER_PCT;
    d_gauge3IsPowerPct = config.gauge3Type == SwitchingGaugeType::POWER_PCT;
    d_gauge4IsPowerPct = config.gauge4Type == SwitchingGaugeType::POWER_PCT;

    d_firstGaugeEpsilon = config.firstGaugeEpsilon;
    d_secondGaugeEpsilon = config.secondGaugeEpsilon;
    d_thirdGaugeEpsilon = config.thirdGaugeEpsilon;
    d_fourthGaugeEpsilon = config.fourthGaugeEpsilon;

    d_fuelFlowEpsilon = config.fuelFlowEpsilon;
    d_oilTempEpsilon = config.oilTempEpsilon;
    d_secondaryTempEpsilon = config.secondaryTempEpsilon;
    d_oilPressEpsilon = config.oilPressEpsilon;

    d_maxPower = config.maxPower;

    d_fuelFlowByWeight = config.fuelFlowByWeight;

    d_hasSecondaryTempGauge = config.hasSecondaryTempGauge;

    DATA_DEFINITION_IDS dataId = d_engineIdx == 1 ? DATA_DEFINITION_IDS::ENGINE1_DEFINITION
      : d_engineIdx == 2                          ? DATA_DEFINITION_IDS::ENGINE2_DEFINITION
      : d_engineIdx == 3                          ? DATA_DEFINITION_IDS::ENGINE3_DEFINITION
                                                  : DATA_DEFINITION_IDS::ENGINE4_DEFINITION;

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   dataId,
                                   gaugeTypeToString(config.gauge1Type, config.type, config.engineTempType).c_str(),
                                   gaugeTypeToUnit(config.gauge1Type).c_str(),
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   config.firstGaugeEpsilon);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   dataId,
                                   gaugeTypeToString(config.gauge2Type, config.type, config.engineTempType).c_str(),
                                   gaugeTypeToUnit(config.gauge2Type).c_str(),
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   config.secondGaugeEpsilon);

    if (config.gauge3Type == SwitchingGaugeType::NONE)
    {

        SimConnect_AddToDataDefinition(simConnectHandle,
                                       dataId,
                                       gaugeTypeToString(config.gauge1Type, config.type, config.engineTempType).c_str(),
                                       gaugeTypeToUnit(config.gauge1Type).c_str(),
                                       SIMCONNECT_DATATYPE_FLOAT64,
                                       config.thirdGaugeEpsilon);

        SimConnect_AddToDataDefinition(simConnectHandle,
                                       dataId,
                                       gaugeTypeToString(config.gauge1Type, config.type, config.engineTempType).c_str(),
                                       gaugeTypeToUnit(config.gauge1Type).c_str(),
                                       SIMCONNECT_DATATYPE_FLOAT64,
                                       config.fourthGaugeEpsilon);

        d_numGauges = 2;
    }
    else
    {
        SimConnect_AddToDataDefinition(simConnectHandle,
                                       dataId,
                                       gaugeTypeToString(config.gauge3Type, config.type, config.engineTempType).c_str(),
                                       gaugeTypeToUnit(config.gauge3Type).c_str(),
                                       SIMCONNECT_DATATYPE_FLOAT64,
                                       config.thirdGaugeEpsilon);

        if (config.gauge4Type == SwitchingGaugeType::NONE)
        {
            SimConnect_AddToDataDefinition(
              simConnectHandle,
              dataId,
              gaugeTypeToString(config.gauge1Type, config.type, config.engineTempType).c_str(),
              gaugeTypeToUnit(config.gauge1Type).c_str(),
              SIMCONNECT_DATATYPE_FLOAT64,
              config.fourthGaugeEpsilon);

            d_numGauges = 3;
        }
        else
        {
            SimConnect_AddToDataDefinition(
              simConnectHandle,
              dataId,
              gaugeTypeToString(config.gauge4Type, config.type, config.engineTempType).c_str(),
              gaugeTypeToUnit(config.gauge4Type).c_str(),
              SIMCONNECT_DATATYPE_FLOAT64,
              config.fourthGaugeEpsilon);

            d_numGauges = 4;
        }
    }

    std::string datumName = d_fuelFlowByWeight ? "ENG FUEL FLOW PPH:" : "ENG FUEL FLOW GPH:";
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   dataId,
                                   (datumName + std::to_string(d_engineIdx)).c_str(),
                                   d_fuelFlowByWeight ? "kilograms per second" : "gallon per hour",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   config.fuelFlowEpsilon);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   dataId,
                                   ("GENERAL ENG OIL TEMPERATURE:" + std::to_string(d_engineIdx)).c_str(),
                                   "celsius",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   config.oilTempEpsilon);


    switch (config.secondaryTempType)
    {
        case TemperatureGaugeType::EGT:
            datumName = "GENERAL ENG EXHAUST GAS TEMPERATURE:" + std::to_string(d_engineIdx);
            break;
        case TemperatureGaugeType::ITT:
            datumName = "TURB ENG ITT:" + std::to_string(d_engineIdx);
            break;
        case TemperatureGaugeType::CHT:
        {
            if (config.type == AircraftType::PROP)
            {
                datumName = "RECIP ENG CYLINDER HEAD TEMPERATURE:" + std::to_string(d_engineIdx);
                break;
            }
            datumName = "ENG CYLINDER HEAD TEMPERATURE:" + std::to_string(d_engineIdx);
            break;
        }
        case TemperatureGaugeType::TIT:
            datumName = "RECIP ENG TURBINE INLET TEMPERATURE:" + std::to_string(d_engineIdx);
            break;
    }

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   dataId,
                                   datumName.c_str(),
                                   "celsius",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   config.secondaryTempEpsilon);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   dataId,
                                   ("GENERAL ENG OIL PRESSURE:" + std::to_string(d_engineIdx)).c_str(),
                                   "kpa",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   config.oilPressEpsilon);
}

}  // namespace handler::engine
