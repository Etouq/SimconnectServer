#include "mainwindow.hpp"
#include "common/dataIdentifiers.hpp"

void MainWindow::clearFlightplan()
{
    MfdIdentifier id = MfdIdentifier::CLEAR_FLIGHTPLAN;
    QByteArray dataToSend;
    util::appendData(MfdIdentifier::CLEAR_FLIGHTPLAN, dataToSend);
    d_connectionHandler.sendDataToClients(dataToSend);
}
