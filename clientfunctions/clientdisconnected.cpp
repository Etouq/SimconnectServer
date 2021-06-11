#include "mainwindow.h"
#include "dataIdentifiers.h"
#include "ui_mainwindow.h"

void MainWindow::clientDisconnected()
{
    setClientConnectionState(DISCONNECTED);
    if (simThread != nullptr && simThread->isRunning())
        closeSim();

    ui->clearFpButton->setDisabled(true);
    ui->readNewFpButton->setDisabled(true);


    tcpSocket->close();
    tcpServer.resumeAccepting();
    if (tcpServer.hasPendingConnections())
        newIncomingConnection();
}
