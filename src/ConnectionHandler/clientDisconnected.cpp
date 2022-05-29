#include "ConnectionHandler.hpp"
#include "SimInterface/SimInterface.hpp"

void ConnectionHandler::clientDisconnected()
{
    emit clienConnectionStateChanged(DISCONNECTED);

    if (d_sim != nullptr && d_sim->isRunning())
        closeSim();


    d_socket->close();
    d_server.resumeAccepting();
    if (d_server.hasPendingConnections())
        newIncomingConnection();
}