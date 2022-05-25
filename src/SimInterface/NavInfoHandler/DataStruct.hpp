#ifndef __NAVINFO_DATASTRUCT_HPP__
#define __NAVINFO_DATASTRUCT_HPP__

#include <cstdint>

namespace navinfo
{

struct RawStruct
{
    int32_t gpsIsActiveFlightplan = 0;
    int32_t gpsIsDirectTo = 0;

    int32_t gpsWpEte = 0;
    int32_t gpsEte = 0;
};

struct DataStruct
{
    bool gpsIsActiveFlightplan = false;
    bool gpsIsDirectTo = false;

    int32_t gpsWpEte = 0;
    int32_t gpsEte = 0;

    DataStruct() = default;

    DataStruct(RawStruct *data)
      : gpsIsActiveFlightplan(data->gpsIsActiveFlightplan != 0),
        gpsIsDirectTo(data->gpsIsDirectTo != 0),

        gpsWpEte(data->gpsWpEte),
        gpsEte(data->gpsEte)
    {}
};

}  // namespace navinfo

#endif  // __NAVINFO_DATASTRUCT_HPP__