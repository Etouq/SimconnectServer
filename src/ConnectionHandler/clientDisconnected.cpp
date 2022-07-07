#include "ConnectionHandler.hpp"

void ConnectionHandler::clientDisconnected(uint64_t id)
{
    delete d_connectedSockets[id];

    d_connectedSockets.erase(id);

    if (d_connectedSockets.empty())
    {
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

        emit simConnectionStateChanged(ConnectionState::DISCONNECTED);
    }
}