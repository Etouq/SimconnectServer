#ifndef __HSIHANDLER_HPP__
#define __HSIHANDLER_HPP__

#include "DataStruct.hpp"
#include "common/TypeEnums.hpp"

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

    std::string gpsWpNextIdValid(bool valid)
    {
        std::string ret;
        if (d_nextGpsWpIdValid != valid)
        {
            d_nextGpsWpIdValid = valid;
            if (d_navSource == HsiNavSource::GPS)
                handleGps(ret, d_previous);
        }

        return ret;
    }

    double latitude() const
    {
        return d_previous.currLat;
    }
    double longitude() const
    {
        return d_previous.currLon;
    }

    bool gpsDrivesNav1() const
    {
        return d_previous.gpsDrivesNav1;
    }

    int autopilotNavSelected() const
    {
        return d_previous.autopilotNavSelected;
    }

    void setupData(HANDLE simConnectHandle);

    [[nodiscard]] std::string processData(unsigned long *raw);

    std::string reset()
    {
        d_previous = DataStruct();

        d_displayDeviation = false;
        d_navSource = HsiNavSource::NONE;
        d_course = -5000.0;
        d_courseDeviation = -5000.0;
        d_nextGpsWpIdValid = false;

        return sendCurrentData();
    }

    [[nodiscard]] std::string sendCurrentData();

private:

    void handleNav1Tacan(std::string &dataToSend, const DataStruct &newData);
    void handleNav2Tacan(std::string &dataToSend, const DataStruct &newData);

    void handleNav1(std::string &dataToSend, const DataStruct &newData);
    void handleNav2(std::string &dataToSend, const DataStruct &newData);

    void handleGps(std::string &dataToSend, const DataStruct &newData);
};

}  // namespace hsi

#endif  // __HSIHANDLER_HPP__
