#ifndef __ALTITUDEHANDLER_HPP__
#define __ALTITUDEHANDLER_HPP__

#include "DataStruct.hpp"
#include "common/dataIdentifiers.hpp"

#include <QObject>


typedef void *HANDLE;

class SimInterface;

namespace altitude
{

class AltitudeHandler : public QObject
{
    Q_OBJECT

    VerticalDeviationMode d_lastVertMode = VerticalDeviationMode::NONE;
    double d_deviation = 0.0;

    DataStruct d_previous;

    const SimInterface *d_parent;

public:

    explicit AltitudeHandler(SimInterface *interface, QObject *parent = nullptr);

    void setupData(HANDLE simConnectHandle);

    void processData(unsigned long *raw);

    void reset();

    void sendCurrentData();
};

}  // namespace altitude

#endif  // __ALTITUDEHANDLER_HPP__
