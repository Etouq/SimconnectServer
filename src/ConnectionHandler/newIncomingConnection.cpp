#include "ConnectionHandler.hpp"
#include <random>

void ConnectionHandler::newIncomingConnection()
{
    std::random_device rd;
    std::mt19937_64 gen(rd());

    FdcSocket *newSocket = new FdcSocket(d_server.nextPendingConnection(), gen(), d_sharedDataUpdated, d_sharedDataMutex, d_sharedData, d_sim, this);

    d_connectedSockets[newSocket->id()] = newSocket;

    // restart the sim if it isn't already running
    // if (!d_sim.isRunning())
    //     startSim();

}
