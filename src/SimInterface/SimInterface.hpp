#ifndef __SIMINTERFACE_HPP__
#define __SIMINTERFACE_HPP__

#include "common/definitions/AircraftConfig.hpp"
#include "SharedThreadData.hpp"
#include "windows.h"
#include "common/dataIdentifiers.hpp"
#include "DataHandlers/DataHandlers.hpp"
#include "common/appendData.hpp"

#include <atomic>
#include <QMutex>
#include <QObject>
#include <QThread>

#include "C:/MSFS SDK/SimConnect SDK/include/SimConnect.h"

class SimInterface : public QThread
{
    Q_OBJECT

    // inter-thread communication
    std::atomic_bool *d_sharedDataUpdated;
    QMutex *d_sharedDataMutex;
    SharedThreadData *d_sharedData;

    // data handlers
    AirspeedHandler d_airspeedHandler;
    AltitudeHandler d_altitudeHandler;
    ApInfoHandler d_autopilotHandler;
    AttitudeHandler d_attitudeHandler;
    BottombarHandler d_bottombarHandler;
    HsiBrgHandler d_bearingHandler;
    HsiHandler d_hsiHandler;
    NavInfoHandler d_navInfoHandler;
    RadioHandler d_radioHandler;
    WindInfoHandler d_windHandler;
    MiscHandler d_miscHandler;

    AircraftHandler d_aircraftHandler;

    EngineHandler d_engine1Handler = EngineHandler(1);
    EngineHandler d_engine2Handler = EngineHandler(2);
    EngineHandler d_engine3Handler = EngineHandler(3);
    EngineHandler d_engine4Handler = EngineHandler(4);


    // internal data
    bool updateAircraft = false;
    AircraftConfig d_aircraftConfig;

    HANDLE d_simConnectHandle = NULL;

    bool quit = false;


public:

    explicit SimInterface(std::atomic_bool *sharedAtomic,
                              QMutex *sharedMutex,
                              SharedThreadData *sharedData,
                              const AircraftConfig &airplaneStartConfig,
                              QObject *parent = nullptr);

    void run() override
    {
        if (tryConnecting())
        {
            setupEvents();
            setupData();

            QByteArray dataToSend;
            util::appendData(ServerMessageIdentifier::SIM_START_EVENT, dataToSend);
            emit sendData(dataToSend);

            while (!quit)
            {
                processDispatches();
                QThread::msleep(15);
            }

            SimConnect_Close(d_simConnectHandle);
        }
    }

signals:
    void sendData(const QByteArray &data) const;
    void receivedError(const QString &errorMsg);
    void simConnectQuit();
    void connected();
    void simConnectionFailed();

private:

    bool tryConnecting();

    void processDispatches();

    void processException(DWORD exceptionId);

    void processSharedData();
    void parseCommandString(const QByteArray &data);

    void setupData();
    void setupEvents();
};

#endif  // __SIMINTERFACE_HPP__
