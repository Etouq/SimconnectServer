#include "ConnectionHandler.hpp"
#include "SimInterface/SimInterface.hpp"

void ConnectionHandler::closeSim()
{
    emit simConnectionStateChanged(ConnectionState::DISCONNECTING);

    // disconnect all signals
    disconnect(d_sim,
            &SimInterface::sendData,
            d_socket,
            qOverload<const QByteArray &>(&QIODevice::write));
    disconnect(d_sim,
            &SimInterface::receivedError,
            this,
            &ConnectionHandler::receivedSimError);
    disconnect(d_sim,
            &SimInterface::simConnectQuit,
            this,
            &ConnectionHandler::simClosed);
    disconnect(d_sim,
            &SimInterface::connected,
            this,
            &ConnectionHandler::simConnected);
    disconnect(d_sim,
            &SimInterface::simConnectionFailed,
            this,
            &ConnectionHandler::simStartupFailed);

    // tell the sim to close
    {
        QMutexLocker locker(&d_threadDataMutex);
        d_threadData.quit = true;
        locker.unlock();
    }
    d_threadDataUpdated.store(true, std::memory_order_seq_cst);

    // wait for the sim to be closed
    if (!d_sim->wait(1000))
        d_sim->terminate();   // terminate if thread took too long

    emit simConnectionStateChanged(ConnectionState::DISCONNECTED);
}