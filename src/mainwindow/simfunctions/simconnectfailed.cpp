#include "../mainwindow.hpp"
#include "common/dataIdentifiers.hpp"

void MainWindow::simConnectFailed()
{
    SimconnectIds id = SimconnectIds::SIM_CONNECTION_FAILED;
    tcpSocket->write(reinterpret_cast<const char *>(&id), sizeof(id));
    setSimConnectionState(DISCONNECTED);
}
