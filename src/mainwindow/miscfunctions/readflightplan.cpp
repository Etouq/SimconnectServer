#include "../mainwindow.hpp"
#include "FlightplanReader/flightplanreader.hpp"
#include "common/binaryconverter.hpp"
#include "common/dataIdentifiers.hpp"

#include <QFile>

void MainWindow::readFlightplan(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray dataToSend = BinaryConverter::toBinary(FlightplanReader::readFile(file));
        file.close();

        int64_t byteSize = dataToSend.size();
        dataToSend.prepend(reinterpret_cast<char *>(&byteSize), sizeof(byteSize));

        SimconnectIds id = SimconnectIds::FLIGHTPLAN_LIST;
        dataToSend.prepend(reinterpret_cast<char *>(&id), sizeof(id));

        tcpSocket->write(dataToSend);
    }
}
