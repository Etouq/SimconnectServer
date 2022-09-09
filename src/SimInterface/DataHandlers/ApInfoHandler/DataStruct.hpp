#ifndef __APINFO_DATASTRUCT_HPP__
#define __APINFO_DATASTRUCT_HPP__

#include <cmath>
#include <cstdint>

namespace apinfo
{

struct RawStruct
{
    float refMach = 0.0;

    uint32_t apMaster = 0;
    uint32_t apYawDamper = 0;

    uint32_t apPitchHold = 0;
    uint32_t apFlc = 0;
    uint32_t apManagedInMach = 0;
    uint32_t apMachHold = 0;
    uint32_t apAltitudeLock = 0;
    uint32_t apVerticalHold = 0;
    uint32_t apGlideslopeActive = 0;

    uint32_t apAltitudeArm = 0;
    uint32_t apGlideslopeArm = 0;

    uint32_t apWingLeveler = 0;
    uint32_t apBankHold = 0;
    uint32_t apHeadingLock = 0;
    uint32_t apNav1Lock = 0;
    uint32_t apBackcourseHold = 0;
    uint32_t autopilotApproachHold = 0;

    uint32_t refSpeed = 0;
    uint32_t refAltitude = 0;
    uint32_t refVspeed = 0;

    uint32_t gpsDrivesNav1 = 0;
    uint32_t autopilotNavSelected = 0;
    uint32_t nav1HasLoc = 0;
    uint32_t nav2HasLoc = 0;
};

struct DataStruct
{
    bool apMaster = false;
    bool apYawDamper = false;

    bool apPitchHold = false;
    bool apFlc = false;
    bool apManagedInMach = false;
    bool apMachHold = false;
    bool apAltitudeLock = false;
    bool apVerticalHold = false;
    bool apGlideslopeActive = false;

    bool apAltitudeArm = false;
    bool apGlideslopeArm = false;

    bool apWingLeveler = false;
    bool apBankHold = false;
    bool apHeadingLock = false;
    bool apNav1Lock = false;
    bool apBackcourseHold = false;
    bool autopilotApproachHold = false;

    uint32_t refSpeed = 0;
    float refMach = 0.0;
    uint32_t refAltitude = 0;
    uint32_t refVspeed = 0;

    bool gpsDrivesNav1 = false;
    uint32_t autopilotNavSelected = 0;
    bool nav1HasLoc = false;
    bool nav2HasLoc = false;

    DataStruct() = default;

    DataStruct(RawStruct *data)
      : apMaster(data->apMaster != 0),
        apYawDamper(data->apYawDamper != 0),

        apPitchHold(data->apPitchHold != 0),
        apFlc(data->apFlc != 0),
        apManagedInMach(data->apManagedInMach != 0),
        apMachHold(data->apMachHold != 0),
        apAltitudeLock(data->apAltitudeLock != 0),
        apVerticalHold(data->apVerticalHold != 0),
        apGlideslopeActive(data->apGlideslopeActive != 0),

        apAltitudeArm(data->apAltitudeArm != 0),
        apGlideslopeArm(data->apGlideslopeArm != 0),

        apWingLeveler(data->apWingLeveler != 0),
        apBankHold(data->apBankHold != 0),
        apHeadingLock(data->apHeadingLock != 0),
        apNav1Lock(data->apNav1Lock != 0),
        apBackcourseHold(data->apBackcourseHold != 0),
        autopilotApproachHold(data->autopilotApproachHold != 0),

        refSpeed(data->refSpeed),
        refMach(data->refMach),
        refAltitude(data->refAltitude),
        refVspeed(data->refVspeed),

        gpsDrivesNav1(data->gpsDrivesNav1 != 0),
        autopilotNavSelected(data->autopilotNavSelected),
        nav1HasLoc(data->nav1HasLoc != 0),
        nav2HasLoc(data->nav2HasLoc != 0)
    {}
};

}  // namespace apinfo

#endif  // __APINFO_DATASTRUCT_HPP__
