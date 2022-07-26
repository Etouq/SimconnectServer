#include "mainwindow.hpp"
#include "common/dataIdentifiers.hpp"

void MainWindow::clearFlightplan()
{
    d_connectionHandler.sendDataToClients(QByteArray::fromStdString({ static_cast<char>(DataGroupIdentifier::MFD_DATA),
                                                  static_cast<char>(MfdIdentifier::CLEAR_FLIGHTPLAN) }));
}
