#include "simconnectthread.ih"
#include <QMutexLocker>

void SimconnectThread::readSharedData()
{
    QMutexLocker locker(sharedDataMutex);
    SharedDataStruct temp = *sharedData;
    locker.unlock();

    if (temp.quit)
    {
        quit = true;
        return;
    }

    SimConnect_RequestDataOnSimObject(d_simConnectHandle, ENGINE_REQUEST, ENGINE_DEFINITION, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_NEVER);
    d_currentAirplaneSettings = temp.airplaneSettings;
    updateAircraft = true;
}
