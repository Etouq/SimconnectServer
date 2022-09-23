#include "ConnectionHandler.hpp"

#include <random>
#include <QDebug>

void ConnectionHandler::newIncomingConnection()
{
    qDebug() << "new incoming connection";
    std::random_device rd;
    std::mt19937_64 gen(rd());

    FdcSocket *newSocket = new FdcSocket(d_server.nextPendingConnection(), gen(), this);


    connect(newSocket, &FdcSocket::handshakeSuccess, this, &ConnectionHandler::clientHandshakeSuccess);
    connect(newSocket, &FdcSocket::socketClosed, this, &ConnectionHandler::clientDisconnected);

    d_connectedSockets[newSocket->id()] = newSocket;

    emit initSocket(newSocket);
}
