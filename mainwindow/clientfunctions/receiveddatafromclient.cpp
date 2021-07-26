#include "../mainwindow.h"
#include "common/dataIdentifiers.h"
#include "common/binaryutil.h"
#include <QMessageBox>

void MainWindow::receivedDataFromClient()
{
    bool reading = true;

    while (reading && !tcpSocket->atEnd())
    {
        tcpSocket->startTransaction();
        ClientIds identifier = ClientIds::QUIT;
        tcpSocket->read(reinterpret_cast<char *>(&identifier), sizeof(identifier));

        switch(identifier)
        {
            case ClientIds::CLIENT_NETWORK_VERSION:
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
                    QMessageBox::critical(this, "Error", "The network data transfer version of the Flight Display Companion is newer than the one used by this application. Either update this application or revert the Flight Display Companion to the last working version.");
                    return;
                }
                if (latestSimconnectNetworkVersion > clientVersion)
                {
                    tcpSocket->disconnectFromHost();
                    QMessageBox::critical(this, "Error", "The network data transfer version of the Flight Display Companion is older than the one used by this application. Either update the Flight Display Companion or revert this application to the last working version.");
                    return;
                }
                break;
            }
            case ClientIds::QUIT:
            {
                tcpSocket->commitTransaction();
                quitFromClient();
                break;
            }
            case ClientIds::CHANGE_AIRCRAFT:
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
                locker.unlock();
                sharedDataUpdated.store(true, std::memory_order_seq_cst);
                break;
            }
            case ClientIds::START:
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
            default:
                qDebug() << "received unknown data:" << static_cast<int>(identifier);
                tcpSocket->commitTransaction();
                break;

        }

    }
}
