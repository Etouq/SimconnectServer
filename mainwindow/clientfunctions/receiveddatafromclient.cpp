#include "../mainwindow.h"
#include "common/binaryutil.h"
#include "common/dataIdentifiers.h"

#include <QMessageBox>

void MainWindow::receivedDataFromClient()
{
    bool reading = true;

    while (reading && !tcpSocket->atEnd())
    {
        tcpSocket->startTransaction();
        ClientToServerIds identifier = ClientToServerIds::QUIT;
        tcpSocket->read(reinterpret_cast<char *>(&identifier), sizeof(identifier));

        switch (identifier)
        {
            case ClientToServerIds::CLIENT_NETWORK_VERSION:
            {
                if (tcpSocket->bytesAvailable() < sizeof(latestSimconnectNetworkVersion))
                {
                    tcpSocket->rollbackTransaction();
                    reading = false;
                    break;
                }

                uint8_t clientVersion = 0;
                tcpSocket->read(reinterpret_cast<char *>(&clientVersion), sizeof(clientVersion));
                tcpSocket->commitTransaction();

                if (latestSimconnectNetworkVersion < clientVersion)
                {
                    tcpSocket->disconnectFromHost();
                    QMessageBox::critical(
                      this,
                      "Error",
                      "The network data transfer version of the Flight Display Companion is newer "
                      "than the one used by this application. Please update this application.");
                    return;
                }
                if (latestSimconnectNetworkVersion > clientVersion)
                {
                    tcpSocket->disconnectFromHost();
                    QMessageBox::critical(
                      this,
                      "Error",
                      "The network data transfer version of the Flight Display Companion is older "
                      "than the one used by this application. Please update the Flight Display "
                      "Companion.");
                    return;
                }
                break;
            }
            case ClientToServerIds::QUIT:
            {
                tcpSocket->commitTransaction();
                quitFromClient();
                break;
            }
            case ClientToServerIds::CHANGE_AIRCRAFT:
            {
                if (tcpSocket->bytesAvailable() < 24)
                {
                    tcpSocket->rollbackTransaction();
                    reading = false;
                    break;
                }

                ActiveAirplaneSettings settings = BinaryUtil::readAirplaneSettings(*tcpSocket);
                tcpSocket->commitTransaction();


                QMutexLocker locker(&sharedDataMutex);

                sharedData.airplaneSettings = settings;
                sharedData.airplaneSettingsChanged = true;

                locker.unlock();

                sharedDataUpdated.store(true, std::memory_order_seq_cst);
                break;
            }
            case ClientToServerIds::START:
            {
                if (tcpSocket->bytesAvailable() < 112)
                {
                    tcpSocket->rollbackTransaction();
                    reading = false;
                    break;
                }

                ActiveAirplaneSettings settings = BinaryUtil::readAirplaneSettings(*tcpSocket);
                tcpSocket->commitTransaction();

                if (simThread == nullptr || !simThread->isRunning())
                {
                    QMutexLocker locker(&sharedDataMutex);

                    sharedData.airplaneSettings = settings;
                    sharedData.quit = false;

                    locker.unlock();


                    sharedDataUpdated.store(true, std::memory_order_seq_cst);

                    startSim(settings);
                }
                break;
            }
            case ClientToServerIds::SIM_COMMANDS:
            {
                uint8_t commandSize = 0;
                if (tcpSocket->bytesAvailable() < sizeof(commandSize))
                {
                    tcpSocket->rollbackTransaction();
                    reading = false;
                    break;
                }

                commandSize = BinaryUtil::readUint8_t(*tcpSocket);
                if (tcpSocket->bytesAvailable() < commandSize)
                {
                    tcpSocket->rollbackTransaction();
                    reading = false;
                    break;
                }

                QByteArray commandString = tcpSocket->read(commandSize);
                tcpSocket->commitTransaction();


                QMutexLocker locker(&sharedDataMutex);

                sharedData.commandString = commandString;

                locker.unlock();


                sharedDataUpdated.store(true, std::memory_order_seq_cst);
                break;
            }
            default:
                qDebug() << "received unknown data:" << static_cast<int>(identifier);
                tcpSocket->commitTransaction();
                break;
        }
    }
}
