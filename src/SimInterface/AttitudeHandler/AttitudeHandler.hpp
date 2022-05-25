#ifndef __ATTITUDEHANDLER_HPP__
#define __ATTITUDEHANDLER_HPP__

#include "DataStruct.hpp"

#include <QObject>

typedef void *HANDLE;

class SimInterface;

namespace attitude
{

class AttitudeHandler : public QObject
{
    Q_OBJECT

    DataStruct d_previous;

    const SimInterface *d_parent;

public:

    explicit AttitudeHandler(SimInterface *interface, QObject *parent = nullptr);

    void setupData(HANDLE simConnectHandle);

    void processData(unsigned long *raw);

    void reset();

    void sendCurrentData();
};

}  // namespace attitude

#endif  // __ATTITUDEHANDLER_HPP__
