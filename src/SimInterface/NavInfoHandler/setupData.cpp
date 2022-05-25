#include "../enums.hpp"
#include "NavInfoHandler.hpp"
#include "windows.h"
#include "C:/MSFS SDK/SimConnect SDK/include/SimConnect.h"

namespace navinfo
{

void NavInfoHandler::setupData(HANDLE simConnectHandle)
{
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::NAV_INFO_DEFINITION,
                                   "GPS IS ACTIVE FLIGHT PLAN",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::NAV_INFO_DEFINITION,
                                   "GPS IS DIRECTTO FLIGHTPLAN",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::NAV_INFO_DEFINITION,
                                   "GPS WP ETE",
                                   "seconds",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::NAV_INFO_DEFINITION,
                                   "GPS ETE",
                                   "seconds",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
}

}  // namespace navinfo
