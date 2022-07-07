#include "FdcSocket.hpp"
#include "SimInterface/SimInterface.hpp"

void FdcSocket::clientDisconnected()
{
    disconnect(&d_sim,
            &SimInterface::sendData,
            d_socket,
            qOverload<const QByteArray &>(&QIODevice::write));


    if (d_socket->isOpen())
            d_socket->close();

        emit socketClosed(d_id);
}