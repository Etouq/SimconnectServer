#include "../mainwindow.h"

#include <QMutexLocker>

void MainWindow::closeSim()
{
    setSimConnectionState(DISCONNECTING);
    // disconnect all signals
    disconnect(simThread,
               &SimconnectThread::sendData,
               tcpSocket,
               qOverload<const QByteArray &>(&QIODevice::write));
    disconnect(simThread, &SimconnectThread::receivedError, this, &MainWindow::showSimMsg);
    disconnect(simThread, &SimconnectThread::simConnectQuit, this, &MainWindow::quitFromSim);
    disconnect(simThread, &SimconnectThread::connected, this, &MainWindow::simConnected);
    disconnect(simThread,
               &SimconnectThread::simConnectionFailed,
               this,
               &MainWindow::simConnectFailed);

    // tell the sim to close
    QMutexLocker locker(&sharedDataMutex);
    sharedData.quit = true;
    locker.unlock();
    sharedDataUpdated.store(true, std::memory_order_seq_cst);

    // wait for the sim to be closed
    if (!simThread->wait(1000))
        simThread->terminate();   // terminate if thread took too long

    setSimConnectionState(DISCONNECTED);
}
