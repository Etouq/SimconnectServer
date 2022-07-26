#ifndef __NAVINFOHANDLER_HPP__
#define __NAVINFOHANDLER_HPP__

#include "DataStruct.hpp"

#include <string>

typedef void *HANDLE;

namespace navinfo
{

class NavInfoHandler
{

    DataStruct d_previous;

public:

    NavInfoHandler() = default;

    void setupData(HANDLE simConnectHandle);

    [[nodiscard]] std::string processData(unsigned long *raw);

    std::string reset()
    {
        d_previous = DataStruct();

        return sendCurrentData();
    }

    [[nodiscard]] std::string sendCurrentData();
};

}  // namespace navinfo

#endif  // __NAVINFOHANDLER_HPP__
