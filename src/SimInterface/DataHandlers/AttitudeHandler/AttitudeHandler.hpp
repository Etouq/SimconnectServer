#ifndef __ATTITUDEHANDLER_HPP__
#define __ATTITUDEHANDLER_HPP__

#include "DataStruct.hpp"

#include <QByteArray>

typedef void *HANDLE;

namespace attitude
{

class AttitudeHandler
{

    DataStruct d_previous;

public:

    AttitudeHandler() = default;

    void setupData(HANDLE simConnectHandle);

    [[nodiscard]] QByteArray processData(unsigned long *raw);

    QByteArray reset()
    {
        d_previous = DataStruct();

        return sendCurrentData();
    }

    [[nodiscard]] QByteArray sendCurrentData();
};

}  // namespace attitude

#endif  // __ATTITUDEHANDLER_HPP__
