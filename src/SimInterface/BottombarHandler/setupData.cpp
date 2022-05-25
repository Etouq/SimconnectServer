#include "../enums.hpp"
#include "BottombarHandler.hpp"
#include "windows.h"
#include "C:/MSFS SDK/SimConnect SDK/include/SimConnect.h"


namespace bottombar
{

void BottombarHandler::setupData(HANDLE simConnectHandle)
{
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::BOTTOMBAR_DEFINITION,
                                   "ZULU TIME",
                                   "Seconds",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::BOTTOMBAR_DEFINITION,
                                   "LOCAL TIME",
                                   "Seconds",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::BOTTOMBAR_DEFINITION,
                                   "GPS GROUND SPEED",
                                   "knots",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::BOTTOMBAR_DEFINITION,
                                   "TOTAL AIR TEMPERATURE",
                                   "Celsius",
                                   SIMCONNECT_DATATYPE_FLOAT32,
                                   0.25);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::BOTTOMBAR_DEFINITION,
                                   "AMBIENT TEMPERATURE",
                                   "Celsius",
                                   SIMCONNECT_DATATYPE_FLOAT32,
                                   0.25);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::BOTTOMBAR_DEFINITION,
                                   "STANDARD ATM TEMPERATURE",
                                   "Celsius",
                                   SIMCONNECT_DATATYPE_FLOAT32,
                                   0.25);
}

}  // namespace bottombar
