#ifndef __AIRSPEEDHANDLER_HPP__
#define __AIRSPEEDHANDLER_HPP__

#include "DataStruct.hpp"

#include <string>


typedef void *HANDLE;

namespace airspeed
{

class AirspeedHandler
{

    DataStruct d_previous;

public:

    AirspeedHandler() = default;

    void setupData(HANDLE simConnectHandle);

    [[nodiscard]] std::string processData(unsigned long *raw);

    std::string reset()
    {
        d_previous = DataStruct();

        return sendCurrentData();
    }

    [[nodiscard]] std::string sendCurrentData();
};

}  // namespace airspeed

#endif  // __AIRSPEEDHANDLER_HPP__
