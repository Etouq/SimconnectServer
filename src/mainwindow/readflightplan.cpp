#include "mainwindow.hpp"
#include "FlightplanReader/flightplanreader.hpp"
#include "common/converters/listConverters.hpp"
#include "common/dataIdentifiers.hpp"

#include <QFile>

void MainWindow::readFlightplan(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray flightplanBytes = Converters::convertList(FlightplanReader::readFile(file));
        file.close();

        d_connectionHandler.sendDataToClients(util::createMessage(MfdIdentifier::FLIGHTPLAN_LIST, flightplanBytes));
    }
}
