#ifndef __RADIOHANDLER_HPP__
#define __RADIOHANDLER_HPP__

#include "DataStruct.hpp"

#include <QByteArray>

typedef void *HANDLE;

namespace radio
{

class RadioHandler
{

    DataStruct d_previous;

public:

    RadioHandler() = default;

    void setupData(HANDLE simConnectHandle);

    [[nodiscard]] QByteArray processData(unsigned long *raw);

    QByteArray reset()
    {
        d_previous = DataStruct();

        return sendCurrentData();
    }

    [[nodiscard]] QByteArray sendCurrentData();
};

}  // namespace radio

#endif  // __RADIOHANDLER_HPP__
