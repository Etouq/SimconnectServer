#include "../mainwindow.h"
#include "common/dataIdentifiers.h"

void MainWindow::simConnectFailed()
{
    SimconnectIds id = SimconnectIds::SIM_CONNECTION_FAILED;
    tcpSocket->write(reinterpret_cast<const char *>(&id), sizeof(id));
    setSimConnectionState(DISCONNECTED);
}
