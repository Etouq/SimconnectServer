#include "simconnectthread.ih"


void SimconnectThread::runDataLoop()
{
    setupData();

    DataIdentifiers id = DataIdentifiers::SIM_START_EVENT;
    emit sendData(QByteArray(reinterpret_cast<char *>(&id), sizeof(id)));

    while (!quit)
    {
        getDispatches();
    }

    SimConnect_Close(d_simConnectHandle);
}
