#ifndef __HSIBRGHANDLER_HPP__
#define __HSIBRGHANDLER_HPP__

#include "DataStruct.hpp"

#include <QObject>

typedef void *HANDLE;

class SimInterface;

namespace hsibrg
{

class HsiBrgHandler : public QObject
{
    Q_OBJECT

    DataStruct d_previous;

    const SimInterface *d_parent;

public:

    explicit HsiBrgHandler(SimInterface *interface, QObject *parent = nullptr);

    void setupData(HANDLE simConnectHandle);

    void processData(unsigned long *raw);

    void reset();

    void sendCurrentData();
};

}  // namespace hsibrg

#endif  // __HSIBRGHANDLER_HPP__
