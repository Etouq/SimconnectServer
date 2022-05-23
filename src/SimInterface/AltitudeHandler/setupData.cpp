#include "../enums.hpp"
#include "AltitudeHandler.hpp"
#include "windows.h"
#include "C:/MSFS SDK/SimConnect SDK/include/SimConnect.h"

void AltitudeHandler::setupData(HANDLE simConnectHandle)
{

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ALTIMETER_DEFINITION,
                                   "INDICATED ALTITUDE",
                                   "feet",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.09);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ALTIMETER_DEFINITION,
                                   "RADIO HEIGHT",
                                   "feet",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.09);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ALTIMETER_DEFINITION,
                                   "KOHLSMAN SETTING HG:1",
                                   "inches of mercury",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.009);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ALTIMETER_DEFINITION,
                                   "VERTICAL SPEED",
                                   "feet per minute",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.09);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ALTIMETER_DEFINITION,
                                   "NAV GSI:1",
                                   "number",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.1);  // look into replacing with nav glide slope error
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ALTIMETER_DEFINITION,
                                   "NAV GSI:2",
                                   "number",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.1);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ALTIMETER_DEFINITION,
                                   "GPS VERTICAL ERROR",
                                   "meters",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.1);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ALTIMETER_DEFINITION,
                                   "AUTOPILOT ALTITUDE LOCK VAR",
                                   "feet",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ALTIMETER_DEFINITION,
                                   "AUTOPILOT VERTICAL HOLD VAR",
                                   "feet per minute",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ALTIMETER_DEFINITION,
                                   "GPS DRIVES NAV1",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ALTIMETER_DEFINITION,
                                   "AUTOPILOT NAV SELECTED",
                                   "Number",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ALTIMETER_DEFINITION,
                                   "GPS APPROACH APPROACH TYPE",
                                   "Enum",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ALTIMETER_DEFINITION,
                                   "NAV HAS GLIDE SLOPE:1",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ALTIMETER_DEFINITION,
                                   "NAV HAS GLIDE SLOPE:2",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ALTIMETER_DEFINITION,
                                   "GPS IS APPROACH ACTIVE",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
}
