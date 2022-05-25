#include "../enums.hpp"
#include "HsiHandler.hpp"
#include "windows.h"
#include "C:/MSFS SDK/SimConnect SDK/include/SimConnect.h"

namespace hsi
{

void HsiHandler::setupData(HANDLE simConnectHandle)
{
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "PLANE HEADING DEGREES MAGNETIC",
                                   "degree",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.0009);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "AUTOPILOT HEADING LOCK DIR",
                                   "degree",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.0009);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "TURN INDICATOR RATE",
                                   "degree per second",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.0009);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "GPS GROUND MAGNETIC TRACK",
                                   "degrees",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.0009);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "GPS WP DESIRED TRACK",
                                   "degree",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.0009);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "GPS POSITION LAT",
                                   "degrees",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.0000001);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "GPS POSITION LON",
                                   "degrees",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.0000001);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "GPS WP CROSS TRK",
                                   "nautical mile",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.009);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "PLANE HEADING DEGREES TRUE",
                                   "degree",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.0009);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "NAV LOCALIZER:1",
                                   "degree",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.0009);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "NAV CDI:1",
                                   "number",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.3);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "NAV OBS:1",
                                   "degree",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.0009);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "TACAN OBS:1",
                                   "degree",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.0009);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "TACAN STATION CDI:1",
                                   "number",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.3);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "NAV LOCALIZER:2",
                                   "degree",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.0009);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "NAV CDI:2",
                                   "number",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.3);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "NAV OBS:2",
                                   "degree",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.0009);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "TACAN OBS:2",
                                   "degree",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.0009);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "TACAN STATION CDI:2",
                                   "number",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.3);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "AUTOPILOT NAV SELECTED",
                                   "Number",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "GPS APPROACH APPROACH TYPE",
                                   "Enum",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "GPS DRIVES NAV1",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "AUTOPILOT APPROACH HOLD",
                                   "Boolean",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "TACAN DRIVES NAV1",
                                   "Boolean",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "NAV HAS TACAN:1",
                                   "Boolean",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "NAV HAS TACAN:2",
                                   "Boolean",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "NAV HAS NAV:1",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "NAV HAS LOCALIZER:1",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "NAV TOFROM:1",
                                   "Enum",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "TACAN STATION TOFROM:1",
                                   "Enum",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "NAV HAS NAV:2",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "NAV HAS LOCALIZER:2",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "NAV TOFROM:2",
                                   "Enum",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::HSI_DEFINITION,
                                   "TACAN STATION TOFROM:2",
                                   "Enum",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
}

}  // namespace hsi
