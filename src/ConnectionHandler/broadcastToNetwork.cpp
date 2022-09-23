#include "ConnectionHandler.hpp"

#include <QJsonDocument>
#include <QNetworkInterface>
#include <QVariant>


void ConnectionHandler::broadcastToNetwork()
{
    QVariantHash datagramBody;
    datagramBody["serverId"] = QByteArray("Simconnect Server");
    datagramBody["serverAddress"] = d_server.serverAddress().toString();
    datagramBody["serverPort"] = d_server.serverPort();

    QByteArray datagramData = QJsonDocument::fromVariant(datagramBody).toJson();

    if (qint64 sentSize = d_broadcastSocket.writeDatagram(datagramData, QHostAddress::Broadcast, 12000);
        sentSize < datagramData.size())
    {
        qDebug() << "datagram size:" << datagramData.size() << "sent size:" << sentSize;
        qDebug() << "failed to write datagram on address:" << QHostAddress(QHostAddress::Broadcast)
                 << "and port: 12000\nwith error:" << d_broadcastSocket.errorString();
    }
    // else
    // {
    //     qDebug() << "Sent broadcast";
    // }
}
