#include "ConnectionHandler.hpp"

#include <QTcpServer>
#include <QTcpSocket>


ConnectionHandler::ConnectionHandler(QObject *parent)
  : QObject(parent)
{

    connect(&d_server, &QTcpServer::newConnection, this, &ConnectionHandler::newIncomingConnection);

    d_broadcastTimer.setInterval(500);
    connect(&d_broadcastTimer, &QTimer::timeout, this, &ConnectionHandler::broadcastToNetwork);

}

ConnectionHandler::~ConnectionHandler()
{
    d_broadcastSocket.abort();

    d_server.close();


    for (auto socket : d_connectedSockets)
    {
        delete socket.second;
    }

    d_connectedSockets.clear();
}
