#include "FdcSocket.hpp"
#include "common/dataIdentifiers.hpp"
#include "SimInterface/SharedThreadData.hpp"
#include "common/converters/basicConverters.hpp"
#include <QHostAddress>


void FdcSocket::receivedClientData()
{
    while (!d_socket->atEnd())
    {
        d_socket->startTransaction();
        ClientToServerIds identifier = ClientToServerIds::QUIT;
        d_socket->read(reinterpret_cast<char *>(&identifier), sizeof(identifier));

        switch (identifier)
        {
            case ClientToServerIds::HANDSHAKE:
            {
                uint8_t messageSize = 0;
                if (d_socket->bytesAvailable() < sizeof(messageSize))
                {
                    d_socket->rollbackTransaction();
                    return;
                }

                d_socket->read(reinterpret_cast<char *>(&messageSize), sizeof(messageSize));
                if (d_socket->bytesAvailable() < messageSize)
                {
                    d_socket->rollbackTransaction();
                    return;
                }

                d_socket->commitTransaction();

                uint8_t clientVersion = 0;
                d_socket->read(reinterpret_cast<char *>(&clientVersion), sizeof(clientVersion));
                QByteArray modelName = d_socket->read(messageSize - sizeof(clientVersion));

                if (clientVersion != c_communicationVersion)
                {
                    d_socket->disconnectFromHost();
                    emit handshakeError(clientVersion < c_communicationVersion);
                }
                else
                {
                    d_endpointName = modelName + " @ " + d_socket->peerAddress().toString();
                    emit handshakeSuccess(d_endpointName);
                }

                break;
            }
            case ClientToServerIds::AIRCRAFT_LOADED:
            {

                d_socket->commitTransaction();

                {
                    std::unique_lock<std::shared_mutex> lock(d_sharedDataMutex);
                    d_sharedData.aircraftLoaded = true;
                }

                d_sharedDataUpdated.store(true, std::memory_order_seq_cst);
                break;
            }
            case ClientToServerIds::COMMAND_STRING:
            {
                uint32_t commandSize = 0;
                if (d_socket->bytesAvailable() < sizeof(commandSize))
                {
                    d_socket->rollbackTransaction();
                    return;
                }

                Converters::convert(*d_socket, commandSize);
                if (d_socket->bytesAvailable() < commandSize)
                {
                    d_socket->rollbackTransaction();
                    return;
                }

                QByteArray commandString = d_socket->read(commandSize);
                d_socket->commitTransaction();

                {
                    std::unique_lock<std::shared_mutex> lock(d_sharedDataMutex);
                    d_sharedData.commandString += commandString;
                }

                d_sharedDataUpdated.store(true, std::memory_order_seq_cst);
                break;
            }
            default:
                qDebug() << "received unknown data:" << static_cast<int>(identifier);
                d_socket->commitTransaction();
                break;
        }
    }
}
