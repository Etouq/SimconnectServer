#include "../mainwindow.h"
#include "common/dataIdentifiers.h"

void MainWindow::clearFlightplan()
{
    SimconnectIds id = SimconnectIds::CLEAR_FLIGHTPLAN;
    tcpSocket->write(reinterpret_cast<char *>(&id), sizeof(id));
}
