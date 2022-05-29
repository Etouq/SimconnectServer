#include "ConnectionHandler.hpp"
#include "SimInterface/SimInterface.hpp"

void ConnectionHandler::closeNow()
{
    if (d_sim != nullptr && d_sim->isRunning())
        closeSim();

    d_socket->abort();
    d_server.close();
}