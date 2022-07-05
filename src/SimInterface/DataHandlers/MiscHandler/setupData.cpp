#include "MiscHandler.hpp"
#include "windows.h"
#include "../../enums.hpp"
#include "C:/MSFS SDK/SimConnect SDK/include/SimConnect.h"

namespace misc
{

void MiscHandler::setupData(HANDLE simConnectHandle)
{
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::MISC_DEFINITION,
                                   "FUEL TOTAL QUANTITY",
                                   "gallons",
                                   SIMCONNECT_DATATYPE_FLOAT32);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::MISC_DEFINITION,
                                   "ENG FUEL FLOW GPH:1",
                                   "gallons per hour",
                                   SIMCONNECT_DATATYPE_FLOAT32);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::MISC_DEFINITION,
                                   "ENG FUEL FLOW GPH:2",
                                   "gallons per hour",
                                   SIMCONNECT_DATATYPE_FLOAT32);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::MISC_DEFINITION,
                                   "ENG FUEL FLOW GPH:3",
                                   "gallons per hour",
                                   SIMCONNECT_DATATYPE_FLOAT32);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::MISC_DEFINITION,
                                   "ENG FUEL FLOW GPH:4",
                                   "gallons per hour",
                                   SIMCONNECT_DATATYPE_FLOAT32);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::MISC_DEFINITION,
                                   "GPS GROUND SPEED",
                                   "knots",
                                   SIMCONNECT_DATATYPE_FLOAT32);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::MISC_DEFINITION,
                                   "GPS WP NEXT ID",
                                   "",
                                   SIMCONNECT_DATATYPE_STRING64);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::MISC_DEFINITION,
                                   "NAV IDENT:1",
                                   "",
                                   SIMCONNECT_DATATYPE_STRING64);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::MISC_DEFINITION,
                                   "NAV IDENT:2",
                                   "",
                                   SIMCONNECT_DATATYPE_STRING64);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::MISC_DEFINITION,
                                   "GPS WP PREV ID",
                                   "",
                                   SIMCONNECT_DATATYPE_STRING64);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::MISC_DEFINITION,
                                   "AUTOPILOT AVAILABLE",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::MISC_DEFINITION,
                                   "COM AVAILABLE:1",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::MISC_DEFINITION,
                                   "COM AVAILABLE:2",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::MISC_DEFINITION,
                                   "COM AVAILABLE:3",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::MISC_DEFINITION,
                                   "NAV AVAILABLE:1",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::MISC_DEFINITION,
                                   "NAV AVAILABLE:2",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::MISC_DEFINITION,
                                   "TRANSPONDER AVAILABLE",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32);
}

}  // namespace misc
