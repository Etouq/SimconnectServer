#ifndef __AIRSPEEDHANDLER_HPP__
#define __AIRSPEEDHANDLER_HPP__

#include "DataStruct.hpp"

#include <QObject>


typedef void *HANDLE;

class SimInterface;

namespace airspeed
{

class AirspeedHandler : public QObject
{
    Q_OBJECT

    DataStruct d_previous;

    const SimInterface *d_parent;

public:

    explicit AirspeedHandler(SimInterface *interface, QObject *parent = nullptr);

    void setupData(HANDLE simConnectHandle);

    void processData(unsigned long *raw);

    void reset();

    void sendCurrentData();
};

}  // namespace airspeed

#endif  // __AIRSPEEDHANDLER_HPP__
