#include "ConnectionHandler.hpp"
#include <mutex>

void ConnectionHandler::clientDisconnected(uint64_t id)
{
    delete d_connectedSockets[id];

    d_connectedSockets.erase(id);

    d_clientNames.clear();
    for (auto socket : d_connectedSockets)
        d_clientNames.append(socket.second->endpointName());

    emit clientsChanged(d_clientNames.size());

    if (d_connectedSockets.empty())
    {
        // tell the sim to close
        {
            std::unique_lock<std::shared_mutex> lock(d_sharedDataMutex);
            d_sharedData.quit = true;
        }
        d_sharedDataUpdated.store(true, std::memory_order_seq_cst);

        // wait for the sim to be closed
        if (!d_sim.wait(1000))
            d_sim.terminate();   // terminate if thread took too long

        emit simConnectionStateChanged(ConnectionState::DISCONNECTED);
    }
}