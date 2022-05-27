#ifndef __WINDINFOHANDLER_HPP__
#define __WINDINFOHANDLER_HPP__

#include "DataStruct.hpp"

#include <QByteArray>

typedef void *HANDLE;

namespace windinfo
{

class WindInfoHandler
{

    DataStruct d_previous;

public:

    WindInfoHandler() = default;

    void setupData(HANDLE simConnectHandle);

    [[nodiscard]] QByteArray processData(unsigned long *raw);

    QByteArray reset()
    {
        d_previous = DataStruct();

        return sendCurrentData();
    }

    [[nodiscard]] QByteArray sendCurrentData();
};

}  // namespace windinfo

#endif  // __WINDINFOHANDLER_HPP__
