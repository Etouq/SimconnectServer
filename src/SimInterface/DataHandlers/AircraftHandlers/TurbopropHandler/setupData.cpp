#include "TurbopropHandler.hpp"
#include "windows.h"
#include "common/dataIdentifiers.hpp"
#include "../../../AircraftConfig.hpp"
#include "../../../enums.hpp"

#include <string>

#include "C:/MSFS SDK/SimConnect SDK/include/SimConnect.h"

namespace aircraft::turboprop
{

void TurbopropHandler::setupData(HANDLE simConnectHandle, const AircraftConfig &config)
{
    copyConfig(config);

    d_n1Eps = config.n1Epsilon;
    d_trqEps = config.trqEpsilon;
    d_ittEps = config.ittEpsilon;
    d_rpmEps = config.rpmEpsilon;

    for (size_t engineIdx = 1; engineIdx <= d_numEngines; ++engineIdx)
    {
        std::string id = std::to_string(engineIdx);
        SimConnect_AddToDataDefinition(simConnectHandle,
                                       DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                       ("TURB ENG N1:" + id).c_str(),
                                       "percent",
                                       SIMCONNECT_DATATYPE_FLOAT64,
                                       d_n1Eps);

        std::string datumName = config.trqAsPct ? "TURB ENG MAX TORQUE PERCENT:" : "TURB ENG FREE TURBINE TORQUE:";
        SimConnect_AddToDataDefinition(simConnectHandle,
                                       DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                       (datumName + id).c_str(),
                                       config.trqAsPct ? "percent" : "newton meter",
                                       SIMCONNECT_DATATYPE_FLOAT64,
                                       d_trqEps);


        switch (config.ittGaugeType)
        {
            case TemperatureGaugeType::EGT:
                datumName = "GENERAL ENG EXHAUST GAS TEMPERATURE:";
                break;
            case TemperatureGaugeType::CHT:
            case TemperatureGaugeType::ITT:
                datumName = "TURB ENG ITT:";
                break;
        }

        SimConnect_AddToDataDefinition(simConnectHandle,
                                       DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                       (datumName + id).c_str(),
                                       "celsius",
                                       SIMCONNECT_DATATYPE_FLOAT64,
                                       d_ittEps);

        if (config.usePropRpm)
            datumName = config.rpmAsPct ? "PROP MAX RPM PERCENT:" : "PROP RPM:";
        else
            datumName = config.rpmAsPct ? "GENERAL ENG PCT MAX RPM:" : "GENERAL ENG RPM:";

        SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                   (datumName + id).c_str(),
                                   config.rpmAsPct ? "percent" : "rpm",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_rpmEps);


        setupEngineCommon(simConnectHandle, config, engineIdx);
    }


    setupDataBase(simConnectHandle);
}

}  // namespace aircraft::turboprop
