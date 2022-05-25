#ifndef PFDDATADEFSH
#define PFDDATADEFSH

#include "sharedStructs.hpp"

struct PfdAirspeedStruct
{
    double airspeed = 0;
    double maxSpeed = 0;

    int32_t trueAirspeed = 0;
    int32_t refSpeed = 0;
};

struct PfdAltimeterRawStruct
{
    double altitude = 0;
    double radarAltitude = 0;

    double pressure = 29.92;

    double vspeed = 0;

    double nav1Gsi = 0;
    double nav2Gsi = 0;
    double gpsVertError = 0;

    int32_t refAltitude = 0;

    int32_t refVspeed = 0;

    int32_t gpsDrivesNav1 = 0;
    int32_t autopilotNavSelected = 0;
    int32_t gpsApproachApproachType = 0;

    int32_t nav1HasGlideslope = 0;
    int32_t nav2HasGlideslope = 0;
    int32_t gpsApproachActive = 0;
};

struct PfdAltimeterStruct
{
    double altitude = 0;
    double radarAltitude = 0;
    int32_t refAltitude = 0;

    double pressure = 29.92;

    double vspeed = 0;
    int32_t refVspeed = 0;

    bool gpsDrivesNav1 = false;
    int32_t autopilotNavSelected = 0;
    int32_t gpsApproachApproachType = 0;

    bool nav1HasGlideslope = false;
    bool nav2HasGlideslope = false;
    bool gpsApproachActive = false;

    double nav1Gsi = 0;
    double nav2Gsi = 0;
    double gpsVertError = 0;

    PfdAltimeterStruct() = default;
    PfdAltimeterStruct(PfdAltimeterRawStruct *data);
};

struct PfdAttitudeRawStruct   // also handles aoa
{
    double angleOfAttack = 0;

    double bank = 0;
    double pitch = 0;
    double slipskid = 0;

    double fdBank = 0;
    double fdPitch = 0;

    int32_t fdState = 0;
};

struct PfdAttitudeStruct   // also handles aoa
{
    double angleOfAttack = 0;

    double bank = 0;
    double pitch = 0;
    double slipskid = 0;

    bool fdState = false;
    double fdBank = 0;
    double fdPitch = 0;

    PfdAttitudeStruct() = default;
    PfdAttitudeStruct(PfdAttitudeRawStruct *data);
};

struct PfdBottombarStruct
{
    int32_t zuluSeconds = 0;
    int32_t localSeconds = 0;

    int32_t groundSpeed = 0;
    float totalAirTemp = 0;
};

struct PfdHsiRawStruct   // also handles position
{
    double rotation = 0;
    double heading = 0;
    double turnRate = 0;
    double currentTrack = 0;
    double gpsWpDesiredTrack = 0;

    double currLat = 0;
    double currLon = 0;

    double gpsWpCrossTrack = 0;
    double trueHeading = 0;

    double nav1Loc = 0;
    double nav1Cdi = 0;
    double nav1Obs = 0;

    double nav2Loc = 0;
    double nav2Cdi = 0;
    double nav2Obs = 0;

    int32_t autopilotNavSelected = 0;
    int32_t gpsApproachApproachType = 0;
    int32_t gpsDrivesNav1 = 0;
    int32_t autopilotApproachHold = 0;

    int32_t nav1HasNav = 0;
    int32_t nav1HasLoc = 0;
    int32_t nav1ToFrom = 0;

    int32_t nav2HasNav = 0;
    int32_t nav2HasLoc = 0;
    int32_t nav2ToFrom = 0;
};

struct PfdHsiStruct   // also handles position
{
    double rotation = 0;
    double heading = 0;
    double turnRate = 0;
    double currentTrack = 0;
    double gpsWpDesiredTrack = 0;

    double currLat = 0;
    double currLon = 0;

    double gpsWpCrossTrack = 0;
    double trueHeading = 0;

    int32_t autopilotNavSelected = 0;
    int32_t gpsApproachApproachType = 0;
    bool gpsDrivesNav1 = false;
    bool autopilotApproachHold = false;

    bool nav1HasNav = false;
    bool nav1HasLoc = false;
    int32_t nav1ToFrom = 0;
    double nav1Loc = 0;
    double nav1Cdi = 0;
    double nav1Obs = 0;

