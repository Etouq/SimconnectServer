#include "ConnectionHandler.hpp"

void ConnectionHandler::clientDisconnected(uint64_t id)
{
    delete d_connectedSockets[id];

    d_connectedSockets.erase(id);

    d_clientNames.clear();
    for (auto socket : d_connectedSockets)
        d_clientNames.append(socket.second->endpointName());

    emit clientsChanged(d_clientNames.size());
}