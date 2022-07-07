#include "FdcSocket.hpp"
#include "SimInterface/SimInterface.hpp"

FdcSocket::FdcSocket(QTcpSocket *socket,
                     uint64_t id,
                     std::atomic_bool &sharedDataUpdated,
                     std::shared_mutex &sharedDataMutex,
                     SharedThreadData &sharedData,
                     SimInterface &sim,
                     QObject *parent)
  : QObject(parent),
    d_id(id),
    d_sharedDataUpdated(sharedDataUpdated),
    d_sharedDataMutex(sharedDataMutex),
    d_sharedData(sharedData),
    d_sim(sim)
{
    //d_socket->setSocketOption(QAbstractSocket::KeepAliveOption, 1);
    //d_socket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
    d_socket = socket;
    d_socket->setSocketOption(QAbstractSocket::LowDelayOption, 1);


    qDebug() << "started socket with id:" << QString::number(d_id);

    connect(&sim,
            &SimInterface::sendData,
            d_socket,
            qOverload<const QByteArray &>(&QIODevice::write),
            Qt::QueuedConnection);
    connect(&sim, &SimInterface::receivedError, this, &FdcSocket::receivedSimError, Qt::QueuedConnection);

    connect(d_socket, &QTcpSocket::disconnected, this, &FdcSocket::clientDisconnected, Qt::UniqueConnection);
    connect(d_socket, &QTcpSocket::readyRead, this, &FdcSocket::receivedClientData, Qt::UniqueConnection);


    d_socket->write(reinterpret_cast<const char *>(&c_communicationVersion), sizeof(c_communicationVersion));
}

FdcSocket::~FdcSocket()
{
    disconnect(&d_sim, &SimInterface::sendData, d_socket, qOverload<const QByteArray &>(&QIODevice::write));

    if (d_socket->state() == QTcpSocket::ConnectedState)
    {
        d_socket->write(util::createMessage(ServerMessageIdentifier::QUIT));
        d_socket->flush();
        d_socket->disconnectFromHost();
    }

    d_socket->deleteLater();
}
