#ifndef __BOTTOMBARHANDLER_HPP__
#define __BOTTOMBARHANDLER_HPP__

#include "DataStruct.hpp"

#include <string>

typedef void *HANDLE;

namespace bottombar
{

class BottombarHandler
{
    DataStruct d_previous;

public:

    BottombarHandler() = default;

    void setupData(HANDLE simConnectHandle);

    [[nodiscard]] std::string processData(unsigned long *raw);

    std::string reset()
    {
        d_previous = DataStruct();

        return sendCurrentData();
    }

    [[nodiscard]] std::string sendCurrentData();
};

}  // namespace bottombar

#endif  // __BOTTOMBARHANDLER_HPP__
