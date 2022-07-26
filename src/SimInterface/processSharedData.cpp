#include "enums.hpp"
#include "SimInterface.hpp"
#include "SimInterface/SharedThreadData.hpp"

#include <mutex>

void SimInterface::processSharedData()
{
    SharedThreadData temp;
    {
        std::shared_lock<std::shared_mutex> lock(d_sharedDataMutex);
        temp = d_sharedData;
        d_sharedData.commandString.clear();
        d_sharedData.aircraftConfigChanged = false;
        d_sharedData.aircraftLoaded = false;
    }

    if (temp.quit)
    {
        quit = true;
        return;
    }

    if (temp.commandString != "")
        parseCommandString(temp.commandString);

    if (temp.aircraftLoaded)
    {

        emit sendData(QByteArray::fromStdString(
          d_aircraftHandler.sendCurrentData() + d_engine1Handler.sendCurrentData() + d_engine2Handler.sendCurrentData()
          + d_engine3Handler.sendCurrentData() + d_engine4Handler.sendCurrentData() + d_miscHandler.sendCurrentData()));
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