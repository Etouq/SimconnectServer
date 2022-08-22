#include "EngineHandler.hpp"
#include "windows.h"
#include "SimInterface/enums.hpp"
#include "C:/MSFS SDK/SimConnect SDK/include/SimConnect.h"

namespace handler::engine
{

void EngineHandler::setupData(HANDLE simConnectHandle, const AircraftConfig &config)
{

    d_gauge1IsPct = (config.gauge1Type == SwitchingGaugeType::POWER
                     || (config.type == AircraftType::PROP && config.gauge1Type == SwitchingGaugeType::TORQUE))
      && config.gauge1Unit == Units::PERCENT;
    d_gauge2IsPct = (config.gauge2Type == SwitchingGaugeType::POWER
                     || (config.type == AircraftType::PROP && config.gauge2Type == SwitchingGaugeType::TORQUE))
      && config.gauge2Unit == Units::PERCENT;
    d_gauge3IsPct = (config.gauge3Type == SwitchingGaugeType::POWER
                     || (config.type == AircraftType::PROP && config.gauge3Type == SwitchingGaugeType::TORQUE))
      && config.gauge3Unit == Units::PERCENT;
    d_gauge4IsPct = (config.gauge4Type == SwitchingGaugeType::POWER
                     || (config.type == AircraftType::PROP && config.gauge4Type == SwitchingGaugeType::TORQUE))
      && config.gauge4Unit == Units::PERCENT;

    d_firstGaugeEpsilon = config.firstGaugeEpsilon;
    d_secondGaugeEpsilon = config.secondGaugeEpsilon;
    d_thirdGaugeEpsilon = config.thirdGaugeEpsilon;
    d_fourthGaugeEpsilon = config.fourthGaugeEpsilon;

    d_fuelFlowEpsilon = config.fuelFlowEpsilon;
    d_oilTempEpsilon = config.oilTempEpsilon;
    d_secondaryTempEpsilon = config.secondaryTempEpsilon;
    d_oilPressEpsilon = config.oilPressEpsilon;


    d_gauge1Factor = !d_gauge1IsPct                    ? 1.0
      : config.gauge1Type == SwitchingGaugeType::POWER ? 1.0 / config.maxPower
                                                       : 1.0 / config.maxTorque;
    d_gauge2Factor = !d_gauge2IsPct                    ? 1.0
      : config.gauge2Type == SwitchingGaugeType::POWER ? 1.0 / config.maxPower
                                                       : 1.0 / config.maxTorque;
    d_gauge3Factor = !d_gauge3IsPct                    ? 1.0
      : config.gauge3Type == SwitchingGaugeType::POWER ? 1.0 / config.maxPower
                                                       : 1.0 / config.maxTorque;
    d_gauge4Factor = !d_gauge4IsPct                    ? 1.0
      : config.gauge4Type == SwitchingGaugeType::POWER ? 1.0 / config.maxPower
                                                       : 1.0 / config.maxTorque;

    d_fuelFlowByWeight = config.fuelFlowByWeight;

    d_hasSecondaryTempGauge = config.hasSecondaryTempGauge;

    DATA_DEFINITION_IDS dataId = d_engineIdx == 1 ? DATA_DEFINITION_IDS::ENGINE1_DEFINITION
      : d_engineIdx == 2                          ? DATA_DEFINITION_IDS::ENGINE2_DEFINITION
      : d_engineIdx == 3                          ? DATA_DEFINITION_IDS::ENGINE3_DEFINITION
                                                  : DATA_DEFINITION_IDS::ENGINE4_DEFINITION;

    SimConnect_AddToDataDefinition(
      simConnectHandle,
      dataId,
      gaugeTypeToString(config.gauge1Type, config.type, config.engineTempType, config.gauge1Unit).c_str(),
      gaugeTypeToUnit(config.gauge1Type, config.type, config.gauge1Unit).c_str(),
      SIMCONNECT_DATATYPE_FLOAT64,
      config.firstGaugeEpsilon);

    SimConnect_AddToDataDefinition(
      simConnectHandle,
      dataId,
      gaugeTypeToString(config.gauge2Type, config.type, config.engineTempType, config.gauge2Unit).c_str(),
      gaugeTypeToUnit(config.gauge2Type, config.type, config.gauge2Unit).c_str(),
      SIMCONNECT_DATATYPE_FLOAT64,
      config.secondGaugeEpsilon);

    if (config.gauge3Type == SwitchingGaugeType::NONE)
    {

        SimConnect_AddToDataDefinition(
          simConnectHandle,
          dataId,
          gaugeTypeToString(config.gauge1Type, config.type, config.engineTempType, config.gauge1Unit).c_str(),
          gaugeTypeToUnit(config.gauge1Type, config.type, config.gauge1Unit).c_str(),
          SIMCONNECT_DATATYPE_FLOAT64,
          config.thirdGaugeEpsilon);

        SimConnect_AddToDataDefinition(
          simConnectHandle,
          dataId,
          gaugeTypeToString(config.gauge1Type, config.type, config.engineTempType, config.gauge1Unit).c_str(),
          gaugeTypeToUnit(config.gauge1Type, config.type, config.gauge1Unit).c_str(),
          SIMCONNECT_DATATYPE_FLOAT64,
          config.fourthGaugeEpsilon);

        d_numGauges = 2;
    }
    else
    {
        SimConnect_AddToDataDefinition(
          simConnectHandle,
          dataId,
          gaugeTypeToString(config.gauge3Type, config.type, config.engineTempType, config.gauge3Unit).c_str(),
          gaugeTypeToUnit(config.gauge3Type, config.type, config.gauge3Unit).c_str(),
          SIMCONNECT_DATATYPE_FLOAT64,
          config.thirdGaugeEpsilon);

        if (config.gauge4Type == SwitchingGaugeType::NONE)
        {
            SimConnect_AddToDataDefinition(
              simConnectHandle,
              dataId,
              gaugeTypeToString(config.gauge1Type, config.type, config.engineTempType, config.gauge1Unit).c_str(),
              gaugeTypeToUnit(config.gauge1Type, config.type, config.gauge1Unit).c_str(),
              SIMCONNECT_DATATYPE_FLOAT64,
              config.fourthGaugeEpsilon);

            d_numGauges = 3;
        }
        else
        {
            SimConnect_AddToDataDefinition(
              simConnectHandle,
              dataId,
              gaugeTypeToString(config.gauge4Type, config.type, config.engineTempType, config.gauge4Unit).c_str(),
              gaugeTypeToUnit(config.gauge4Type, config.type, config.gauge4Unit).c_str(),
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
