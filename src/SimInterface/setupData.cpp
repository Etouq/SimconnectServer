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

    switch (d_aircraftConfig.type)
    {
        case AircraftType::JET:
            d_aircraftHandler = new JetHandler();
            break;
        case AircraftType::PROP:
            d_aircraftHandler = new PropHandler();
            break;
        case AircraftType::TURBOPROP:
            d_aircraftHandler = new TurbopropHandler();
            break;
    }

    d_aircraftHandler->setupData(d_simConnectHandle, d_aircraftConfig);

    SimConnect_AddToDataDefinition(d_simConnectHandle,
                                   SET_XPNDR_STATE_DEF,
                                   "TRANSPONDER STATE:1",
                                   "enum",
                                   SIMCONNECT_DATATYPE_INT32);

    SimConnect_SubscribeToSystemEvent(d_simConnectHandle, EVENT_6HZ_ID, "6Hz");
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


    SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                      ENGINE_REQUEST,
                                      ENGINE_DEFINITION,
                                      SIMCONNECT_OBJECT_ID_USER,
                                      SIMCONNECT_PERIOD_SIM_FRAME,
                                      SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);
}