#include "../../enums.hpp"
#include "RadioHandler.hpp"
#include "windows.h"
#include "C:/MSFS SDK/SimConnect SDK/include/SimConnect.h"

namespace radio
{

void RadioHandler::setupData(HANDLE simConnectHandle)
{
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::RADIO_DEFINITION,
                                   "COM ACTIVE FREQUENCY:1",
                                   "MHz",
                                   SIMCONNECT_DATATYPE_FLOAT32,
                                   0.0009);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::RADIO_DEFINITION,
                                   "COM ACTIVE FREQUENCY:2",
                                   "MHz",
                                   SIMCONNECT_DATATYPE_FLOAT32,
                                   0.0009);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::RADIO_DEFINITION,
                                   "COM ACTIVE FREQUENCY:3",
                                   "MHz",
                                   SIMCONNECT_DATATYPE_FLOAT32,
                                   0.0009);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::RADIO_DEFINITION,
                                   "NAV ACTIVE FREQUENCY:1",
                                   "MHz",
                                   SIMCONNECT_DATATYPE_FLOAT32,
                                   0.009);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::RADIO_DEFINITION,
                                   "NAV ACTIVE FREQUENCY:2",
                                   "MHz",
                                   SIMCONNECT_DATATYPE_FLOAT32,
                                   0.009);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::RADIO_DEFINITION,
                                   "COM STANDBY FREQUENCY:1",
                                   "MHz",
                                   SIMCONNECT_DATATYPE_FLOAT32,
                                   0.0009);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::RADIO_DEFINITION,
                                   "COM STANDBY FREQUENCY:2",
                                   "MHz",
                                   SIMCONNECT_DATATYPE_FLOAT32,
                                   0.0009);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::RADIO_DEFINITION,
                                   "COM STANDBY FREQUENCY:3",
                                   "MHz",
                                   SIMCONNECT_DATATYPE_FLOAT32,
                                   0.0009);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::RADIO_DEFINITION,
                                   "NAV STANDBY FREQUENCY:1",
                                   "MHz",
                                   SIMCONNECT_DATATYPE_FLOAT32,
                                   0.009);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::RADIO_DEFINITION,
                                   "NAV STANDBY FREQUENCY:2",
                                   "MHz",
                                   SIMCONNECT_DATATYPE_FLOAT32,
                                   0.009);

    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::RADIO_DEFINITION,
                                   "TRANSPONDER CODE:1",
                                   "number",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
    SimConnect_AddToDataDefinition(simConnectHandle,
                                   DATA_DEFINITION_IDS::RADIO_DEFINITION,
                                   "TRANSPONDER STATE:1",
                                   "number",
                                   SIMCONNECT_DATATYPE_INT32,
                                   0.0);
}

}  // namespace radio
