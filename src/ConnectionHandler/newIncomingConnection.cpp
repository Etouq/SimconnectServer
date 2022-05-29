#include "ConnectionHandler.hpp"

void ConnectionHandler::newIncomingConnection()
{
    d_socket->abort();

    d_socket->setSocketOption(QAbstractSocket::KeepAliveOption, 1);
    d_socket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
    d_socket = d_server.nextPendingConnection();
    d_socket->setSocketOption(QAbstractSocket::LowDelayOption, 1);

    d_server.pauseAccepting();

    connect(d_socket, &QTcpSocket::disconnected, this, &ConnectionHandler::clientDisconnected, Qt::UniqueConnection);
    connect(d_socket, &QTcpSocket::readyRead, this, &ConnectionHandler::receivedClientData, Qt::UniqueConnection);

    emit clienConnectionStateChanged(ConnectionState::CONNECTED);

    SharedServerIds id = SharedServerIds::SIMCONNECT_SERVER;
    d_socket->write(reinterpret_cast<const char *>(&id), sizeof(id));
    d_socket->write(reinterpret_cast<const char *>(&c_communicationVersion), sizeof(c_communicationVersion));
}