#include "AircraftHandler.hpp"
#include "windows.h"
#include "SimInterface/enums.hpp"
#include "C:/MSFS SDK/SimConnect SDK/include/SimConnect.h"

namespace handler::aircraft
{

void AircraftHandler::setupData(HANDLE simConnectHandle, const AircraftConfig &config)
{
    d_fuelQtyEps = config.fuelQtyEpsilon;

    d_singleTank = config.singleTank;
    d_fuelQtyByWeight = config.fuelQtyByWeight;

    d_checkFlaps = config.hasFlaps;
    d_checkSpoilers = config.hasSpoilers;

    d_checkElevTrim = config.hasElevatorTrim;
    d_checkRuddTrim = config.hasRudderTrim;
    d_checkAilTrim = config.hasAileronTrim;

    d_checkApu = config.hasApu;


    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AIRCRAFT_GENERAL_DEFINITION,
                                   d_singleTank ? "FUEL TOTAL QUANTITY" : "FUEL LEFT QUANTITY",
                                   d_fuelQtyByWeight ? "gallons" : "liter",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   config.fuelQtyEpsilon);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AIRCRAFT_GENERAL_DEFINITION,
                                   "FUEL RIGHT QUANTITY",
                                   d_fuelQtyByWeight ? "gallons" : "liter",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_singleTank ? 10000.0 : config.fuelQtyEpsilon);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AIRCRAFT_GENERAL_DEFINITION,
                                   "TRAILING EDGE FLAPS LEFT ANGLE",
                                   "degrees",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_checkFlaps ? 0.1 : 10000);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AIRCRAFT_GENERAL_DEFINITION,
                                   "TRAILING EDGE FLAPS RIGHT ANGLE",
                                   "degrees",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_checkFlaps ? 0.1 : 10000);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AIRCRAFT_GENERAL_DEFINITION,
                                   "SPOILERS LEFT POSITION",
                                   "percent over 100",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_checkFlaps && d_checkSpoilers ? 0.001 : 10000);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AIRCRAFT_GENERAL_DEFINITION,
                                   "SPOILERS RIGHT POSITION",
                                   "percent over 100",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_checkFlaps && d_checkSpoilers ? 0.001 : 10000);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AIRCRAFT_GENERAL_DEFINITION,
                                   "ELEVATOR TRIM PCT",
                                   "percent over 100",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_checkElevTrim ? 0.001 : 10000);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AIRCRAFT_GENERAL_DEFINITION,
                                   "RUDDER TRIM PCT",
                                   "percent over 100",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_checkRuddTrim ? 0.001 : 10000);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AIRCRAFT_GENERAL_DEFINITION,
                                   "AILERON TRIM PCT",
                                   "percent over 100",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_checkAilTrim ? 0.001 : 10000);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AIRCRAFT_GENERAL_DEFINITION,
                                   "APU PCT RPM",
                                   "percent",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   d_checkApu ? 0.5 : 10000);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AIRCRAFT_GENERAL_DEFINITION,
                                   "FUEL WEIGHT PER GALLON",
                                   "kilograms",
                                   SIMCONNECT_DATATYPE_FLOAT64,
                                   0.5);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AIRCRAFT_GENERAL_DEFINITION,
                                   "ELEVATOR TRIM POSITION",
                                   "degrees",
                                   SIMCONNECT_DATATYPE_INT32);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AIRCRAFT_GENERAL_DEFINITION,
                                   "RUDDER TRIM",
                                   "degrees",
                                   SIMCONNECT_DATATYPE_INT32);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::AIRCRAFT_GENERAL_DEFINITION,
                                   "AILERON TRIM",
                                   "degrees",
                                   SIMCONNECT_DATATYPE_INT32);
}

}
