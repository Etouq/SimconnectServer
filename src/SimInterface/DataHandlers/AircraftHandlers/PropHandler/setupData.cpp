#include "../../../enums.hpp"
#include "../../../AircraftConfig.hpp"
#include "PropHandler.hpp"
#include "common/dataIdentifiers.hpp"
#include "windows.h"
#include "C:/MSFS SDK/SimConnect SDK/include/SimConnect.h"
#include <string>


namespace aircraft::prop
{

void PropHandler::setupData(HANDLE simConnectHandle, const AircraftConfig &config)
{
    copyConfig(config);

    d_checkRpm = config.hasRpm;

    d_powerAsPct = config.powerAsPct;
    d_checkPower = config.hasPower;
    d_maxPower = config.maxPower;

    d_checkManPress = config.hasManPress;
    d_checkCht = config.hasCht;

    d_rpmEps = d_checkRpm ? config.rpmEpsilon : 10000;
    d_powerEps = d_checkPower ? config.powerEpsilon : 10000;
    d_manPressEps = d_checkManPress ? config.manPressEpsilon : 10000;
    d_chtEps = d_checkCht ? config.chtEpsilon : 10000;


    for (size_t engineIdx = 1; engineIdx <= d_numEngines; ++engineIdx)
    {
        std::string id = std::to_string(engineIdx);
        std::string datumName = config.usePropRpm ? "PROP RPM:" : "GENERAL ENG RPM:";
        SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                   (datumName + id).c_str(),
                                   "rpm",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_rpmEps);

        SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                   ("RECIP ENG BRAKE POWER:" + id).c_str(),
                                   "ft lb per second",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_powerEps);

        SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                   ("RECIP ENG MANIFOLD PRESSURE:" + id).c_str(),
                                   "kpa",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_manPressEps);

        switch (config.chtGaugeType)
        {
            case TemperatureGaugeType::ITT: // not allowed so revert to cht
            case TemperatureGaugeType::CHT:
                datumName = "RECIP ENG CYLINDER HEAD TEMPERATURE:";
                break;
            case TemperatureGaugeType::EGT:
                datumName = "GENERAL ENG EXHAUST GAS TEMPERATURE:";
                break;
        }

        SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                   (datumName + id).c_str(),
                                   "celsius",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_chtEps);

        setupEngineCommon(simConnectHandle, config, engineIdx);
    }


    setupDataBase(simConnectHandle);
}

}  // namespace aircraft::prop
