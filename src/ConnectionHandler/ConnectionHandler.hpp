#ifndef __CONNECTIONHANDLER_HPP__
#define __CONNECTIONHANDLER_HPP__

#include "common/dataIdentifiers.hpp"
#include "FdcSocket/FdcSocket.hpp"
#include "SimInterface/SharedThreadData.hpp"

#include <atomic>
#include <cstdint>
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

    Q_INVOKABLE QString getClientName(int idx)
    {
        return d_clientNames.at(idx);
    }

signals:
    void networkChanged(const QHostAddress &address, quint16 port);
    void openMessageBox(const QString &title, const QString &text);

    void simConnectionStateChanged(ConnectionState state);
    void clienConnectionStateChanged(ConnectionState state);

    void clientsChanged(int numClients);


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

    void clientHandshakeSuccess()
    {
        d_clientNames.clear();
        for (auto socket : d_connectedSockets)
            d_clientNames.append(socket.second->endpointName());

        emit clientsChanged(d_clientNames.size());
    }

    void broadcastToNetwork();


    void newIncomingConnection();

    // client
    void clientDisconnected(uint64_t id);


    // sim
    void simStartupFailed()
    {
        writeToConnectedSockets(QByteArray::fromStdString({ static_cast<char>(DataGroupIdentifier::SERVER_DATA),
                                                  static_cast<char>(ServerMessageIdentifier::SIM_STARTUP_FAILED) }));

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

        writeToConnectedSockets(QByteArray::fromStdString({ static_cast<char>(DataGroupIdentifier::SERVER_DATA),
                                                  static_cast<char>(ServerMessageIdentifier::QUIT) }));
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

    QStringList d_clientNames;

    // thread data and communication
    // used to signal the simconnect thread that the shared data has been updated
    std::atomic_bool d_sharedDataUpdated;
    std::shared_mutex d_sharedDataMutex;
    SharedThreadData d_sharedData;


    QTimer d_trySimStartTimer;
};


#endif  // __CONNECTIONHANDLER_HPP__
