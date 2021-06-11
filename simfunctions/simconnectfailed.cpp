#include "mainwindow.h"
#include "dataIdentifiers.h"

void MainWindow::simConnectFailed()
{
    DataIdentifiers id = DataIdentifiers::SIM_CONNECTION_FAILED;
    tcpSocket->write(reinterpret_cast<char *>(&id), sizeof(id));
    setSimConnectionState(DISCONNECTED);
}
