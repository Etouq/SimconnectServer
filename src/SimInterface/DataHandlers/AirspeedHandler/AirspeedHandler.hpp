#ifndef __AIRSPEEDHANDLER_HPP__
#define __AIRSPEEDHANDLER_HPP__

#include "DataStruct.hpp"

#include <QByteArray>


typedef void *HANDLE;

namespace airspeed
{

class AirspeedHandler
{

    DataStruct d_previous;

public:

    AirspeedHandler() = default;

    void setupData(HANDLE simConnectHandle);

    [[nodiscard]] QByteArray processData(unsigned long *raw);

    QByteArray reset()
    {
        d_previous = DataStruct();

        return sendCurrentData();
    }

    [[nodiscard]] QByteArray sendCurrentData();
};

}  // namespace airspeed

#endif  // __AIRSPEEDHANDLER_HPP__
