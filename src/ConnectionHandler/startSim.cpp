#include "ConnectionHandler.hpp"
#include "SimInterface/SimInterface.hpp"

void ConnectionHandler::startSim()
{
    if (d_sim.isRunning())
        return;

    emit simConnectionStateChanged(ConnectionState::CONNECTING);

    d_sim.start();
}