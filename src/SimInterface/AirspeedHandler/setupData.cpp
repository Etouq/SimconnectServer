#include "../enums.hpp"
#include "AirspeedHandler.hpp"
#include "windows.h"
#include "C:/MSFS SDK/SimConnect SDK/include/SimConnect.h"


namespace airspeed
{

void AirspeedHandler::setupData(HANDLE simConnectHandle)
{
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AIRSPEED_DEFINITION,
                                   "AIRSPEED INDICATED",
                                   "knots",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.01);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AIRSPEED_DEFINITION,
                                   "AIRSPEED BARBER POLE",
                                   "knots",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.09);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AIRSPEED_DEFINITION,
                                   "AIRSPEED TRUE",
                                   "knots",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AIRSPEED_DEFINITION,
                                   "AUTOPILOT AIRSPEED HOLD VAR",
                                   "knots",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
}

}  // namespace airspeed
