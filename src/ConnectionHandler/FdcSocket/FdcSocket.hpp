#ifndef __FDC_SOCKET_HPP__
#define __FDC_SOCKET_HPP__


#include "common/appendData.hpp"
#include "common/dataIdentifiers.hpp"

#include <atomic>
#include <cstdint>
#include <mutex>
#include <shared_mutex>

#include <QObject>
#include <QTcpSocket>

class SimInterface;

struct SharedThreadData;

// encapsulates a QTcpSocket and handles its data and state
class FdcSocket : public QObject
{
    Q_OBJECT

public:

    FdcSocket(QTcpSocket *socket,
              uint64_t id,
              std::atomic_bool &sharedDataUpdated,
              std::shared_mutex &sharedDataMutex,
              SharedThreadData &sharedData,
              SimInterface &sim,
              QObject *parent);

    ~FdcSocket();

    uint64_t id() const
    {
        return d_id;
    }

    void writeToSocket(const QByteArray &data)
    {
        d_socket->write(data);
    }

signals:

    void socketClosed(uint64_t id);
    void handshakeError(bool clientTooOld);

private slots:

    void clientDisconnected();
    void receivedClientData();

    void receivedSimError(const QString &msg)
    {
        QByteArray dataToSend;
        util::appendData(ServerMessageIdentifier::ERROR_MSG, msg.toUtf8(), dataToSend);
        d_socket->write(dataToSend);
    }

private:

    static constexpr uint8_t c_communicationVersion = 3;

    const uint64_t d_id;

    QTcpSocket *d_socket;

    std::atomic_bool &d_sharedDataUpdated;
    std::shared_mutex &d_sharedDataMutex;
    SharedThreadData &d_sharedData;

    SimInterface &d_sim;
};

#endif  // __FDC_SOCKET_HPP__