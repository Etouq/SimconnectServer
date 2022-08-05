#include "enums.hpp"
#include "SimInterface.hpp"

void SimInterface::setupEvents()
{
    SimConnect_MapClientEventToSimEvent(d_simConnectHandle, SIM_COMMAND_IDS::SET_COM1_STBY, "COM_STBY_RADIO_SET_HZ");
    SimConnect_MapClientEventToSimEvent(d_simConnectHandle, SIM_COMMAND_IDS::SET_COM2_STBY, "COM2_STBY_RADIO_SET_HZ");
    SimConnect_MapClientEventToSimEvent(d_simConnectHandle, SIM_COMMAND_IDS::SET_COM3_STBY, "COM3_STBY_RADIO_SET_HZ");

    SimConnect_MapClientEventToSimEvent(d_simConnectHandle, SIM_COMMAND_IDS::SET_NAV1_STBY, "NAV1_STBY_SET_HZ");
    SimConnect_MapClientEventToSimEvent(d_simConnectHandle, SIM_COMMAND_IDS::SET_NAV2_STBY, "NAV2_STBY_SET_HZ");

    SimConnect_MapClientEventToSimEvent(d_simConnectHandle, SIM_COMMAND_IDS::SWAP_COM1, "COM_STBY_RADIO_SWAP");
    SimConnect_MapClientEventToSimEvent(d_simConnectHandle, SIM_COMMAND_IDS::SWAP_COM2, "COM2_RADIO_SWAP");
    SimConnect_MapClientEventToSimEvent(d_simConnectHandle, SIM_COMMAND_IDS::SWAP_COM3, "COM3_RADIO_SWAP");

    SimConnect_MapClientEventToSimEvent(d_simConnectHandle, SIM_COMMAND_IDS::SWAP_NAV1, "NAV1_RADIO_SWAP");
    SimConnect_MapClientEventToSimEvent(d_simConnectHandle, SIM_COMMAND_IDS::SWAP_NAV2, "NAV2_RADIO_SWAP");

    SimConnect_MapClientEventToSimEvent(d_simConnectHandle, SIM_COMMAND_IDS::SET_XPNDR_CODE, "XPNDR_SET");

    SimConnect_MapClientEventToSimEvent(d_simConnectHandle, SIM_COMMAND_IDS::TOGGLE_GPS_DRIVES_NAV1, "TOGGLE_GPS_DRIVES_NAV1");
    SimConnect_MapClientEventToSimEvent(d_simConnectHandle, SIM_COMMAND_IDS::SET_AP_NAV_SELECTED, "AP_NAV_SELECT_SET");
}
