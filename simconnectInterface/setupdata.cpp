#include "simconnectthread.ih"

void SimconnectThread::setupData()
{
    d_lastPfdData = PfdCleanDataStruct();
    d_lastSlowData = SlowDatadefStruct();
    d_lastStringsData = StringsDataStruct();
    d_lastJetData = JetData();
    d_lastPropData = PropData();
    d_lastTurbopropData = TurbopropData();
    sendBlankPfdData();
    sendBlankEngineData();
    sendBlankSlowData();
    sendBlankStringsData();

    for(const dataDef& def : pfdDataDefVector)
        SimConnect_AddToDataDefinition(d_simConnectHandle, PFD_DATA_DEFINITION_ID, def.DatumName, def.UnitsName, def.DatumType, def.fEpsilon);

    for(const dataDef& def : slowDatadefVector)
        SimConnect_AddToDataDefinition(d_simConnectHandle, SLOW_DATA_DEFINITION_ID, def.DatumName, def.UnitsName, def.DatumType);

    for (const dataDef& def : stringsDatadefVector)
        SimConnect_AddToDataDefinition(d_simConnectHandle, STRINGS_DATA_DEFINITION_ID, def.DatumName, NULL, def.DatumType);

    setupAircraftData();

    SimConnect_SubscribeToSystemEvent(d_simConnectHandle, EVENT_6HZ_ID, "6Hz");
    SimConnect_SubscribeToSystemEvent(d_simConnectHandle, SIM_START_EVENT_ID, "SimStart");
    SimConnect_SubscribeToSystemEvent(d_simConnectHandle, SIM_STOP_EVENT_ID, "SimStop");
    SimConnect_RequestDataOnSimObject(d_simConnectHandle, SLOW_DATA_REQUEST_ID, SLOW_DATA_DEFINITION_ID, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SECOND);
    SimConnect_RequestDataOnSimObject(d_simConnectHandle, STRINGS_DATA_REQUEST_ID, STRINGS_DATA_DEFINITION_ID, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SECOND);
    SimConnect_RequestDataOnSimObject(d_simConnectHandle, PFD_DATA_REQUEST_ID, PFD_DATA_DEFINITION_ID, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SIM_FRAME, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);
    SimConnect_RequestDataOnSimObject(d_simConnectHandle, ENGINE_DATA_REQUEST_ID, ENGINE_DATA_DEFINITION_ID, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SIM_FRAME, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);
}
