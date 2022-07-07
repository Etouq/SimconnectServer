#include "ConnectionHandler.hpp"
#include "SimInterface/SimInterface.hpp"

#include <QTcpServer>
#include <QTcpSocket>


ConnectionHandler::ConnectionHandler(QObject *parent)
  : QObject(parent),
    d_sim(&d_threadDataUpdated, &d_threadDataMutex, &d_threadData, AircraftConfig())
{
    connect(&d_server, &QTcpServer::newConnection, this, &ConnectionHandler::newIncomingConnection);

    d_broadcastTimer.setInterval(500);
    connect(&d_broadcastTimer, &QTimer::timeout, this, &ConnectionHandler::broadcastToNetwork);
    d_broadcastTimer.start();

    d_trySimStartTimer.setInterval(10000);
    d_trySimStartTimer.setSingleShot(true);
    connect(&d_trySimStartTimer, &QTimer::timeout, this, &ConnectionHandler::startSim);
}

ConnectionHandler::~ConnectionHandler()
{
    d_broadcastSocket.abort();

    d_server.close();

    // tell the sim to close
    {
        QMutexLocker locker(&d_threadDataMutex);
        d_threadData.quit = true;
        locker.unlock();
    }
    d_threadDataUpdated.store(true, std::memory_order_seq_cst);

    // wait for the sim to be closed
    if (!d_sim.wait(1000))
        d_sim.terminate();   // terminate if thread took too long

    for (auto socket : d_connectedSockets)
    {
        delete socket.second;
    }

    d_connectedSockets.clear();
}
