#ifndef __CONNECTIONHANDLER_HPP__
#define __CONNECTIONHANDLER_HPP__

#include "common/appendData.hpp"
#include "common/dataIdentifiers.hpp"
#include "FdcSocket/FdcSocket.hpp"
#include "SimInterface/SharedThreadData.hpp"

#include <atomic>
#include <cstdint>
#include <mutex>
#include <QMutex>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QUdpSocket>

#include <shared_mutex>
#include <unordered_map>


#include "SimInterface/SimInterface.hpp"

class ConnectionHandler : public QObject
{
    Q_OBJECT


    // thread data and communication
    // used to signal the simconnect thread that the shared data has been updated
    std::atomic_bool d_threadDataUpdated;
    QMutex d_threadDataMutex;
    SharedThreadData d_threadData;

    SimInterface d_sim;

    // network
    static constexpr uint8_t c_communicationVersion = 3;

    QTcpServer d_server;

    QUdpSocket d_broadcastSocket;
    QTimer d_broadcastTimer;

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

    void sendDataToClients(const QByteArray &data)
    {
        writeToConnectedSockets(data);
    }

signals:
    void networkChanged(const QHostAddress &address, quint16 port);
    void openMessageBox(const QString &title, const QString &text);

    void simConnectionStateChanged(ConnectionState state);
    void clienConnectionStateChanged(ConnectionState state);


private slots:

    void handshakeError(bool clientTooOld)
    {
        emit openMessageBox(
          "Error",
          clientTooOld
            ? "The network data transfer version of the Flight Display Companion is older than the one used by "
              "this application. Please update the Flight Display Companion."
            : "The network data transfer version of the Flight Display Companion is newer "
              "than the one used by this application. Please update this application.");
    }

    void broadcastToNetwork();


    void newIncomingConnection();

    // client
    void clientDisconnected(uint64_t id);


    // sim
    void simStartupFailed()
    {
        writeToConnectedSockets(util::createMessage(ServerMessageIdentifier::SIM_STARTUP_FAILED));

        emit simConnectionStateChanged(ConnectionState::DISCONNECTED);

        // try again in 10 seconds
        d_trySimStartTimer.start();
    }

    void simConnected()
    {
        emit simConnectionStateChanged(ConnectionState::CONNECTED);
    }

    void simClosed()
    {
        // sim called quit so sim is already closing, only need to tell the client to close let the
        // client close the connection
        emit simConnectionStateChanged(ConnectionState::DISCONNECTED);

        emit clienConnectionStateChanged(ConnectionState::DISCONNECTING);

        writeToConnectedSockets(util::createMessage(ServerMessageIdentifier::QUIT));
    }

private:

    void writeToConnectedSockets(const QByteArray &data)
    {
        for (auto socket : d_connectedSockets)
        {
            socket.second->writeToSocket(data);
        }
    }

    void initializeServer();


    // sim
    void startSim();


    std::unordered_map<uint64_t, FdcSocket *> d_connectedSockets;

    std::atomic_bool d_sharedDataUpdated;
    std::shared_mutex d_sharedDataMutex;
    SharedThreadData d_sharedData;


    QTimer d_trySimStartTimer;
};


#endif  // __CONNECTIONHANDLER_HPP__
