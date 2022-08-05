#ifndef __FDC_SOCKET_HPP__
#define __FDC_SOCKET_HPP__


#include "common/dataIdentifiers.hpp"

#include <cstdint>
#include <QObject>
#include <QTcpSocket>

#include <QDebug>


class SimInterface;

struct SharedThreadData;

namespace definitions
{
struct ReferenceSpeed;
}

// encapsulates a QTcpSocket and handles its data and state
class FdcSocket : public QObject
{
    Q_OBJECT

public:

    FdcSocket(QTcpSocket *socket,
              uint64_t id,
              QObject *parent);

    ~FdcSocket();

    uint64_t id() const
    {
        return d_id;
    }

    const QString &endpointName() const
    {
        return d_endpointName;
    }

    void writeToSocket(const QByteArray &data)
    {
        d_socket->write(data);
    }

    void writeToSocket(const std::string &data)
    {
        d_socket->write(data.data(), data.size());
    }

    void connectSimSignals(const SimInterface *sim);

signals:

    void socketClosed(uint64_t id);
    void handshakeError(bool clientTooOld);
    void handshakeSuccess();
    void updateDefaultSpeedBugs(const QList<definitions::ReferenceSpeed> &newBugs);

    void newCommandString(const QByteArray &commandString);
    void aircraftLoaded();

private slots:

    void clientDisconnected();
    void receivedClientData();

    void receivedSimError(const QString &msg)
    {
        qCritical() << msg;
        QByteArray message = msg.toUtf8();

        const uint64_t size = message.size();

        message.prepend(reinterpret_cast<const char *>(&size), sizeof(size));
        message.prepend(QByteArray::fromStdString({ static_cast<char>(DataGroupIdentifier::SERVER_DATA),
                                                    static_cast<char>(ServerMessageIdentifier::ERROR_MSG) }));

        d_socket->write(message);
    }

private:

    static constexpr uint8_t s_communicationVersion = 3;

    const uint64_t d_id;

    QTcpSocket *d_socket;

    QString d_endpointName = "";

    QMetaObject::Connection d_sendDataConnection;
};

#endif  // __FDC_SOCKET_HPP__