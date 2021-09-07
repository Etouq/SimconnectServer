#include "simconnectthread.ih"


void SimconnectThread::runDataLoop()
{
    setupData();

    SimconnectIds id = SimconnectIds::SIM_START_EVENT;
    emit sendData(QByteArray(reinterpret_cast<char *>(&id), sizeof(id)));

    while (!quit)
    {
        getDispatches();
        QThread::msleep(10);
    }

    SimConnect_Close(d_simConnectHandle);
}
