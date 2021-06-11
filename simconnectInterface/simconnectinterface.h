#ifndef SIMCONNECTINTERFACE_H
#define SIMCONNECTINTERFACE_H

//qt headers
#include <QObject>
#include <QByteArray>
#include <QString>

//misc headers
#include <cmath>
#include "simThreadMain.h"

//simconnect headers
#include <windows.h>
#include <windef.h>
#include "C:/MSFS SDK/SimConnect SDK/include/SimConnect.h"

//simconnect data headers
#include "../dataIdentifiers.h"
#include "../aircraftData/engineDataDefs.h"
#include "../aircraftData/pfdDataDefs.h"
#include "../aircraftData/miscDataDefs.h"


enum DATA_DEFINITION_IDS
{
    PFD_DATA_DEFINITION_ID,
    ENGINE_DATA_DEFINITION_ID,
    SLOW_DATA_DEFINITION_ID,
    STRINGS_DATA_DEFINITION_ID
};

enum DATA_REQUEST_IDS
{
    PFD_DATA_REQUEST_ID,
    ENGINE_DATA_REQUEST_ID,
    SLOW_DATA_REQUEST_ID,
    STRINGS_DATA_REQUEST_ID
};

enum EVENT_IDS
{
    EVENT_4SEC_ID,
    SIM_START_EVENT_ID,
    SIM_STOP_EVENT_ID
};



class SimconnectInterface : public QObject
{
    Q_OBJECT

    //pfd data
    PfdCleanDataStruct d_lastPfdData;

    int32_t d_lastVertMode = -1; // 0: none, 1: vdi, 2: gs, 3: gp, 4: gspreview

    bool d_lastDisplayDeviation = true;
    int32_t d_lastNavSource = -1; // 0: GPS, 1: VOR1, 2: LOC1, 3: VOR2, 4: LOC2
    double d_lastCourse = -5000;
    double d_lastCourseDeviation = -5000;
    int32_t d_lastToFrom = -1;

    QByteArray d_lastAP_VerticalActive = "a";
    QByteArray d_lastAP_ModeReference = "b";
    QByteArray d_lastAP_Armed = "c";
    QByteArray d_lastAP_ArmedReference = "d";
    QByteArray d_lastAP_LateralActive = "e";
    QByteArray d_lastAP_LateralArmed = "f";


    //engine data
    JetData d_lastJetData;
    PropData d_lastPropData;
    TurbopropData d_lastTurbopropData;
    ActiveAirplaneSettings d_currentAirplaneSettings;


    //slow data
    SlowDatadefStruct d_lastSlowData;

    //strings data
    StringsDataStruct d_lastStringsData;


    //internal data
    bool updateAircraft = false;
    uint8_t lastAtomicValue = 0;

    HANDLE d_simConnectHandle = NULL;

    void (SimconnectInterface::*d_engineHandler)(SIMCONNECT_RECV_SIMOBJECT_DATA *) = nullptr;
    void (SimconnectInterface::*d_aircraftHandler)(SIMCONNECT_RECV_SIMOBJECT_DATA *) = nullptr;

    bool quit = true;

public:
    explicit SimconnectInterface(uint8_t startingValue, QObject *parent = nullptr);

    bool tryConnecting();

    void run();




signals:
    void sendData(const QByteArray &data);
    void receivedError(const QString &errorMsg);
    void simConnectQuit();
    void connected();

private:
    void getDispatches();
    void sendBlankPfdData();
    void sendBlankEngineData();
    void sendBlankSlowData();
    void sendBlankStringsData();

    void setupAircraftData();
    void handlePfdData(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData);
    void handleSlowData(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData);
    void handleStringsData(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData);

    void handleJetSingleEngdata(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData);
    void handleJetTwinEngdata(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData);
    void handleJetQuadEngdata(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData);

    void handlePropSingleEngdata(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData);
    void handlePropTwinEngdata(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData);

    void handleTurbopropSingleEngdata(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData);
    void handleTurbopropTwinEngdata(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData);



};

#endif // SIMCONNECTINTERFACE_H
