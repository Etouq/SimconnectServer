#ifndef __HSIBRGHANDLER_HPP__
#define __HSIBRGHANDLER_HPP__

#include "DataStruct.hpp"

#include <string>

typedef void *HANDLE;

namespace hsibrg
{

class HsiBrgHandler
{

    DataStruct d_previous;

public:

    HsiBrgHandler() = default;

    void setupData(HANDLE simConnectHandle);

    [[nodiscard]] std::string processData(unsigned long *raw);

    std::string reset()
    {
        d_previous = DataStruct();

        return sendCurrentData();
    }

    [[nodiscard]] std::string sendCurrentData();
};

}  // namespace hsibrg

#endif  // __HSIBRGHANDLER_HPP__
