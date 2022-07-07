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
        QByteArray dataToSend = Converters::convertList(FlightplanReader::readFile(file));
        file.close();

        int64_t byteSize = dataToSend.size();
        dataToSend.prepend(reinterpret_cast<const char *>(&byteSize), sizeof(byteSize));

        MfdIdentifier id = MfdIdentifier::FLIGHTPLAN_LIST;
        dataToSend.prepend(reinterpret_cast<const char *>(&id), sizeof(id));
        constexpr DataGroupIdentifier groupId = DataGroupIdentifier::MFD_DATA;
        dataToSend.prepend(reinterpret_cast<const char *>(&groupId), sizeof(groupId));

        d_connectionHandler.sendDataToClients(dataToSend);
    }
}
