#ifndef SIMCONNECTTHREAD_H
#define SIMCONNECTTHREAD_H

#include "aircraftData/engineDataDefs.h"
#include "aircraftData/miscDataDefs.h"
#include "aircraftData/pfdDataDefs.h"

#include <QMutex>
#include <QObject>
#include <QThread>


struct ActiveAirplaneSettings
{
    double secondDivFactor = 1;
    bool egtReplacesItt = false;
    bool torqueAsPct = false;
    bool usePropRpm = false;
    bool secondIsLoad = false;
    bool hasApu = false;
    bool hasFlaps = false;
    bool hasSpoilers = false;
    bool hasElevTrim = false;
    bool hasRudderTrim = false;
    bool hasAileronTrim = false;
    bool hasEgt = false;
    bool fuelQtyByVolume = false;
    bool fuelFlowByVolume = false;
    int8_t numEngines = 1;
    int8_t numTanks = 1;
    int8_t type = 0;   // 0: jet, 1: prop, 2: turboprop
    double n1Epsilon = 0;
    double n2Epsilon = 0;
    double ittEpsilon = 0;
    double rpmEpsilon = 0;
    double secondEpsilon = 0;
    double trqEpsilon = 0;
    double fuelQtyEpsilon = 0;
    double fuelFlowEpsilon = 0;
    double oilTempEpsilon = 0;
    double oilPressEpsilon = 0;
    double egtEpsilon = 0;
};

struct SharedDataStruct
{
    QByteArray commandString;
    ActiveAirplaneSettings airplaneSettings;
    bool airplaneSettingsChanged = false;
    bool quit = false;
};


class SimconnectThread : public QThread
{
    Q_OBJECT

    // shared data
    std::atomic_bool *sharedDataUpdated;
    QMutex *sharedDataMutex;

    SharedDataStruct *sharedData;

    // pfd data
    PfdAirspeedStruct d_lastAirspeedData;
    PfdAltimeterStruct d_lastAltimeterData;
    PfdAttitudeStruct d_lastAttitudeData;
    PfdBottombarStruct d_lastBottombarData;
    PfdHsiStruct d_lastHsiData;
    PfdHsiBrgStruct d_lastHsiBrgData;
    PfdRadioStruct d_lastRadioData;
    PfdNavInfoStruct d_lastNavInfoData;
    PfdWindStruct d_lastWindData;
    PfdApInfoStruct d_lastApInfoData;

    int32_t d_lastVertMode = -1;   // 0: none, 1: vdi, 2: gs, 3: gp, 4: gspreview

    bool d_lastDisplayDeviation = true;
    int32_t d_lastNavSource = -1;   // 0: GPS, 1: VOR1, 2: LOC1, 3: VOR2, 4: LOC2
    double d_lastCourse = -5000;
    double d_lastCourseDeviation = -5000;
    int32_t d_lastToFrom = -1;

    QByteArray d_lastAP_VerticalActive = "";
    QByteArray d_lastAP_ModeReference = "";
    QByteArray d_lastAP_Armed = "";
    QByteArray d_lastAP_ArmedReference = "";
    QByteArray d_lastAP_LateralActive = "";
    QByteArray d_lastAP_LateralArmed = "";

    // engine data
    JetData d_lastJetData;
    PropData d_lastPropData;
    TurbopropData d_lastTurbopropData;
    ActiveAirplaneSettings d_currentAirplaneSettings;

    // slow data
    SlowDatadefStruct d_lastSlowData;

    // strings data
    StringsDataStruct d_lastStringsData;

    // internal data
    bool updateAircraft = false;

    HANDLE d_simConnectHandle = NULL;

    void (SimconnectThread::*d_aircraftHandler)(SIMCONNECT_RECV_SIMOBJECT_DATA *) = nullptr;

    bool quit = false;

public:
    explicit SimconnectThread(std::atomic_bool *sharedAtomic,
                              QMutex *sharedMutex,
                              SharedDataStruct *sharedStruct,
                              const ActiveAirplaneSettings &airplaneStartSettings,
                              QObject *parent = nullptr);


    void run() override
    {
        if (tryConnecting())
            runDataLoop();
    }


signals:
    void sendData(const QByteArray &data);
    void receivedError(const QString &errorMsg);
    void simConnectQuit();
    void connected();
    void simConnectionFailed();

private:
    bool tryConnecting();
    void runDataLoop();

    void readSharedData();
    void readCommandString(const QByteArray &data);

    void setupData();
    void setupEvents();

    void getDispatches();

    void sendBlankPfdData();

    void sendBlankAirspeedData();
    void sendBlankAltimeterData();
    void sendBlankAttitudeData();
    void sendBlankBottombarData();
    void sendBlankHsiData();
    void sendBlankHsiBrgData();
    void sendBlankRadioData();
    void sendBlankNavInfoData();
    void sendBlankWindData();
    void sendBlankApInfoData();

    void sendBlankEngineData();
    void sendBlankSlowData();
    void sendBlankStringsData();

    void setupAircraftData();

    void handleAirspeedData(const PfdAirspeedStruct &newData);
    void handleAltimeterData(const PfdAltimeterStruct &newData);
    void handleAttitudeData(const PfdAttitudeStruct &newData);
    void handleBottombarData(const PfdBottombarStruct &newData);
    void handleHsiData(const PfdHsiStruct &newData);
    void handleHsiBrgData(const PfdHsiBrgStruct &newData);
    void handleRadioData(const PfdRadioStruct &newData);
    void handleNavInfoData(const PfdNavInfoStruct &newData);
    void handleWindData(const PfdWindStruct &newData);
    void handleApInfoData(const PfdApInfoStruct &newData);

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

#endif   // SIMCONNECTTHREAD_H
