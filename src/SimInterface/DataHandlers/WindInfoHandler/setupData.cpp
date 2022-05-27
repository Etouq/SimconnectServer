#include "WindInfoHandler.hpp"
#include "windows.h"
#include "../../enums.hpp"
#include "C:/MSFS SDK/SimConnect SDK/include/SimConnect.h"


namespace windinfo
{

void WindInfoHandler::setupData(HANDLE simConnectHandle)
{
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::WIND_DEFINITION,
                                   "PLANE HEADING DEGREES MAGNETIC",
                                   "degree",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.05);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::WIND_DEFINITION,
                                   "AMBIENT WIND VELOCITY",
                                   "knots",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.05);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::WIND_DEFINITION,
                                   "AMBIENT WIND DIRECTION",
                                   "degree",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.05);
}

}  // namespace windinfo
