#ifndef __SIMINTERFACE_HPP__
#define __SIMINTERFACE_HPP__

#include "AirspeedHandler/AirspeedHandler.hpp"
#include "AltitudeHandler/AltitudeHandler.hpp"

#include <QObject>
#include <QThread>

class SimInterface : public QThread
{
    Q_OBJECT

    AirspeedHandler airspeedHandler;
    AltitudeHandler altitudeHandler;

public:

    explicit SimInterface(QObject *parent = nullptr);

signals:
    void sendData(const QByteArray &data) const;
    void receivedError(const QString &errorMsg);
    void simConnectQuit();
    void connected();
    void simConnectionFailed();
};

#endif  // __SIMINTERFACE_HPP__
