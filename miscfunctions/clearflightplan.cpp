#include "mainwindow.h"
#include "dataIdentifiers.h"

void MainWindow::clearFlightplan()
{
    DataIdentifiers id = DataIdentifiers::CLEAR_FLIGHTPLAN;
    tcpSocket->write(reinterpret_cast<char *>(&id), sizeof(id));
}
