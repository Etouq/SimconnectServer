#ifndef __AIRCRAFT_HANDLER_HPP__
#define __AIRCRAFT_HANDLER_HPP__

#include "DataStruct.hpp"
#include "common/definitions/AircraftConfig.hpp"

#include <string>


typedef void *HANDLE;

namespace handler::aircraft
{

class AircraftHandler
{

public:

    void setupData(HANDLE simConnectHandle, const AircraftConfig &config);

    [[nodiscard]] std::string processData(const unsigned long *raw);

    std::string reset()
    {
        d_previous = DataStruct();

        d_fuelQtyEps = 10000;

        d_singleTank = false;
        d_fuelQtyByWeight = false;

        d_checkFlaps = true;
        d_checkSpoilers = true;
        d_flapsAngle = 0;
        d_spoilersPct = 0;

        d_checkElevTrim = true;
        d_checkRuddTrim = true;
        d_checkAilTrim = true;

        d_checkApu = false;

        return sendCurrentData();
    }

    [[nodiscard]] std::string sendCurrentData();

private:

    DataStruct d_previous;

    double d_fuelQtyEps = 10000;

    bool d_singleTank = false;
    bool d_fuelQtyByWeight = false;

    bool d_checkFlaps = true;
    bool d_checkSpoilers = true;
    double d_flapsAngle = 0;
    double d_spoilersPct = 0;

    bool d_checkElevTrim = true;
    bool d_checkRuddTrim = true;
    bool d_checkAilTrim = true;

    bool d_checkApu = false;
};

}  // namespace handler::aircraft


#endif  // __AIRCRAFT_HANDLER_HPP__