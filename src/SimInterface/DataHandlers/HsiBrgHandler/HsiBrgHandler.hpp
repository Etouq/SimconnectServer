#ifndef __HSIBRGHANDLER_HPP__
#define __HSIBRGHANDLER_HPP__

#include "DataStruct.hpp"

#include <QByteArray>

typedef void *HANDLE;

namespace hsibrg
{

class HsiBrgHandler
{

    DataStruct d_previous;

public:

    HsiBrgHandler() = default;

    void setupData(HANDLE simConnectHandle);

    [[nodiscard]] QByteArray processData(unsigned long *raw);

    QByteArray reset()
    {
        d_previous = DataStruct();

        return sendCurrentData();
    }

    [[nodiscard]] QByteArray sendCurrentData();
};

}  // namespace hsibrg

#endif  // __HSIBRGHANDLER_HPP__
