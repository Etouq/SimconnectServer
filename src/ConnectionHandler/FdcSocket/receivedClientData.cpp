#include "FdcSocket.hpp"
#include "common/dataIdentifiers.hpp"
#include "common/definitions/BaseTypes.hpp"

#include <QHostAddress>

void FdcSocket::receivedClientData()
{
    ClientToServerIds identifier = ClientToServerIds::HANDSHAKE;
    while (!d_socket->atEnd())
    {
        QByteArray allData = d_socket->peek(d_socket->bytesAvailable());
        d_socket->startTransaction();
        d_socket->read(reinterpret_cast<char *>(&identifier), sizeof(identifier));

        switch (identifier)
        {
            case ClientToServerIds::HANDSHAKE:
            {
                uint8_t messageSize = 0;
                if (static_cast<size_t>(d_socket->bytesAvailable()) < sizeof(messageSize))
                {
                    d_socket->rollbackTransaction();
                    return;
                }

                d_socket->read(reinterpret_cast<char *>(&messageSize), sizeof(messageSize));

                uint8_t clientVersion = 0;
                if (static_cast<size_t>(d_socket->bytesAvailable()) < messageSize + sizeof(clientVersion))
                {
                    d_socket->rollbackTransaction();
                    return;
                }

                d_socket->commitTransaction();


                d_socket->read(reinterpret_cast<char *>(&clientVersion), sizeof(clientVersion));
                QByteArray modelName = d_socket->read(messageSize);

                if (clientVersion != s_communicationVersion)
                {
                    qDebug() << "handshake failure";
                    d_socket->disconnectFromHost();
                    emit handshakeError(clientVersion < s_communicationVersion);
                }
                else
                {
                    qDebug() << "handshake success, client name:" << modelName << "client address:" << d_socket->peerAddress();
                    d_endpointName = modelName + " @ " + d_socket->peerAddress().toString();
                    emit handshakeSuccess();
                }

                break;
            }
            case ClientToServerIds::AIRCRAFT_LOADED:
            {

                d_socket->commitTransaction();

                emit aircraftLoaded();
                break;
            }
            case ClientToServerIds::UPDATE_DEFAULT_SPEEDBUGS:
            {
                uint16_t size = 0;
                if (static_cast<uint64_t>(d_socket->bytesAvailable()) < sizeof(size))
                {
                    d_socket->rollbackTransaction();
                    return;
                }
                d_socket->read(reinterpret_cast<char *>(&size), sizeof(size));

                if (d_socket->bytesAvailable() < size)
                {
                    d_socket->rollbackTransaction();
                    return;
                }

                d_socket->commitTransaction();

                d_socket->read(reinterpret_cast<char *>(&size), sizeof(size));

                QList<definitions::ReferenceSpeed> newBugs;

                uint16_t speed = 0;
                uint8_t identSize = 0;

                while (size--)
                {
                    d_socket->read(reinterpret_cast<char *>(&speed), sizeof(speed));
                    d_socket->read(reinterpret_cast<char *>(&identSize), sizeof(identSize));

                    newBugs.append({ speed, QString::fromUtf8(d_socket->read(identSize)) });
                }

                emit updateDefaultSpeedBugs(newBugs);

                break;
            }
            case ClientToServerIds::COMMAND_STRING:
            {
                uint64_t commandSize = 0;
                if (d_socket->bytesAvailable() < sizeof(commandSize))
                {
                    d_socket->rollbackTransaction();
                    return;
                }

                d_socket->read(reinterpret_cast<char *>(&commandSize), sizeof(commandSize));

                if (d_socket->bytesAvailable() < commandSize)
                {
                    d_socket->rollbackTransaction();
                    return;
                }

                d_socket->commitTransaction();

                emit newCommandString(d_socket->read(commandSize));

                break;
            }
            default:
                qDebug() << "received unknown data:" << static_cast<int>(identifier);
                d_socket->commitTransaction();
                break;
        }
    }
}
