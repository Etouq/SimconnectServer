#ifndef __MISCHANDLER_HPP__
#define __MISCHANDLER_HPP__

#include "DataStruct.hpp"

#include <string>

typedef void *HANDLE;

namespace misc
{

class MiscHandler
{
    DataStruct d_previous;

public:

    MiscHandler() = default;

    void setupData(HANDLE simConnectHandle);

    [[nodiscard]] std::string processData(unsigned long *raw, bool *wpIdValid);

    std::string reset()
    {
        d_previous = DataStruct();

        return sendCurrentData();
    }

    [[nodiscard]] std::string sendCurrentData();
};

}  // namespace misc

#endif  // __MISCHANDLER_HPP__
