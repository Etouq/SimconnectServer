#ifndef __CONNECTIONHANDLER_HPP__
#define __CONNECTIONHANDLER_HPP__

#include "common/dataIdentifiers.hpp"
#include "FdcSocket/FdcSocket.hpp"
#include "FlightplanManager/FlightPlanWaypoint.hpp"
#include "common/definitions/AircraftDefinition/AircraftDefinition.hpp"

#include <cstdint>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QUdpSocket>

#include <unordered_map>


class FlightplanManager;

namespace sim
{
class SimThreadManager;
}

class ConnectionHandler : public QObject
{
    Q_OBJECT


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

    void clientsChanged(int numClients);

    void initSocket(FdcSocket *newSocket);

public slots:

    void aircraftSelected(const definitions::AircraftDefinition &definition)
    {
        const QByteArray definitionBinary = definition.toBinary();

        const uint64_t definitionSize = definitionBinary.size();

        QByteArray completeBinary =
          QByteArray::fromStdString({ static_cast<char>(DataGroupIdentifier::SERVER_DATA),
                                      static_cast<char>(ServerMessageIdentifier::LOAD_AIRCRAFT) })
            .append(reinterpret_cast<const char *>(&definitionSize), sizeof(definitionSize))
            .append(definitionBinary);

        qDebug() << "sending aircraft:" << definition.name << "with size:" << definitionSize;

        for (const auto &[key, client] : d_connectedSockets)
        {
            client->writeToSocket(completeBinary);
        }
    }

    void updateActiveLegIdx(int32_t idx)
    {
        const QByteArray dataToSend =
          QByteArray::fromStdString(
            { static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::FLIGHTPLAN_LEG_IDX) })
            .append(reinterpret_cast<const char *>(&idx), sizeof(idx));

        for (const auto &[key, client] : d_connectedSockets)
        {
            client->writeToSocket(dataToSend);
        }
    }

    void flightplanChanged(const std::vector<FlightPlanWaypoint> &newPlan)
    {
        if (newPlan.empty())
        {

            const std::string clearPlanString(
              { static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::CLEAR_FLIGHTPLAN) });

            for (const auto &[key, client] : d_connectedSockets)
            {
                client->writeToSocket(clearPlanString);
            }
        }

        const uint64_t listSize = newPlan.size();

        std::string planBinaryData(reinterpret_cast<const char *>(&listSize), sizeof(listSize));

        for (const FlightPlanWaypoint &waypoint : newPlan)
        {
            planBinaryData += waypoint.toBinary();
        }

        const uint64_t binarySize = planBinaryData.size();
        planBinaryData.insert(0, reinterpret_cast<const char *>(&binarySize), sizeof(binarySize));

        planBinaryData.insert(
          0,
          { static_cast<char>(DataGroupIdentifier::MFD_DATA), static_cast<char>(MfdIdentifier::FLIGHTPLAN_LIST) });


        for (const auto &[key, client] : d_connectedSockets)
        {
            client->writeToSocket(planBinaryData);
        }
    }

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

private:

    void writeToConnectedSockets(const QByteArray &data)
    {
        for (auto socket : d_connectedSockets)
        {
            socket.second->writeToSocket(data);
        }
    }

    void initializeServer();


    static constexpr uint8_t c_communicationVersion = 3;

    QTcpServer d_server;

    QUdpSocket d_broadcastSocket;
    QTimer d_broadcastTimer;

    std::unordered_map<uint64_t, FdcSocket *> d_connectedSockets;

    QStringList d_clientNames;
};


#endif  // __CONNECTIONHANDLER_HPP__
