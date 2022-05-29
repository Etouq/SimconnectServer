#include "ConnectionHandler.hpp"
#include "SimInterface/SimInterface.hpp"

void ConnectionHandler::startSim(const AircraftConfig &config)
{
    emit simConnectionStateChanged(ConnectionState::CONNECTING);

    delete d_sim;
    d_sim = new SimInterface(&d_threadDataUpdated, &d_threadDataMutex, &d_threadData, config);

    connect(d_sim,
            &SimInterface::sendData,
            d_socket,
            qOverload<const QByteArray &>(&QIODevice::write),
            Qt::QueuedConnection);
    connect(d_sim,
            &SimInterface::receivedError,
            this,
            &ConnectionHandler::receivedSimError,
            Qt::QueuedConnection);
    connect(d_sim,
            &SimInterface::simConnectQuit,
            this,
            &ConnectionHandler::simClosed,
            Qt::QueuedConnection);
    connect(d_sim,
            &SimInterface::connected,
            this,
            &ConnectionHandler::simConnected,
            Qt::QueuedConnection);
    connect(d_sim,
            &SimInterface::simConnectionFailed,
            this,
            &ConnectionHandler::simStartupFailed,
            Qt::QueuedConnection);

    d_sim->start();
}