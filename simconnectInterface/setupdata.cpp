#include "simconnectthread.ih"

void SimconnectThread::setupData()
{
    d_lastSlowData = SlowDatadefStruct();
    d_lastStringsData = StringsDataStruct();
    d_lastJetData = JetData();
    d_lastPropData = PropData();
    d_lastTurbopropData = TurbopropData();
    sendBlankPfdData();
    sendBlankEngineData();
    sendBlankSlowData();
    sendBlankStringsData();

    d_updateAltimeter = true;
    d_updateHsi = true;
    d_updateHsiBrg = true;
    d_updateWind = true;
    d_updateApInfo = true;

    for(const dataDef& def : pfdAirspeedDefs)
        SimConnect_AddToDataDefinition(d_simConnectHandle, AIRSPEED_DEFINITION, def.DatumName, def.UnitsName, def.DatumType, def.fEpsilon);

    for(const dataDef& def : pfdAltimeterDefs)
        SimConnect_AddToDataDefinition(d_simConnectHandle, ALTIMETER_DEFINITION, def.DatumName, def.UnitsName, def.DatumType, def.fEpsilon);

    for(const dataDef& def : pfdAttitudeDefs)
        SimConnect_AddToDataDefinition(d_simConnectHandle, ATTITUDE_DEFINITION, def.DatumName, def.UnitsName, def.DatumType, def.fEpsilon);

    for(const dataDef& def : pfdBottombarDefs)
        SimConnect_AddToDataDefinition(d_simConnectHandle, BOTTOMBAR_DEFINITION, def.DatumName, def.UnitsName, def.DatumType, def.fEpsilon);

    for(const dataDef& def : pfdHsiDefs)
        SimConnect_AddToDataDefinition(d_simConnectHandle, HSI_DEFINITION, def.DatumName, def.UnitsName, def.DatumType, def.fEpsilon);

    for(const dataDef& def : pfdHsiBrgDefs)
        SimConnect_AddToDataDefinition(d_simConnectHandle, HSI_BRG_DEFINITION, def.DatumName, def.UnitsName, def.DatumType, def.fEpsilon);

    for(const dataDef& def : pfdRadioDefs)
        SimConnect_AddToDataDefinition(d_simConnectHandle, RADIO_DEFINITION, def.DatumName, def.UnitsName, def.DatumType, def.fEpsilon);

    for(const dataDef& def : pfdNavInfoDefs)
        SimConnect_AddToDataDefinition(d_simConnectHandle, NAV_INFO_DEFINITION, def.DatumName, def.UnitsName, def.DatumType, def.fEpsilon);

    for(const dataDef& def : pfdWindDefs)
        SimConnect_AddToDataDefinition(d_simConnectHandle, WIND_DEFINITION, def.DatumName, def.UnitsName, def.DatumType, def.fEpsilon);

    for(const dataDef& def : pfdApInfoDefs)
        SimConnect_AddToDataDefinition(d_simConnectHandle, AP_INFO_DEFINITION, def.DatumName, def.UnitsName, def.DatumType, def.fEpsilon);

    for(const dataDef& def : slowDatadefVector)
        SimConnect_AddToDataDefinition(d_simConnectHandle, SLOW_DEFINITION, def.DatumName, def.UnitsName, def.DatumType);

    for (const dataDef& def : stringsDatadefVector)
        SimConnect_AddToDataDefinition(d_simConnectHandle, STRINGS_DEFINITION, def.DatumName, NULL, def.DatumType);

    setupAircraftData();

    SimConnect_SubscribeToSystemEvent(d_simConnectHandle, EVENT_6HZ_ID, "6Hz");
    SimConnect_SubscribeToSystemEvent(d_simConnectHandle, SIM_START_EVENT_ID, "SimStart");
    SimConnect_SubscribeToSystemEvent(d_simConnectHandle, SIM_STOP_EVENT_ID, "SimStop");
    SimConnect_RequestDataOnSimObject(d_simConnectHandle, SLOW_REQUEST, SLOW_DEFINITION, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SECOND);
    SimConnect_RequestDataOnSimObject(d_simConnectHandle, STRINGS_REQUEST, STRINGS_DEFINITION, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SECOND);

    SimConnect_RequestDataOnSimObject(d_simConnectHandle, AIRSPEED_REQUEST, AIRSPEED_DEFINITION, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SIM_FRAME, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

    SimConnect_RequestDataOnSimObject(d_simConnectHandle, ALTIMETER_REQUEST, ALTIMETER_DEFINITION, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SIM_FRAME, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

    SimConnect_RequestDataOnSimObject(d_simConnectHandle, ATTITUDE_REQUEST, ATTITUDE_DEFINITION, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SIM_FRAME, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

    SimConnect_RequestDataOnSimObject(d_simConnectHandle, BOTTOMBAR_REQUEST, BOTTOMBAR_DEFINITION, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SIM_FRAME, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

    SimConnect_RequestDataOnSimObject(d_simConnectHandle, HSI_REQUEST, HSI_DEFINITION, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SIM_FRAME, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

    SimConnect_RequestDataOnSimObject(d_simConnectHandle, HSI_BRG_REQUEST, HSI_BRG_DEFINITION, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SIM_FRAME, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

    SimConnect_RequestDataOnSimObject(d_simConnectHandle, RADIO_REQUEST, RADIO_DEFINITION, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SIM_FRAME, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

    SimConnect_RequestDataOnSimObject(d_simConnectHandle, NAV_INFO_REQUEST, NAV_INFO_DEFINITION, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SIM_FRAME, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

    SimConnect_RequestDataOnSimObject(d_simConnectHandle, WIND_REQUEST, WIND_DEFINITION, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SIM_FRAME, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

    SimConnect_RequestDataOnSimObject(d_simConnectHandle, AP_INFO_REQUEST, AP_INFO_DEFINITION, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SIM_FRAME, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);



    SimConnect_RequestDataOnSimObject(d_simConnectHandle, ENGINE_REQUEST, ENGINE_DEFINITION, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SIM_FRAME, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);
}
