#include "../mainwindow.h"
#include "common/binaryutil.h"
#include "common/dataIdentifiers.h"

void MainWindow::showSimMsg(const QString &msg)
{
    DataIdentifiers id = DataIdentifiers::ERROR_STRING;
    QByteArray dataToSend(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend += BinaryUtil::toBinary(msg);
    tcpSocket->write(dataToSend);
}
