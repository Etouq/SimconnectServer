#include "ConnectionHandler.hpp"
#include "SimInterface/SimInterface.hpp"

#include <QTcpServer>
#include <QTcpSocket>


ConnectionHandler::ConnectionHandler(QObject *parent)
  : QObject(parent)
{
    d_server.setMaxPendingConnections(1);
    connect(&d_server, &QTcpServer::newConnection, this, &ConnectionHandler::newIncomingConnection);

    d_broadcastTimer.setInterval(1000);
    connect(&d_broadcastTimer, &QTimer::timeout, this, &ConnectionHandler::broadcastToNetwork);
    d_broadcastTimer.start();
}

ConnectionHandler::~ConnectionHandler()
{
    delete d_socket;
    delete d_sim;
}
