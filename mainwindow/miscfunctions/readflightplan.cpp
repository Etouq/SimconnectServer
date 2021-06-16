#include "../mainwindow.h"
#include "FlightplanReader/flightplanreader.h"
#include "common/dataIdentifiers.h"
#include "common/binaryutil.h"

void MainWindow::readFlightplan(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        FlightplanReader reader;
        QByteArray dataToSend = BinaryUtil::toBinary(reader.readFlightPlanFile(file));
        file.close();

        int64_t byteSize = dataToSend.size();
        dataToSend.prepend(reinterpret_cast<char *>(&byteSize), sizeof(byteSize));

        DataIdentifiers id = DataIdentifiers::FLIGHTPLAN_LIST;
        dataToSend.prepend(reinterpret_cast<char *>(&id), sizeof(id));

        tcpSocket->write(dataToSend);
    }
}
