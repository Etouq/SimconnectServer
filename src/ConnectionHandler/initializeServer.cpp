#include "ConnectionHandler.hpp"

#include <QMessageBox>
#include <QNetworkInterface>
#include <QNetworkProxy>
#include <QSettings>

void ConnectionHandler::initializeServer()
{

    QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
    bool found = false;
    QStringList errors;

    qDebug() << "found address list:" << addresses;

    QSettings settings;

    if (settings.contains("lastUsedAddress") && settings.contains("lastUsedPort"))
    {
        QHostAddress lastAddress = QHostAddress(settings.value("lastUsedAddress").toString());
        int lastPort = settings.value("lastUsedPort").toInt();

        if (addresses.contains(lastAddress))
        {
            found = d_server.listen(lastAddress, lastPort);

            if (!found)
                found = d_server.listen(lastAddress);
        }
    }

    if (!found)
    {
        // used if we can't find a working ipv4 address (prefer ipv4 since it is easier to type)
        QList<QHostAddress> ipv6Addresses;

        for (const QHostAddress &address : addresses)
        {
            if (!address.isLoopback())
            {
                if (address.protocol() == QAbstractSocket::IPv4Protocol)
                    found = d_server.listen(address);
                else if (address.protocol() == QAbstractSocket::IPv6Protocol)
                    ipv6Addresses.append(address);
            }

            if (found)
                break;

            // if (!address.isLoopback() && (address.protocol() == QAbstractSocket::IPv4Protocol || address.protocol()
            // == QAbstractSocket::IPv6Protocol))
            // {
            //     quint16 tcpPort = 12001;
            //     while (!d_server.listen(address, tcpPort) && tcpPort <= 12100)
            //     {
            //         errors.append(address.toString() + " - " + QString::number(tcpPort) + ": " +
            //         d_server.errorString());
            //         ++tcpPort;
            //     }

            //     if (tcpPort <= 12100)
            //     {
            //         found = true;
            //         break;
            //     }
            // }
        }

        if (!found)
        {
            for (const QHostAddress &address : ipv6Addresses)
            {
                found = d_server.listen(address);

                if (found)
                    break;
            }
        }
    }

    if (!found)
    {
        qDebug() << ("Unable to start the server.\n" + errors.join("\n"));
        return;
    }

    d_broadcastTimer.start();

    qDebug() << d_server.proxy();
    qDebug() << d_server.serverAddress() << "\t" << d_server.serverPort();

    settings.setValue("lastUsedAddress", d_server.serverAddress().toString());
    settings.setValue("lastUsedPort", d_server.serverPort());

    emit networkChanged(d_server.serverAddress().toString(), d_server.serverPort());
}
