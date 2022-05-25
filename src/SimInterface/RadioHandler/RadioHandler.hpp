#ifndef __RADIOHANDLER_HPP__
#define __RADIOHANDLER_HPP__

#include "DataStruct.hpp"

#include <QObject>

typedef void *HANDLE;

class SimInterface;

namespace radio
{

class RadioHandler : public QObject
{
    Q_OBJECT

    DataStruct d_previous;

    const SimInterface *d_parent;

public:

    explicit RadioHandler(SimInterface *interface, QObject *parent = nullptr);

    void setupData(HANDLE simConnectHandle);

    void processData(unsigned long *raw);

    void reset();

    void sendCurrentData();
};

}  // namespace radio

#endif  // __RADIOHANDLER_HPP__
