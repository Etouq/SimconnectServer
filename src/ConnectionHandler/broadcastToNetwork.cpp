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

    if (d_broadcastSocket.writeDatagram(datagramData, QHostAddress::Broadcast, 11999) == -1)
    {
        qDebug() << "failed to write datagram on address:" << QHostAddress(QHostAddress::Broadcast) << "and port: 11999\nwith error:" << d_broadcastSocket.errorString();
        emit openMessageBox("Simconnect Server", "failed to write datagram on address: " + QHostAddress(QHostAddress::Broadcast).toString() + " and port: 11999\nwith error: " + d_broadcastSocket.errorString());
    }
}