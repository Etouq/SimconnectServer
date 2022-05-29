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
        if (!address.isLoopback() && address.protocol() == QAbstractSocket::IPv4Protocol)
        {
            if (d_server.listen(address))
            {
                found = true;
                break;
            }
            else
            {
                errors.append(address.toString() + ": " + d_server.errorString());
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
