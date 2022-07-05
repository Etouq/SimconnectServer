#ifndef __SHARED_THREAD_DATA__
#define __SHARED_THREAD_DATA__

#include <QByteArray>
#include "common/definitions/AircraftConfig.hpp"

struct SharedThreadData
{
    QByteArray commandString;
    AircraftConfig aircraftConfig;
    bool aircraftConfigChanged = false;
    bool aircraftLoaded = false;
    bool quit = false;
};

#endif  // __SHARED_THREAD_DATA__