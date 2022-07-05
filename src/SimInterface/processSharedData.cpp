#include "enums.hpp"
#include "SimInterface.hpp"
#include "SimInterface/SharedThreadData.hpp"

#include <QMutexLocker>


void SimInterface::processSharedData()
{
    QMutexLocker locker(d_sharedDataMutex);
    SharedThreadData temp = *d_sharedData;
    d_sharedData->commandString = "";
    d_sharedData->aircraftConfigChanged = false;
    d_sharedData->aircraftLoaded = false;
    locker.unlock();

    if (temp.quit)
    {
        quit = true;
        return;
    }

    if (temp.commandString != "")
        parseCommandString(temp.commandString);

    if (temp.aircraftLoaded)
    {
        QByteArray dataToSend = d_aircraftHandler.sendCurrentData();
        dataToSend += d_engine1Handler.sendCurrentData();
        dataToSend += d_engine2Handler.sendCurrentData();
        dataToSend += d_engine3Handler.sendCurrentData();
        dataToSend += d_engine4Handler.sendCurrentData();
        dataToSend += d_miscHandler.sendCurrentData();
    }

    if (temp.aircraftConfigChanged)
    {
        SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                          ENGINE1_REQUEST,
                                          ENGINE1_DEFINITION,
                                          SIMCONNECT_OBJECT_ID_USER,
                                          SIMCONNECT_PERIOD_NEVER);
        SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                          ENGINE2_REQUEST,
                                          ENGINE2_DEFINITION,
                                          SIMCONNECT_OBJECT_ID_USER,
                                          SIMCONNECT_PERIOD_NEVER);
        SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                          ENGINE3_REQUEST,
                                          ENGINE3_DEFINITION,
                                          SIMCONNECT_OBJECT_ID_USER,
                                          SIMCONNECT_PERIOD_NEVER);
        SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                          ENGINE4_REQUEST,
                                          ENGINE4_DEFINITION,
                                          SIMCONNECT_OBJECT_ID_USER,
                                          SIMCONNECT_PERIOD_NEVER);
        SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                          AIRCRAFT_GENERAL_REQUEST,
                                          AIRCRAFT_GENERAL_DEFINITION,
                                          SIMCONNECT_OBJECT_ID_USER,
                                          SIMCONNECT_PERIOD_NEVER);

        d_aircraftConfig = temp.aircraftConfig;
        updateAircraft = true;
    }
}