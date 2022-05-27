#include "../../enums.hpp"
#include "HsiBrgHandler.hpp"
#include "windows.h"
#include "C:/MSFS SDK/SimConnect SDK/include/SimConnect.h"

namespace hsibrg
{

void HsiBrgHandler::setupData(HANDLE simConnectHandle)
{
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_BRG_DEFINITION,
                                   "NAV DME:1",
                                   "nautical miles",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.09);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_BRG_DEFINITION,
                                   "NAV RADIAL:1",
                                   "degree",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.0009);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_BRG_DEFINITION,
                                   "NAV DME:2",
                                   "nautical miles",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.09);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_BRG_DEFINITION,
                                   "NAV RADIAL:2",
                                   "degree",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.0009);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_BRG_DEFINITION,
                                   "GPS WP DISTANCE",
                                   "nautical miles",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.09);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_BRG_DEFINITION,
                                   "GPS WP BEARING",
                                   "degree",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.0009);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_BRG_DEFINITION,
                                   "ADF ACTIVE FREQUENCY:1",
                                   "KHz",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.09);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_BRG_DEFINITION,
                                   "ADF RADIAL:1",
                                   "degree",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.0009);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_BRG_DEFINITION,
                                   "PLANE HEADING DEGREES MAGNETIC",
                                   "degree",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.0009);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_BRG_DEFINITION,
                                   "NAV HAS NAV:1",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_BRG_DEFINITION,
                                   "NAV SIGNAL:1",
                                   "number",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_BRG_DEFINITION,
                                   "NAV HAS DME:1",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_BRG_DEFINITION,
                                   "NAV HAS NAV:2",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_BRG_DEFINITION,
                                   "NAV SIGNAL:2",
                                   "number",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_BRG_DEFINITION,
                                   "NAV HAS DME:2",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_BRG_DEFINITION,
                                   "ADF SIGNAL:1",
                                   "number",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
}

}  // namespace hsibrg
