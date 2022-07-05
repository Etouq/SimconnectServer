#ifndef __ALTITUDEHANDLER_HPP__
#define __ALTITUDEHANDLER_HPP__

#include "common/dataIdentifiers.hpp"
#include "common/TypeEnums.hpp"
#include "DataStruct.hpp"

#include <QByteArray>


typedef void *HANDLE;

namespace altitude
{

class AltitudeHandler
{
    VerticalDeviationMode d_vertDevMode = VerticalDeviationMode::NONE;
    double d_deviation = 0.0;

    DataStruct d_previous;

public:

    AltitudeHandler() = default;

    void setupData(HANDLE simConnectHandle);

    [[nodiscard]] QByteArray processData(unsigned long *raw);

    QByteArray reset()
    {
        d_previous = DataStruct();

        d_vertDevMode = VerticalDeviationMode::NONE;
        d_deviation = 0.0;

        return sendCurrentData();
    }

    [[nodiscard]] QByteArray sendCurrentData();


private:

    void handleGps(QByteArray &dataToSend, const DataStruct &newData);
    void handleNav1(QByteArray &dataToSend, const DataStruct &newData);
    void handleNav2(QByteArray &dataToSend, const DataStruct &newData);
};

}  // namespace altitude

#endif  // __ALTITUDEHANDLER_HPP__
