#include "FdcSocket.hpp"

FdcSocket::FdcSocket(QTcpSocket *socket,
                     uint64_t id,
                     QObject *parent)
  : QObject(parent),
    d_id(id)
{
    //d_socket->setSocketOption(QAbstractSocket::KeepAliveOption, 1);
    //d_socket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
    d_socket = socket;
    d_socket->setSocketOption(QAbstractSocket::LowDelayOption, 1);


    qDebug() << "started socket with id:" << QString::number(d_id);


    connect(d_socket, &QTcpSocket::disconnected, this, &FdcSocket::clientDisconnected, Qt::UniqueConnection);
    connect(d_socket, &QTcpSocket::readyRead, this, &FdcSocket::receivedClientData, Qt::UniqueConnection);


    d_socket->write(reinterpret_cast<const char *>(&s_communicationVersion), sizeof(s_communicationVersion));
}

FdcSocket::~FdcSocket()
{
    qDebug() << "destroyed socket with id:" << QString::number(d_id);
    disconnect(d_sendDataConnection);

    if (d_socket->state() == QTcpSocket::ConnectedState)
    {
        d_socket->write(QByteArray::fromStdString({ static_cast<char>(DataGroupIdentifier::SERVER_DATA),
                                                  static_cast<char>(ServerMessageIdentifier::SERVER_CLOSING) }));
        d_socket->flush();
        d_socket->disconnectFromHost();
    }

    d_socket->deleteLater();
}
