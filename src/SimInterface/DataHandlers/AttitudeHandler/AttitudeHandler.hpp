#ifndef __ATTITUDEHANDLER_HPP__
#define __ATTITUDEHANDLER_HPP__

#include "DataStruct.hpp"

#include <string>

typedef void *HANDLE;

namespace attitude
{

class AttitudeHandler
{

    DataStruct d_previous;

public:

    AttitudeHandler() = default;

    void setupData(HANDLE simConnectHandle);

    [[nodiscard]] std::string processData(unsigned long *raw);

    std::string reset()
    {
        d_previous = DataStruct();

        return sendCurrentData();
    }

    [[nodiscard]] std::string sendCurrentData();
};

}  // namespace attitude

#endif  // __ATTITUDEHANDLER_HPP__
