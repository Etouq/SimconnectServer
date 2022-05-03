#include "../mainwindow.hpp"
#include "common/binaryconverter.hpp"
#include "common/dataIdentifiers.hpp"

void MainWindow::showSimMsg(const QString &msg)
{
    SimconnectIds id = SimconnectIds::ERROR_STRING;
    QByteArray dataToSend(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend += BinaryConverter::toBinary(msg);
    tcpSocket->write(dataToSend);
}
