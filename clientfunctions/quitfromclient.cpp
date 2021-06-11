#include "mainwindow.h"

void MainWindow::quitFromClient()
{
    //first close simconnect thread
    if(simThread != nullptr && simThread->isRunning())
        closeSim();

    //then close the connection
    setClientConnectionState(DISCONNECTING);
    tcpSocket->disconnectFromHost();
}
