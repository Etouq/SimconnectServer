#include "enums.hpp"
#include "SimInterface.hpp"

void SimInterface::setupData()
{
    d_airspeedHandler.setupData(d_simConnectHandle);
    d_altitudeHandler.setupData(d_simConnectHandle);
    d_autopilotHandler.setupData(d_simConnectHandle);
    d_attitudeHandler.setupData(d_simConnectHandle);
    d_bottombarHandler.setupData(d_simConnectHandle);
    d_bearingHandler.setupData(d_simConnectHandle);
    d_hsiHandler.setupData(d_simConnectHandle);
    d_navInfoHandler.setupData(d_simConnectHandle);
    d_radioHandler.setupData(d_simConnectHandle);
    d_windHandler.setupData(d_simConnectHandle);
    d_miscHandler.setupData(d_simConnectHandle);

    d_engine1Handler.setupData(d_simConnectHandle, d_aircraftConfig);
    d_engine2Handler.setupData(d_simConnectHandle, d_aircraftConfig);
    d_engine3Handler.setupData(d_simConnectHandle, d_aircraftConfig);
    d_engine4Handler.setupData(d_simConnectHandle, d_aircraftConfig);

    d_aircraftHandler.setupData(d_simConnectHandle, d_aircraftConfig);

    SimConnect_AddToDataDefinition(d_simConnectHandle,
                                   SET_XPNDR_STATE_DEF,
                                   "TRANSPONDER STATE:1",
                                   "enum",
                                   SIMCONNECT_DATATYPE_INT32);

    SimConnect_SubscribeToSystemEvent(d_simConnectHandle, EVENT_6HZ_ID, "6Hz");
    SimConnect_SubscribeToSystemEvent(d_simConnectHandle, EVENT_1SEC_ID, "1sec");
    SimConnect_SubscribeToSystemEvent(d_simConnectHandle, SIM_START_EVENT_ID, "SimStart");
    SimConnect_SubscribeToSystemEvent(d_simConnectHandle, SIM_STOP_EVENT_ID, "SimStop");

    SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                      MISC_REQUEST,
                                      MISC_DEFINITION,
                                      SIMCONNECT_OBJECT_ID_USER,
                                      SIMCONNECT_PERIOD_SECOND);

    SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                      AIRSPEED_REQUEST,
                                      AIRSPEED_DEFINITION,
                                      SIMCONNECT_OBJECT_ID_USER,
                                      SIMCONNECT_PERIOD_SIM_FRAME,
                                      SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

    SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                      ALTIMETER_REQUEST,
                                      ALTIMETER_DEFINITION,
                                      SIMCONNECT_OBJECT_ID_USER,
                                      SIMCONNECT_PERIOD_SIM_FRAME,
                                      SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

    SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                      ATTITUDE_REQUEST,
                                      ATTITUDE_DEFINITION,
                                      SIMCONNECT_OBJECT_ID_USER,
                                      SIMCONNECT_PERIOD_SIM_FRAME,
                                      SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

    SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                      BOTTOMBAR_REQUEST,
                                      BOTTOMBAR_DEFINITION,
                                      SIMCONNECT_OBJECT_ID_USER,
                                      SIMCONNECT_PERIOD_SIM_FRAME,
                                      SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

    SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                      HSI_REQUEST,
                                      HSI_DEFINITION,
                                      SIMCONNECT_OBJECT_ID_USER,
                                      SIMCONNECT_PERIOD_SIM_FRAME,
                                      SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

    SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                      HSI_BRG_REQUEST,
                                      HSI_BRG_DEFINITION,
                                      SIMCONNECT_OBJECT_ID_USER,
                                      SIMCONNECT_PERIOD_SIM_FRAME,
                                      SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

    SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                      RADIO_REQUEST,
                                      RADIO_DEFINITION,
                                      SIMCONNECT_OBJECT_ID_USER,
                                      SIMCONNECT_PERIOD_SIM_FRAME,
                                      SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

    SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                      NAV_INFO_REQUEST,
                                      NAV_INFO_DEFINITION,
                                      SIMCONNECT_OBJECT_ID_USER,
                                      SIMCONNECT_PERIOD_SIM_FRAME,
                                      SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

    SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                      WIND_REQUEST,
                                      WIND_DEFINITION,
                                      SIMCONNECT_OBJECT_ID_USER,
                                      SIMCONNECT_PERIOD_SIM_FRAME,
                                      SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

    SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                      AP_INFO_REQUEST,
                                      AP_INFO_DEFINITION,
                                      SIMCONNECT_OBJECT_ID_USER,
                                      SIMCONNECT_PERIOD_SIM_FRAME,
                                      SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);


    switch (d_aircraftConfig.numEngines)
    {
        case 4:
            SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                              ENGINE4_REQUEST,
                                              ENGINE4_DEFINITION,
                                              SIMCONNECT_OBJECT_ID_USER,
                                              SIMCONNECT_PERIOD_SIM_FRAME,
                                              SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);
            SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                              ENGINE3_REQUEST,
                                              ENGINE3_DEFINITION,
                                              SIMCONNECT_OBJECT_ID_USER,
                                              SIMCONNECT_PERIOD_SIM_FRAME,
                                              SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);
        case 2:
            SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                              ENGINE2_REQUEST,
                                              ENGINE2_DEFINITION,
                                              SIMCONNECT_OBJECT_ID_USER,
                                              SIMCONNECT_PERIOD_SIM_FRAME,
                                              SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);
        case 1:
        default:
            SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                              ENGINE1_REQUEST,
                                              ENGINE1_DEFINITION,
                                              SIMCONNECT_OBJECT_ID_USER,
                                              SIMCONNECT_PERIOD_SIM_FRAME,
                                              SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);
    }


    SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                      AIRCRAFT_GENERAL_REQUEST,
                                      AIRCRAFT_GENERAL_DEFINITION,
                                      SIMCONNECT_OBJECT_ID_USER,
                                      SIMCONNECT_PERIOD_SIM_FRAME,
                                      SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);
}