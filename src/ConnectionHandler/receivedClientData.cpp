#include "ConnectionHandler.hpp"
#include "SimInterface/SimInterface.hpp"
#include "common/dataIdentifiers.hpp"
#include "common/converters/listConverters.hpp"


void ConnectionHandler::receivedClientData()
{
    while (!d_socket->atEnd())
    {
        d_socket->startTransaction();
        ClientToServerIds identifier = ClientToServerIds::QUIT;
        d_socket->read(reinterpret_cast<char *>(&identifier), sizeof(identifier));

        switch (identifier)
        {
            case ClientToServerIds::CLIENT_NETWORK_VERSION:
            {
                if (d_socket->bytesAvailable() < sizeof(c_communicationVersion))
                {
                    d_socket->rollbackTransaction();
                    return;
                }

                uint8_t clientVersion = 0;
                d_socket->read(reinterpret_cast<char *>(&clientVersion), sizeof(clientVersion));
                d_socket->commitTransaction();

                if (clientVersion > c_communicationVersion)
                {
                    d_socket->disconnectFromHost();
                    emit openMessageBox("Error",
                                        "The network data transfer version of the Flight Display Companion is newer "
                                        "than the one used by this application. Please update this application.");
                    return;
                }
                if (clientVersion < c_communicationVersion)
                {
                    d_socket->disconnectFromHost();
                    emit openMessageBox(
                      "Error",
                      "The network data transfer version of the Flight Display Companion is older than the one used by "
                      "this application. Please update the Flight Display Companion.");
                    return;
                }
                break;
            }
            case ClientToServerIds::QUIT:
            {
                d_socket->commitTransaction();
                clientSentQuitSignal();
                break;
            }
            case ClientToServerIds::AIRCRAFT_LOADED:
            {

                d_socket->commitTransaction();


                QMutexLocker locker(&d_threadDataMutex);
                d_threadData.aircraftLoaded = true;
                locker.unlock();

                d_threadDataUpdated.store(true, std::memory_order_seq_cst);
                break;
            }
            case ClientToServerIds::START:
            {
                if (d_socket->bytesAvailable() < 135)
                {
                    d_socket->rollbackTransaction();
                    return;
                }

                AircraftConfig config;// = Converters::convert<AircraftConfig>(*d_socket);
                d_socket->commitTransaction();

                if (d_sim == nullptr || !d_sim->isRunning())
                {
                    QMutexLocker locker(&d_threadDataMutex);

                    d_threadData.aircraftConfig = config;
                    d_threadData.quit = false;

                    locker.unlock();


                    d_threadDataUpdated.store(false, std::memory_order_seq_cst);

                    startSim(config);
                }
                break;
            }
            case ClientToServerIds::COMMAND_STRING:
            {
                uint8_t commandSize = 0;
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


                QMutexLocker locker(&d_threadDataMutex);

                d_threadData.commandString = commandString;

                locker.unlock();


                d_threadDataUpdated.store(true, std::memory_order_seq_cst);
                break;
            }
            default:
                qDebug() << "received unknown data:" << static_cast<int>(identifier);
                d_socket->commitTransaction();
                break;
        }
    }
}
