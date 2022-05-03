#include "../mainwindow.hpp"
#include "common/dataIdentifiers.hpp"

void MainWindow::clearFlightplan()
{
    SimconnectIds id = SimconnectIds::CLEAR_FLIGHTPLAN;
    tcpSocket->write(reinterpret_cast<char *>(&id), sizeof(id));
}
