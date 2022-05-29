#include "mainwindow.hpp"
#include "common/dataIdentifiers.hpp"

void MainWindow::clearFlightplan()
{
    SimconnectIds id = SimconnectIds::CLEAR_FLIGHTPLAN;
    d_connectionHandler.sendDataToClient(QByteArray(reinterpret_cast<const char *>(&id), sizeof(id)));
}
