#include "FdcSocket.hpp"
#include "SimInterface/SimInterface.hpp"

void FdcSocket::connectSimSignals(const SimInterface *sim)
{
    d_sendDataConnection = connect(sim,
                                   &SimInterface::sendData,
                                   d_socket,
                                   qOverload<const QByteArray &>(&QIODevice::write),
                                   Qt::QueuedConnection);

    connect(sim, &SimInterface::receivedError, this, &FdcSocket::receivedSimError, Qt::QueuedConnection);
}