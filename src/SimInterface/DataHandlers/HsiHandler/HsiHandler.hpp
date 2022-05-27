#ifndef __HSIHANDLER_HPP__
#define __HSIHANDLER_HPP__

#include "common/dataIdentifiers.hpp"
#include "DataStruct.hpp"

#include <QByteArray>
#include <string>

typedef void *HANDLE;

namespace hsi
{

class HsiHandler
{

    bool d_displayDeviation = false;
    HsiNavSource d_navSource = HsiNavSource::NONE;
    double d_course = -5000.0;
    double d_courseDeviation = -5000.0;
    bool d_nextGpsWpIdValid = false;

    DataStruct d_previous;

public:

    HsiHandler() = default;

    void gpsWpNextIdValid(bool valid)
    {
        d_nextGpsWpIdValid = valid;
    }

    void setupData(HANDLE simConnectHandle);

    [[nodiscard]] QByteArray processData(unsigned long *raw);

    QByteArray reset()
    {
        d_previous = DataStruct();

        d_displayDeviation = false;
        d_navSource = HsiNavSource::NONE;
        d_course = -5000.0;
        d_courseDeviation = -5000.0;
        d_nextGpsWpIdValid = false;

        return sendCurrentData();
    }

    [[nodiscard]] QByteArray sendCurrentData();

private:

    void handleNav1Tacan(QByteArray &dataToSend, const DataStruct &newData);
    void handleNav2Tacan(QByteArray &dataToSend, const DataStruct &newData);

    void handleNav1(QByteArray &dataToSend, const DataStruct &newData);
    void handleNav2(QByteArray &dataToSend, const DataStruct &newData);

    void handleGps(QByteArray &dataToSend, const DataStruct &newData);
};

}  // namespace hsi

#endif  // __HSIHANDLER_HPP__
