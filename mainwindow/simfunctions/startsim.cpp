#include "../mainwindow.h"

void MainWindow::startSim(ActiveAirplaneSettings settings)
{

    setSimConnectionState(CONNECTING);

    delete simThread;
    simThread = new SimconnectThread(&sharedDataUpdated, &sharedDataMutex, &sharedData, settings);

    connect(simThread,
            &SimconnectThread::sendData,
            tcpSocket,
            qOverload<const QByteArray &>(&QIODevice::write),
            Qt::UniqueConnection);
    connect(simThread,
            &SimconnectThread::receivedError,
            this,
            &MainWindow::showSimMsg,
            Qt::UniqueConnection);
    connect(simThread,
            &SimconnectThread::simConnectQuit,
            this,
            &MainWindow::quitFromSim,
            Qt::UniqueConnection);
    connect(simThread,
            &SimconnectThread::connected,
            this,
            &MainWindow::simConnected,
            Qt::UniqueConnection);
    connect(simThread,
            &SimconnectThread::simConnectionFailed,
            this,
            &MainWindow::simConnectFailed,
            Qt::UniqueConnection);

    simThread->start();
}