    bool nav2HasNav = false;
    bool nav2HasLoc = false;
    int32_t nav2ToFrom = 0;
    double nav2Loc = 0;
    double nav2Cdi = 0;
    double nav2Obs = 0;

    PfdHsiStruct() = default;
    PfdHsiStruct(PfdHsiRawStruct *data);
};

struct PfdHsiBrgRawStruct
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

struct PfdHsiBrgStruct
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

    PfdHsiBrgStruct() = default;
    PfdHsiBrgStruct(PfdHsiBrgRawStruct *data);
};

struct PfdRadioStruct
{
    float com1Freq = 0;
    float com2Freq = 0;

    float nav1Freq = 0;
    float nav2Freq = 0;

    float com1Stby = 0;
    float com2Stby = 0;

    float nav1Stby = 0;
    float nav2Stby = 0;

    int32_t xpdrCode = 0;
    int32_t xpdrState = 0;
};

struct PfdNavInfoRawStruct
{
    int32_t gpsIsActiveFlightplan = 0;
    int32_t gpsIsDirectto = 0;

    int32_t gpsWpEte = 0;
    int32_t gpsEte = 0;
};

struct PfdNavInfoStruct
{
    bool gpsIsActiveFlightplan = false;
    bool gpsIsDirectto = false;

    int32_t gpsWpEte = 0;
    int32_t gpsEte = 0;

    PfdNavInfoStruct() = default;
    PfdNavInfoStruct(PfdNavInfoRawStruct *data);
};

struct PfdWindRawStruct
{
    double rotation = 0;
    double ambientWindVelocity = 0;
    double ambientWindDirection = 0;
};

struct PfdWindStruct
{
    double windVelocity = 0;
    double windDirection = 0;
    double windTrueDirection = 0;

    PfdWindStruct() = default;
    PfdWindStruct(PfdWindRawStruct *data);
};

struct PfdApInfoRawStruct
{
    int32_t apMaster = 0;
    int32_t apYawDamper = 0;

    int32_t apPitchHold = 0;
    int32_t apFlc = 0;
    int32_t apAltitudeLock = 0;
    int32_t apVerticalHold = 0;
    int32_t apGlideslopeActive = 0;

    int32_t apAltitudeArm = 0;
    int32_t apGlideslopeArm = 0;

    int32_t apWingLeveler = 0;
    int32_t apBankHold = 0;
    int32_t apHeadingLock = 0;
    int32_t apNav1Lock = 0;
    int32_t apBackcourseHold = 0;
    int32_t autopilotApproachHold = 0;

    int32_t refSpeed = 0;
    int32_t refAltitude = 0;
    int32_t refVspeed = 0;

    int32_t gpsDrivesNav1 = 0;
    int32_t autopilotNavSelected = 0;
    int32_t nav1HasLoc = 0;
    int32_t nav2HasLoc = 0;
};

struct PfdApInfoStruct
{
    bool apMaster = false;
    bool apYawDamper = false;

    bool apPitchHold = false;
    bool apFlc = false;
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

    int32_t refSpeed = 0;
    int32_t refAltitude = 0;
    int32_t refVspeed = 0;

    bool gpsDrivesNav1 = false;
    int32_t autopilotNavSelected = 0;
    bool nav1HasLoc = false;
    bool nav2HasLoc = false;

    PfdApInfoStruct() = default;
    PfdApInfoStruct(PfdApInfoRawStruct *data);
};


extern const std::vector<dataDef> pfdAirspeedDefs;

extern const std::vector<dataDef> pfdAltimeterDefs;

extern const std::vector<dataDef> pfdAttitudeDefs;

extern const std::vector<dataDef> pfdBottombarDefs;

extern const std::vector<dataDef> pfdHsiDefs;

extern const std::vector<dataDef> pfdHsiBrgDefs;

extern const std::vector<dataDef> pfdRadioDefs;

extern const std::vector<dataDef> pfdNavInfoDefs;

extern const std::vector<dataDef> pfdWindDefs;

extern const std::vector<dataDef> pfdApInfoDefs;

#endif   // PFDDATADEFSH
