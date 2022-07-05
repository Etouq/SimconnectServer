#ifndef __ALTIMETER_DATASTRUCT_HPP__
#define __ALTIMETER_DATASTRUCT_HPP__

#include <cstdint>
#include "common/simEnums.hpp"

namespace altitude
{

struct RawStruct
{
    double altitude = 0;
    double radarAltitude = 0;

    double pressure = 29.92;

    double vspeed = 0;

    double nav1Gsi = 0;
    double nav2Gsi = 0;
    double gpsVertError = 0;

    uint32_t refAltitude = 0;

    uint32_t refVspeed = 0;

    uint32_t gpsDrivesNav1 = 0;
    uint32_t autopilotNavSelected = 0;
    simenums::ApproachType gpsApproachApproachType = simenums::ApproachType::NONE;

    uint32_t nav1HasGlideslope = 0;
    uint32_t nav2HasGlideslope = 0;
    uint32_t gpsApproachActive = 0;
    uint32_t apApproachActive = 0;
};

struct DataStruct
{
    double altitude = 0;
    double radarAltitude = 0;
    uint32_t refAltitude = 0;

    double pressure = 29.92;

    double vspeed = 0;
    uint32_t refVspeed = 0;

    bool gpsDrivesNav1 = false;
    uint32_t autopilotNavSelected = 0;
    simenums::ApproachType gpsApproachApproachType = simenums::ApproachType::NONE;

    bool nav1HasGlideslope = false;
    bool nav2HasGlideslope = false;
    bool gpsApproachActive = false;
    bool apApproachActive = false;

    double nav1Gsi = 0;
    double nav2Gsi = 0;
    double gpsVertError = 0;

    DataStruct() = default;

    DataStruct(RawStruct *data)
      : altitude(data->altitude),
        radarAltitude(data->radarAltitude),
        refAltitude(data->refAltitude),

        pressure(data->pressure),

        vspeed(data->vspeed),
        refVspeed(data->refVspeed),

        gpsDrivesNav1(data->gpsDrivesNav1 != 0),
        autopilotNavSelected(data->autopilotNavSelected),
        gpsApproachApproachType(data->gpsApproachApproachType),

        nav1HasGlideslope(data->nav1HasGlideslope != 0),
        nav2HasGlideslope(data->nav2HasGlideslope != 0),
        gpsApproachActive(data->gpsApproachActive != 0),
        apApproachActive(data->apApproachActive != 0),

        nav1Gsi(data->nav1Gsi),
        nav2Gsi(data->nav2Gsi),
        gpsVertError(data->gpsVertError)
    {}
};

}  // namespace altitude

#endif  // __ALTIMETER_DATASTRUCT_HPP__