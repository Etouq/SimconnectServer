#include "../mainwindow.h"
#include "common/dataIdentifiers.h"

void MainWindow::quitFromSim()
{
    // sim called quit so sim is already closing, only need to tell the client to close let the
    // client close the connection
    setSimConnectionState(DISCONNECTED);

    setClientConnectionState(DISCONNECTING);

    SimconnectIds id = SimconnectIds::QUIT;
    tcpSocket->write(reinterpret_cast<const char *>(&id), sizeof(id));
}
