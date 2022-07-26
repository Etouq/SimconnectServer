#ifndef __RADIOHANDLER_HPP__
#define __RADIOHANDLER_HPP__

#include "DataStruct.hpp"

#include <string>

typedef void *HANDLE;

namespace radio
{

class RadioHandler
{

    DataStruct d_previous;

public:

    RadioHandler() = default;

    void setupData(HANDLE simConnectHandle);

    [[nodiscard]] std::string processData(unsigned long *raw);

    std::string reset()
    {
        d_previous = DataStruct();

        return sendCurrentData();
    }

    [[nodiscard]] std::string sendCurrentData();
};

}  // namespace radio

#endif  // __RADIOHANDLER_HPP__
