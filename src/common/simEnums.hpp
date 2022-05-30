#ifndef __SIM_ENUMS_HPP__
#define __SIM_ENUMS_HPP__

#include <cstdint>

enum ApproachType : uint32_t
{
    NONE = 0,
    GPS = 1,
    VOR = 2,
    NDB = 3,
    ILS = 4,
    LOCALIZER = 5,
    SDF = 6,
    LDA = 7,
    VOR_DME = 8,
    NDB_DME = 9,
    RNAV = 10,
    BACKCOURSE = 11
};


enum TransponderState : uint32_t
{
    OFF = 0,
    STANDBY = 1,
    TEST = 2,
    ON = 3,
    ALT = 4,
    GROUND = 5
};

#endif  // __SIM_ENUMS_HPP__