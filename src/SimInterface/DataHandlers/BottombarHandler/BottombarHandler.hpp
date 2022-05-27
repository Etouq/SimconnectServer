#ifndef __BOTTOMBARHANDLER_HPP__
#define __BOTTOMBARHANDLER_HPP__

#include "DataStruct.hpp"

#include <QByteArray>

typedef void *HANDLE;

namespace bottombar
{

class BottombarHandler
{
    DataStruct d_previous;

public:

    BottombarHandler() = default;

    void setupData(HANDLE simConnectHandle);

    [[nodiscard]] QByteArray processData(unsigned long *raw);

    QByteArray reset()
    {
        d_previous = DataStruct();

        return sendCurrentData();
    }

    [[nodiscard]] QByteArray sendCurrentData();
};

}  // namespace bottombar

#endif  // __BOTTOMBARHANDLER_HPP__
