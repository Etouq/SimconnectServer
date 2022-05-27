#ifndef __NAVINFOHANDLER_HPP__
#define __NAVINFOHANDLER_HPP__

#include "DataStruct.hpp"

#include <QByteArray>

typedef void *HANDLE;

namespace navinfo
{

class NavInfoHandler
{

    DataStruct d_previous;

public:

    NavInfoHandler() = default;

    void setupData(HANDLE simConnectHandle);

    [[nodiscard]] QByteArray processData(unsigned long *raw);

    QByteArray reset()
    {
        d_previous = DataStruct();

        return sendCurrentData();
    }

    [[nodiscard]] QByteArray sendCurrentData();
};

}  // namespace navinfo

#endif  // __NAVINFOHANDLER_HPP__
