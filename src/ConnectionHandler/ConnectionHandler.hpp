#ifndef __CONNECTIONHANDLER_HPP__
#define __CONNECTIONHANDLER_HPP__

#include "common/converters/basicConverters.hpp"
#include "common/dataIdentifiers.hpp"
#include "common/appendData.hpp"
#include "common/definitions/AircraftConfig.hpp"
#include "SimInterface/SharedThreadData.hpp"

#include <atomic>
#include <cstdint>
#include <qglobal.h>
#include <qhostaddress.h>
#include <QMutex>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>


class QTcpSocket;

class SimInterface;

class ConnectionHandler : public QObject
{
    Q_OBJECT


    // thread data and communication
    // this is used to signal the simconnect thread that the shared data has been updated
    std::atomic_bool d_threadDataUpdated;
    QMutex d_threadDataMutex;
    SharedThreadData d_threadData;

    SimInterface *d_sim = nullptr;

    // network
    const uint8_t c_communicationVersion = 3;

    QTcpServer d_server;
    QTcpSocket *d_socket = new QTcpSocket();


public:

    ConnectionHandler(QObject *parent = nullptr);
    ~ConnectionHandler();

    enum ConnectionState
    {
        CONNECTED,
        CONNECTING,
        DISCONNECTING,
        DISCONNECTED
    };

    void init()
    {
        initializeServer();
    }

    void closeNow();

    void sendDataToClient(const QByteArray &data)
    {
        d_socket->write(data);
    }

signals:
    void networkChanged(const QHostAddress &address, quint16 port);
    void openMessageBox(const QString &title, const QString &text);

    void simConnectionStateChanged(ConnectionState state);
    void clienConnectionStateChanged(ConnectionState state);


private slots:
    void newIncomingConnection();

    // client
    void clientDisconnected();

    void receivedClientData();

    // sim
    void simStartupFailed()
    {
        QByteArray dataToSend;
        util::appendData(ServerMessageIdentifier::SIM_STARTUP_FAILED, dataToSend);
        d_socket->write(dataToSend);
        emit simConnectionStateChanged(ConnectionState::DISCONNECTED);
    }

    void simConnected()
    {
        emit simConnectionStateChanged(ConnectionState::CONNECTED);
    }

    void receivedSimError(const QString &msg)
    {
        QByteArray dataToSend;
        util::appendData(ServerMessageIdentifier::ERROR_MSG, msg.toUtf8(), dataToSend);
        d_socket->write(dataToSend);
    }

    void simClosed()
    {
        // sim called quit so sim is already closing, only need to tell the client to close let the
        // client close the connection
        emit simConnectionStateChanged(ConnectionState::DISCONNECTED);

        emit clienConnectionStateChanged(ConnectionState::DISCONNECTING);

        QByteArray dataToSend;
        util::appendData(ServerMessageIdentifier::QUIT, dataToSend);
        d_socket->write(dataToSend);
    }

private:

    void initializeServer();

    // client
    void clientSentQuitSignal();

    // sim
    void startSim(const AircraftConfig &config);
    void closeSim();
};


#endif  // __CONNECTIONHANDLER_HPP__
