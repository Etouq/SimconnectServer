#include "AircraftHandler.hpp"
#include "windows.h"
#include "../../../enums.hpp"

#include <string>

#include "C:/MSFS SDK/SimConnect SDK/include/SimConnect.h"

namespace aircraft::base
{

void AircraftHandler::setupDataBase(HANDLE simConnectHandle)
{

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                   "TRAILING EDGE FLAPS LEFT ANGLE",
                                   "degrees",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_checkFlaps ? 0.1 : 10000);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                   "TRAILING EDGE FLAPS RIGHT ANGLE",
                                   "degrees",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_checkFlaps ? 0.1 : 10000);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                   "SPOILERS LEFT POSITION",
                                   "percent over 100",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_checkFlaps && d_checkSpoilers ? 0.001 : 10000);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                   "SPOILERS RIGHT POSITION",
                                   "percent over 100",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_checkFlaps && d_checkSpoilers ? 0.001 : 10000);


    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                   "ELEVATOR TRIM PCT",
                                   "percent over 100",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_checkElevTrim ? 0.001 : 10000);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                   "RUDDER TRIM PCT",
                                   "percent over 100",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_checkRuddTrim ? 0.001 : 10000);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                   "AILERON TRIM PCT",
                                   "percent over 100",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_checkAilTrim ? 0.001 : 10000);


    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                   "FUEL LEFT QUANTITY",
                                   d_fuelQtyByWeight ? "gallons" : "liter",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_singleTank ? 1000000 : d_fuelQtyEps);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                   "FUEL RIGHT QUANTITY",
                                   d_fuelQtyByWeight ? "gallons" : "liter",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_singleTank ? 1000000 : d_fuelQtyEps);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                   "FUEL TOTAL QUANTITY",
                                   d_fuelQtyByWeight ? "gallons" : "liter",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_singleTank ? d_fuelQtyEps : 1000000);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                   "APU PCT RPM",
                                   "percent",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_checkApu ? 0.5 : 1000000);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::ENGINE_DEFINITION,
                                   "FUEL WEIGHT PER GALLON",
                                   "kilograms",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   100);
}

}  // namespace aircraft::base
