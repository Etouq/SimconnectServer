#include "ConnectionHandler.hpp"

#include <QMessageBox>
#include <QNetworkInterface>

void ConnectionHandler::initializeServer()
{

    QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
    bool found = false;
    QStringList errors;


    for (const QHostAddress &address : addresses)
    {

        if (!address.isLoopback() && (address.protocol() == QAbstractSocket::IPv4Protocol || address.protocol() == QAbstractSocket::IPv6Protocol))
        {
            quint16 tcpPort = 12000;
            while (!d_server.listen(address, tcpPort) && tcpPort <= 12100)
            {
                errors.append(address.toString() + " - " + QString::number(tcpPort) + ": " + d_server.errorString());
                ++tcpPort;
            }

            if (tcpPort <= 12100)
            {
                found = true;
                break;
            }
        }
    }

    if (!found)
    {
        emit openMessageBox("Simconnect Server", "Unable to start the server.\n" + errors.join("\n"));
        return;
    }

    emit networkChanged(d_server.serverAddress(), d_server.serverPort());
}
