#ifndef __HSIBRG_DATASTRUCT_HPP__
#define __HSIBRG_DATASTRUCT_HPP__

#include <cmath>
#include <cstdint>


namespace hsibrg
{

struct RawStruct
{
    double nav1Dme = 0;
    double nav1Radial = 0;

    double nav2Dme = 0;
    double nav2Radial = 0;

    double gpsNextWpDist = 0;
    double gpsNextWpBearing = 0;

    double adfActiveFreq = 0;
    double adfRadial = 0;
    double rotation = 0;

    int32_t nav1HasNav = 0;
    int32_t nav1HasSignal = 0;
    int32_t nav1HasDme = 0;

    int32_t nav2HasNav = 0;
    int32_t nav2HasSignal = 0;
    int32_t nav2HasDme = 0;

    int32_t adfHasSignal = 0;
};

struct DataStruct
{
    double nav1Dme = 0;
    double nav1Radial = 0;
    bool nav1HasNav = false;
    bool nav1HasSignal = false;
    bool nav1HasDme = false;

    double nav2Dme = 0;
    double nav2Radial = 0;
    bool nav2HasNav = false;
    bool nav2HasSignal = false;
    bool nav2HasDme = false;

    double gpsNextWpDist = 0;
    double gpsNextWpBearing = 0;

    double adfActiveFreq = 0;
    double adfRadial = 0;
    bool adfHasSignal = false;

    DataStruct() = default;

    DataStruct(RawStruct *data)
      : nav1Dme(data->nav1Dme),
        nav1Radial(data->nav1Radial),
        nav1HasNav(data->nav1HasNav != 0),
        nav1HasSignal(data->nav1HasSignal > 0),
        nav1HasDme(data->nav1HasDme != 0),

        nav2Dme(data->nav2Dme),
        nav2Radial(data->nav2Radial),
        nav2HasNav(data->nav2HasNav != 0),
        nav2HasSignal(data->nav2HasSignal > 0),
        nav2HasDme(data->nav2HasDme != 0),

        gpsNextWpDist(data->gpsNextWpDist),
        gpsNextWpBearing(data->gpsNextWpBearing - 360.0 * std::floor(data->gpsNextWpBearing / 360.0)),

        adfActiveFreq(data->adfActiveFreq),
        adfHasSignal(data->adfHasSignal > 0)
    {
        const double radialSum = data->adfRadial + data->rotation;
        adfRadial = radialSum - 360.0 * std::floor(radialSum / 360.0);
    }
};

}  // namespace hsibrg

#endif  // __HSIBRG_DATASTRUCT_HPP__