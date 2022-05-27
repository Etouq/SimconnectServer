#include "../../enums.hpp"
#include "ApInfoHandler.hpp"
#include "windows.h"
#include "C:/MSFS SDK/SimConnect SDK/include/SimConnect.h"

namespace apinfo
{

void ApInfoHandler::setupData(HANDLE simConnectHandle)
{
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "AUTOPILOT MACH HOLD VAR",
                                   "mach",
                                   SIMCONNECT_DATATYPE_FLOAT32,
                                   0.0005);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "AUTOPILOT MASTER",
                                   "Boolean",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "AUTOPILOT YAW DAMPER",
                                   "Boolean",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "AUTOPILOT PITCH HOLD",
                                   "Boolean",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "AUTOPILOT FLIGHT LEVEL CHANGE",
                                   "Boolean",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "AUTOPILOT MANAGED SPEED IN MACH",
                                   "Boolean",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "AUTOPILOT MACH HOLD",
                                   "Boolean",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "AUTOPILOT ALTITUDE LOCK",
                                   "Boolean",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "AUTOPILOT VERTICAL HOLD",
                                   "Boolean",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "AUTOPILOT GLIDESLOPE ACTIVE",
                                   "Boolean",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "AUTOPILOT ALTITUDE ARM",
                                   "Boolean",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "AUTOPILOT GLIDESLOPE ARM",
                                   "Boolean",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "AUTOPILOT WING LEVELER",
                                   "Boolean",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "AUTOPILOT BANK HOLD",
                                   "Boolean",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "AUTOPILOT HEADING LOCK",
                                   "Boolean",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "AUTOPILOT NAV1 LOCK",
                                   "Boolean",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "AUTOPILOT BACKCOURSE HOLD",
                                   "Boolean",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "AUTOPILOT APPROACH HOLD",
                                   "Boolean",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "AUTOPILOT AIRSPEED HOLD VAR",
                                   "knots",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "AUTOPILOT ALTITUDE LOCK VAR:2",
                                   "feet",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "AUTOPILOT VERTICAL HOLD VAR",
                                   "feet per minute",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "GPS DRIVES NAV1",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "AUTOPILOT NAV SELECTED",
                                   "Number",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "NAV HAS LOCALIZER:1",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AP_INFO_DEFINITION,
                                   "NAV HAS LOCALIZER:2",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
}

}  // namespace apinfo
