#ifndef __NAVINFOHANDLER_HPP__
#define __NAVINFOHANDLER_HPP__

#include "DataStruct.hpp"

#include <QObject>

typedef void *HANDLE;

class SimInterface;

namespace navinfo
{

class NavInfoHandler : public QObject
{
    Q_OBJECT

    DataStruct d_previous;

    const SimInterface *d_parent;

public:

    explicit NavInfoHandler(SimInterface *interface, QObject *parent = nullptr);

    void setupData(HANDLE simConnectHandle);

    void processData(unsigned long *raw);

    void reset();

    void sendCurrentData();
};

}  // namespace navinfo

#endif  // __NAVINFOHANDLER_HPP__
