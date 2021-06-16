#include "../mainwindow.h"
#include "common/dataIdentifiers.h"
#include "common/binaryutil.h"

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
