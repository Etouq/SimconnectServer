#include "ConnectionHandler.hpp"
#include <QJsonDocument>
#include <QVariant>

void ConnectionHandler::broadcastToNetwork()
{
    QVariantHash datagramBody;
    datagramBody["serverId"] = QByteArray("Simconnect Server");
    datagramBody["serverAddress"] = d_server.serverAddress().toString();
    datagramBody["serverPort"] = d_server.serverPort();

    QByteArray datagramData = QJsonDocument::fromVariant(datagramBody).toJson();

    d_broadcastSocket.writeDatagram(datagramData, QHostAddress::Broadcast, 12000);
}