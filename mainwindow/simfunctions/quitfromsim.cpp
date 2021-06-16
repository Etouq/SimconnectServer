#include "../mainwindow.h"
#include "common/dataIdentifiers.h"

void MainWindow::quitFromSim()
{
    //sim called quit so sim is already closing, only need to tell the client to close let the client close the connection
    setSimConnectionState(DISCONNECTED);

    setClientConnectionState(DISCONNECTING);

    DataIdentifiers id = DataIdentifiers::QUIT;
    tcpSocket->write(reinterpret_cast<char *>(&id), sizeof(id));
}
