#include "SimThreadManager.hpp"
#include "ConnectionHandler/FdcSocket/FdcSocket.hpp"

namespace sim
{

void SimThreadManager::initSocket(FdcSocket *newSocket) const
{
    newSocket->connectSimSignals(&d_sim);

    connect(newSocket, &FdcSocket::aircraftLoaded, this, &SimThreadManager::setAircraftLoaded);
    connect(newSocket, &FdcSocket::newCommandString, this, &SimThreadManager::setCommandString);
}

}