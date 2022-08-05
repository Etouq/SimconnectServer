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
        std::string dataToSend = d_airspeedHandler.sendCurrentData();
        dataToSend += d_altitudeHandler.sendCurrentData();
        dataToSend += d_autopilotHandler.sendCurrentData();
        dataToSend += d_attitudeHandler.sendCurrentData();
        dataToSend += d_bottombarHandler.sendCurrentData();
        dataToSend += d_bearingHandler.sendCurrentData();
        dataToSend += d_hsiHandler.sendCurrentData();
        dataToSend += d_navInfoHandler.sendCurrentData();
        dataToSend += d_radioHandler.sendCurrentData();
        dataToSend += d_windHandler.sendCurrentData();
        dataToSend += d_miscHandler.sendCurrentData();
        dataToSend += d_aircraftHandler.sendCurrentData();
        dataToSend += d_engine1Handler.sendCurrentData();
        dataToSend += d_engine2Handler.sendCurrentData();
        dataToSend += d_engine3Handler.sendCurrentData();
        dataToSend += d_engine4Handler.sendCurrentData();

        emit sendData(QByteArray::fromStdString(dataToSend));
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