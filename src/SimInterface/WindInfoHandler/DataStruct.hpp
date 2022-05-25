#ifndef __WINDINFO_DATASTRUCT_HPP__
#define __WINDINFO_DATASTRUCT_HPP__

#include <cmath>
#include <cstdint>


namespace windinfo
{

struct RawStruct
{
    double rotation = 0;
    double ambientWindVelocity = 0;
    double ambientWindDirection = 0;
};

struct DataStruct
{
    double windVelocity = 0;
    double windDirection = 0;
    double windTrueDirection = 0;

    DataStruct() = default;

    DataStruct(RawStruct *data)
      : windVelocity(data->ambientWindVelocity),
        windTrueDirection(data->ambientWindDirection)
    {
        const double directionSum = data->ambientWindDirection + 180.0 - data->rotation;
        windDirection = directionSum - 360.0 * std::floor(directionSum / 360.0);
    }
};

}  // namespace windinfo

#endif  // __WINDINFO_DATASTRUCT_HPP__