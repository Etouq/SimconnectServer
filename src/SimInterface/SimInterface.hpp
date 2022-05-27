#ifndef __SIMINTERFACE_HPP__
#define __SIMINTERFACE_HPP__

#include "DataHandlers/DataHandlers.hpp"

#include <QObject>
#include <QThread>


class SimInterface : public QThread
{
    Q_OBJECT

    AirspeedHandler d_airspeedHandler;
    AltitudeHandler d_altitudeHandler;
    ApInfoHandler d_autopilotHandler;
    AttitudeHandler d_attitudeHandler;
    BottombarHandler d_bottombarHandler;
    HsiBrgHandler d_bearingHandler;
    HsiHandler d_hsiHandler;
    NavInfoHandler d_navInfoHandler;
    RadioHandler d_radioHandler;
    WindInfoHandler d_windHandler;

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
