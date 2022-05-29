#include "ConnectionHandler.hpp"
#include "SimInterface/SimInterface.hpp"

#include <QTcpServer>
#include <QTcpSocket>


ConnectionHandler::ConnectionHandler(QObject *parent)
  : QObject(parent)
{
    d_server.setMaxPendingConnections(1);
    connect(&d_server, &QTcpServer::newConnection, this, &ConnectionHandler::newIncomingConnection);

}

ConnectionHandler::~ConnectionHandler()
{
    delete d_socket;
    delete d_sim;
}
