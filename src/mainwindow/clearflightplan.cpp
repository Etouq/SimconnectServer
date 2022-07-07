#include "mainwindow.hpp"
#include "common/dataIdentifiers.hpp"

void MainWindow::clearFlightplan()
{
    d_connectionHandler.sendDataToClients(util::createMessage(MfdIdentifier::CLEAR_FLIGHTPLAN));
}
