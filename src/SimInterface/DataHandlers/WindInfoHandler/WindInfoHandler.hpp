#ifndef __WINDINFOHANDLER_HPP__
#define __WINDINFOHANDLER_HPP__

#include "DataStruct.hpp"

#include <string>

typedef void *HANDLE;

namespace windinfo
{

class WindInfoHandler
{

    DataStruct d_previous;

public:

    WindInfoHandler() = default;

    void setupData(HANDLE simConnectHandle);

    [[nodiscard]] std::string processData(unsigned long *raw);

    std::string reset()
    {
        d_previous = DataStruct();

        return sendCurrentData();
    }

    [[nodiscard]] std::string sendCurrentData();
};

}  // namespace windinfo

#endif  // __WINDINFOHANDLER_HPP__
