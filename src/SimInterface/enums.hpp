#ifndef __ENUMS_HPP__
#define __ENUMS_HPP__

enum DATA_DEFINITION_IDS
{
    AIRSPEED_DEFINITION,
    ALTIMETER_DEFINITION,
    ATTITUDE_DEFINITION,
    BOTTOMBAR_DEFINITION,
    HSI_DEFINITION,
    HSI_BRG_DEFINITION,
    RADIO_DEFINITION,
    NAV_INFO_DEFINITION,
    WIND_DEFINITION,
    AP_INFO_DEFINITION,
    AIRCRAFT_GENERAL_DEFINITION,
    ENGINE1_DEFINITION,
    ENGINE2_DEFINITION,
    ENGINE3_DEFINITION,
    ENGINE4_DEFINITION,
    MISC_DEFINITION,
    SET_XPNDR_STATE_DEF
};

enum DATA_REQUEST_IDS
{
    AIRSPEED_REQUEST,
    ALTIMETER_REQUEST,
    ATTITUDE_REQUEST,
    BOTTOMBAR_REQUEST,
    HSI_REQUEST,
    HSI_BRG_REQUEST,
    RADIO_REQUEST,
    NAV_INFO_REQUEST,
    WIND_REQUEST,
    AP_INFO_REQUEST,
    AIRCRAFT_GENERAL_REQUEST,
    ENGINE1_REQUEST,
    ENGINE2_REQUEST,
    ENGINE3_REQUEST,
    ENGINE4_REQUEST,
    MISC_REQUEST
};

enum EVENT_IDS
{
    EVENT_6HZ_ID,
    EVENT_1SEC_ID,
    SIM_START_EVENT_ID,
    SIM_STOP_EVENT_ID
};

enum SIM_COMMAND_IDS
{
    SET_COM1_STBY = 4, // to prevent conflict with EVENT_IDS
    SET_COM2_STBY,
    SET_COM3_STBY,
    SET_NAV1_STBY,
    SET_NAV2_STBY,
    SWAP_COM1,
    SWAP_COM2,
    SWAP_COM3,
    SWAP_NAV1,
    SWAP_NAV2,
    SET_XPNDR_CODE,
    TOGGLE_GPS_DRIVES_NAV1,
    SET_AP_NAV_SELECTED
};

#endif // __ENUMS_HPP__
