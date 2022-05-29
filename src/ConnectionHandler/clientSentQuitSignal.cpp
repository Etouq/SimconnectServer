#include "ConnectionHandler.hpp"
#include "SimInterface/SimInterface.hpp"

void ConnectionHandler::clientSentQuitSignal()
{
    {
    // first close simconnect thread
    if (d_sim != nullptr && d_sim->isRunning())
        closeSim();

    // then close the connection
    emit clienConnectionStateChanged(DISCONNECTING);
    d_socket->disconnectFromHost();
}
}