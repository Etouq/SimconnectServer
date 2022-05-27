#include "JetHandler.hpp"
#include "windows.h"
#include "common/dataIdentifiers.hpp"
#include "../../../AircraftConfig.hpp"
#include "../../../enums.hpp"

#include <string>

#include "C:/MSFS SDK/SimConnect SDK/include/SimConnect.h"

namespace aircraft::jet
{

void JetHandler::setupData(HANDLE simConnectHandle, const AircraftConfig &config)
{
    copyConfig(config);

    d_n1Eps = config.n1Epsilon;
    d_n2Eps = config.n2Epsilon;
    d_ittEps = config.ittEpsilon;

    for (size_t engineIdx = 1; engineIdx <= d_numEngines; ++engineIdx)
    {
        std::string id = std::to_string(engineIdx);
        SimConnect_AddToDataDefinition(simConnectHandle,
                                       DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                       ("TURB ENG N1:" + id).c_str(),
                                       "percent",
                                       SIMCONNECT_DATATYPE_FLOAT64,
                                       d_n1Eps);

        SimConnect_AddToDataDefinition(simConnectHandle,
                                       DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                       ("TURB ENG N2:" + id).c_str(),
                                       "percent",
                                       SIMCONNECT_DATATYPE_FLOAT64,
                                       d_n2Eps);

        std::string datumName;
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


        setupEngineCommon(simConnectHandle, config, engineIdx);
    }


    setupDataBase(simConnectHandle);
}

}  // namespace aircraft::jet
