#include "../../enums.hpp"
#include "AttitudeHandler.hpp"
#include "windows.h"
#include "C:/MSFS SDK/SimConnect SDK/include/SimConnect.h"

namespace attitude
{

void AttitudeHandler::setupData(HANDLE simConnectHandle)
{

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ATTITUDE_DEFINITION,
                                   "ANGLE OF ATTACK INDICATOR",
                                   "Degrees",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.25);  //{ "INCIDENCE ALPHA", "Degrees", SIMCONNECT_DATATYPE_FLOAT64, 0.25 },

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ATTITUDE_DEFINITION,
                                   "ATTITUDE INDICATOR BANK DEGREES",
                                   "Degrees",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.0001);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ATTITUDE_DEFINITION,
                                   "ATTITUDE INDICATOR PITCH DEGREES",
                                   "Degrees",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.0001);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ATTITUDE_DEFINITION,
                                   "TURN COORDINATOR BALL",
                                   "position",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.0001);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ATTITUDE_DEFINITION,
                                   "AUTOPILOT FLIGHT DIRECTOR BANK",
                                   "Degrees",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.09);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ATTITUDE_DEFINITION,
                                   "AUTOPILOT FLIGHT DIRECTOR PITCH",
                                   "Degrees",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.09);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ATTITUDE_DEFINITION,
                                   "AUTOPILOT FLIGHT DIRECTOR ACTIVE",
                                   "Bool",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
}

}  // namespace attitude
