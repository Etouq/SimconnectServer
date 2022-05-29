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
    locker.unlock();

    if (temp.quit)
    {
        quit = true;
        return;
    }

    if (temp.commandString != "")
        parseCommandString(temp.commandString);

    if (temp.aircraftConfigChanged)
    {
        SimConnect_RequestDataOnSimObject(d_simConnectHandle,
                                          ENGINE_REQUEST,
                                          ENGINE_DEFINITION,
                                          SIMCONNECT_OBJECT_ID_USER,
                                          SIMCONNECT_PERIOD_NEVER);
        d_aircraftConfig = temp.aircraftConfig;
        updateAircraft = true;
    }
}