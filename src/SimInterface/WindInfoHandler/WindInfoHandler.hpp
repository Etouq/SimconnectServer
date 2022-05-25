#ifndef __WINDINFOHANDLER_HPP__
#define __WINDINFOHANDLER_HPP__

#include "DataStruct.hpp"

#include <QObject>

typedef void *HANDLE;

class SimInterface;

namespace windinfo
{

class WindInfoHandler : public QObject
{
    Q_OBJECT

    DataStruct d_previous;

    const SimInterface *d_parent;

public:

    explicit WindInfoHandler(SimInterface *interface, QObject *parent = nullptr);

    void setupData(HANDLE simConnectHandle);

    void processData(unsigned long *raw);

    void reset();

    void sendCurrentData();
};

}  // namespace windinfo

#endif  // __WINDINFOHANDLER_HPP__
