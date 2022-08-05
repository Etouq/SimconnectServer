#include "FdcSocket.hpp"

void FdcSocket::clientDisconnected()
{
    qDebug() << "socket with id:" << d_id << "closed";
    disconnect(d_sendDataConnection);


    if (d_socket->isOpen())
            d_socket->abort();

    emit socketClosed(d_id);
}