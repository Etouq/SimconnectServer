#ifndef __MISCHANDLER_HPP__
#define __MISCHANDLER_HPP__

#include "DataStruct.hpp"

#include <QByteArray>

typedef void *HANDLE;

namespace misc
{

class MiscHandler
{
    DataStruct d_previous;

public:

    MiscHandler() = default;

    void setupData(HANDLE simConnectHandle);

    [[nodiscard]] QByteArray processData(unsigned long *raw, bool *wpIdValid);

    QByteArray reset()
    {
        d_previous = DataStruct();

        return sendCurrentData();
    }

    [[nodiscard]] QByteArray sendCurrentData();
};

}  // namespace misc

#endif  // __MISCHANDLER_HPP__
