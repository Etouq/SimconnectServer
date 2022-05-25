#include "pfdDataDefs.hpp"

#include <cmath>
using namespace std;


PfdAltimeterStruct::PfdAltimeterStruct(PfdAltimeterRawStruct *data)
{
    altitude = data->altitude;
    radarAltitude = data->radarAltitude;
    refAltitude = data->refAltitude;

    pressure = data->pressure;

    vspeed = data->vspeed;
    refVspeed = data->refVspeed;

    gpsDrivesNav1 = data->gpsDrivesNav1 != 0;
    autopilotNavSelected = data->autopilotNavSelected;
    gpsApproachApproachType = data->gpsApproachApproachType;

    nav1HasGlideslope = data->nav1HasGlideslope != 0;
    nav2HasGlideslope = data->nav2HasGlideslope != 0;
    gpsApproachActive = data->gpsApproachActive != 0;

    nav1Gsi = data->nav1Gsi;
    nav2Gsi = data->nav2Gsi;
    gpsVertError = data->gpsVertError;
}

PfdAttitudeStruct::PfdAttitudeStruct(PfdAttitudeRawStruct *data)
{
    angleOfAttack = data->angleOfAttack;
    bank = data->bank;
    pitch = data->pitch;
    slipskid = data->slipskid;
    fdBank = data->fdBank;
    fdPitch = data->fdPitch;
    fdState = data->fdState != 0;
}

PfdHsiStruct::PfdHsiStruct(PfdHsiRawStruct *data)
{
    rotation = data->rotation;
    heading = data->heading;
    turnRate = data->turnRate;
    currentTrack = data->currentTrack;
    gpsWpDesiredTrack = data->gpsWpDesiredTrack;

    currLat = data->currLat;
    currLon = data->currLon;

    gpsWpCrossTrack = data->gpsWpCrossTrack;
    trueHeading = data->trueHeading;

    autopilotNavSelected = data->autopilotNavSelected;
    gpsApproachApproachType = data->gpsApproachApproachType;
    gpsDrivesNav1 = data->gpsDrivesNav1 != 0;
    autopilotApproachHold = data->autopilotApproachHold != 0;

    nav1HasNav = data->nav1HasNav != 0;
    nav1HasLoc = data->nav1HasLoc != 0;
    nav1ToFrom = data->nav1ToFrom;
    nav1Loc = data->nav1Loc;
    nav1Cdi = data->nav1Cdi;
    nav1Obs = data->nav1Obs;

    nav2HasNav = data->nav2HasNav != 0;
    nav2HasLoc = data->nav2HasLoc != 0;
    nav2ToFrom = data->nav2ToFrom;
    nav2Loc = data->nav2Loc;
    nav2Cdi = data->nav2Cdi;
    nav2Obs = data->nav2Obs;
}

PfdHsiBrgStruct::PfdHsiBrgStruct(PfdHsiBrgRawStruct *data)
{
    nav1Dme = data->nav1Dme;
    nav1Radial = data->nav1Radial;
    nav1HasNav = data->nav1HasNav != 0;
    nav1HasSignal = data->nav1HasSignal != 0;
    nav1HasDme = data->nav1HasDme != 0;

    nav2Dme = data->nav2Dme;
    nav2Radial = data->nav2Radial;
    nav2HasNav = data->nav2HasNav != 0;
    nav2HasSignal = data->nav2HasSignal != 0;
    nav2HasDme = data->nav2HasDme != 0;

    gpsNextWpDist = data->gpsNextWpDist;
    gpsNextWpBearing = fmod(360.0 + fmod(data->gpsNextWpBearing, 360.0), 360.0);

    adfActiveFreq = data->adfActiveFreq;
    adfRadial = data->adfRadial + data->rotation;
    adfHasSignal = data->adfHasSignal != 0;
    if (adfRadial > 360.0)
        adfRadial -= 360.0;
}

PfdNavInfoStruct::PfdNavInfoStruct(PfdNavInfoRawStruct *data)
{
    gpsIsActiveFlightplan = data->gpsIsActiveFlightplan != 0;
    gpsIsDirectto = data->gpsIsDirectto != 0;

    gpsWpEte = data->gpsWpEte;
    gpsEte = data->gpsEte;
}

PfdWindStruct::PfdWindStruct(PfdWindRawStruct *data)
{
    windVelocity = data->ambientWindVelocity;
    windTrueDirection = data->ambientWindDirection;
    windDirection
      = fmod(360.0 + fmod(data->ambientWindDirection + 180.0 - data->rotation, 360.0), 360.0);
}

PfdApInfoStruct::PfdApInfoStruct(PfdApInfoRawStruct *data)
{
    apMaster = data->apMaster != 0;
    apYawDamper = data->apYawDamper != 0;

    apPitchHold = data->apPitchHold != 0;
    apFlc = data->apFlc != 0;
    apAltitudeLock = data->apAltitudeLock != 0;
    apVerticalHold = data->apVerticalHold != 0;
    apGlideslopeActive = data->apGlideslopeActive != 0;

    apAltitudeArm = data->apAltitudeArm != 0;
    apGlideslopeArm = data->apGlideslopeArm != 0;

    apWingLeveler = data->apWingLeveler != 0;
    apBankHold = data->apBankHold != 0;
    apHeadingLock = data->apHeadingLock != 0;
    apNav1Lock = data->apNav1Lock != 0;
    apBackcourseHold = data->apBackcourseHold != 0;
    autopilotApproachHold = data->autopilotApproachHold != 0;

    refSpeed = data->refSpeed;
    refAltitude = data->refAltitude;
    refVspeed = data->refVspeed;

    gpsDrivesNav1 = data->gpsDrivesNav1 != 0;
    autopilotNavSelected = data->autopilotNavSelected;
    nav1HasLoc = data->nav1HasLoc != 0;
    nav2HasLoc = data->nav2HasLoc != 0;
}

const vector<dataDef> pfdAirspeedDefs
  = { { "AIRSPEED INDICATED", "knots", SIMCONNECT_DATATYPE_FLOAT64, 0.01f },
      { "AIRSPEED BARBER POLE", "knots", SIMCONNECT_DATATYPE_FLOAT64, 0.09f },

      { "AIRSPEED TRUE", "knots", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "AUTOPILOT AIRSPEED HOLD VAR", "knots", SIMCONNECT_DATATYPE_INT32, 0.0f } };

const vector<dataDef> pfdAltimeterDefs
  = { { "INDICATED ALTITUDE", "feet", SIMCONNECT_DATATYPE_FLOAT64, 0.09f },
      { "RADIO HEIGHT", "feet", SIMCONNECT_DATATYPE_FLOAT64, 0.09f },

      { "KOHLSMAN SETTING HG:1", "inches of mercury", SIMCONNECT_DATATYPE_FLOAT64, 0.009f },

      { "VERTICAL SPEED", "feet per minute", SIMCONNECT_DATATYPE_FLOAT64, 0.09f },

      { "NAV GSI:1", "number", SIMCONNECT_DATATYPE_FLOAT64, 0.1f },   // look into replacing with nav glide slope error
      { "NAV GSI:2", "number", SIMCONNECT_DATATYPE_FLOAT64, 0.1f },
      { "GPS VERTICAL ERROR", "meters", SIMCONNECT_DATATYPE_FLOAT64, 0.1f },

      { "AUTOPILOT ALTITUDE LOCK VAR", "feet", SIMCONNECT_DATATYPE_INT32, 0.0f },

      { "AUTOPILOT VERTICAL HOLD VAR", "feet per minute", SIMCONNECT_DATATYPE_INT32, 0.0f },

      { "GPS DRIVES NAV1", "Bool", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "AUTOPILOT NAV SELECTED", "Number", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "GPS APPROACH APPROACH TYPE", "Enum", SIMCONNECT_DATATYPE_INT32, 0.0f },

      { "NAV HAS GLIDE SLOPE:1", "Bool", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "NAV HAS GLIDE SLOPE:2", "Bool", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "GPS IS APPROACH ACTIVE", "Bool", SIMCONNECT_DATATYPE_INT32, 0.0f } };

const vector<dataDef> pfdAttitudeDefs
  = { { "ANGLE OF ATTACK INDICATOR", "Degrees", SIMCONNECT_DATATYPE_FLOAT64, 0.25f },   //{ "INCIDENCE ALPHA", "Degrees", SIMCONNECT_DATATYPE_FLOAT64, 0.25 },

      { "ATTITUDE INDICATOR BANK DEGREES", "Degrees", SIMCONNECT_DATATYPE_FLOAT64, 0.0001f },
      { "ATTITUDE INDICATOR PITCH DEGREES", "Degrees", SIMCONNECT_DATATYPE_FLOAT64, 0.0001f },
      { "TURN COORDINATOR BALL", "position", SIMCONNECT_DATATYPE_FLOAT64, 0.0001f },

      { "AUTOPILOT FLIGHT DIRECTOR BANK", "Degrees", SIMCONNECT_DATATYPE_FLOAT64, 0.09f },
      { "AUTOPILOT FLIGHT DIRECTOR PITCH", "Degrees", SIMCONNECT_DATATYPE_FLOAT64, 0.09f },
      { "AUTOPILOT FLIGHT DIRECTOR ACTIVE", "Bool", SIMCONNECT_DATATYPE_INT32, 0.0f } };

const vector<dataDef> pfdBottombarDefs
  = { { "ZULU TIME", "Seconds", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "LOCAL TIME", "Seconds", SIMCONNECT_DATATYPE_INT32, 0.0f },

      { "GPS GROUND SPEED", "knots", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "TOTAL AIR TEMPERATURE", "Celsius", SIMCONNECT_DATATYPE_FLOAT32, 0.25f } };

const vector<dataDef> pfdHsiDefs = {
    { "PLANE HEADING DEGREES MAGNETIC", "degree", SIMCONNECT_DATATYPE_FLOAT64, 0.0009f },
    { "AUTOPILOT HEADING LOCK DIR", "degree", SIMCONNECT_DATATYPE_FLOAT64, 0.0009f },
    { "TURN INDICATOR RATE", "degree per second", SIMCONNECT_DATATYPE_FLOAT64, 0.0009f },
    { "GPS GROUND MAGNETIC TRACK", "degrees", SIMCONNECT_DATATYPE_FLOAT64, 0.0009f },
    { "GPS WP DESIRED TRACK", "degree", SIMCONNECT_DATATYPE_FLOAT64, 0.0009f },

    { "GPS POSITION LAT", "degrees", SIMCONNECT_DATATYPE_FLOAT64, 0.0000001f },
    { "GPS POSITION LON", "degrees", SIMCONNECT_DATATYPE_FLOAT64, 0.0000001f },

    { "GPS WP CROSS TRK", "nautical mile", SIMCONNECT_DATATYPE_FLOAT64, 0.009f },
    { "PLANE HEADING DEGREES TRUE", "degree", SIMCONNECT_DATATYPE_FLOAT64, 0.0009f },

    { "NAV LOCALIZER:1", "degree", SIMCONNECT_DATATYPE_FLOAT64, 0.0009f },
    { "NAV CDI:1", "number", SIMCONNECT_DATATYPE_FLOAT64, 0.3f },
    { "NAV OBS:1", "degree", SIMCONNECT_DATATYPE_FLOAT64, 0.0009f },

    { "NAV LOCALIZER:2", "degree", SIMCONNECT_DATATYPE_FLOAT64, 0.0009f },
    { "NAV CDI:2", "number", SIMCONNECT_DATATYPE_FLOAT64, 0.3f },
    { "NAV OBS:2", "degree", SIMCONNECT_DATATYPE_FLOAT64, 0.0009f },

    { "AUTOPILOT NAV SELECTED", "Number", SIMCONNECT_DATATYPE_INT32, 0.0f },
    { "GPS APPROACH APPROACH TYPE", "Enum", SIMCONNECT_DATATYPE_INT32, 0.0f },
    { "GPS DRIVES NAV1", "Bool", SIMCONNECT_DATATYPE_INT32, 0.0f },
    { "AUTOPILOT APPROACH HOLD", "Boolean", SIMCONNECT_DATATYPE_INT32, 0.0f },

    { "NAV HAS NAV:1", "Bool", SIMCONNECT_DATATYPE_INT32, 0.0f },
    { "NAV HAS LOCALIZER:1", "Bool", SIMCONNECT_DATATYPE_INT32, 0.0f },
    { "NAV TOFROM:1", "Enum", SIMCONNECT_DATATYPE_INT32, 0.0f },

    { "NAV HAS NAV:2", "Bool", SIMCONNECT_DATATYPE_INT32, 0.0f },
    { "NAV HAS LOCALIZER:2", "Bool", SIMCONNECT_DATATYPE_INT32, 0.0f },
    { "NAV TOFROM:2", "Enum", SIMCONNECT_DATATYPE_INT32, 0.0f },
};

const vector<dataDef> pfdHsiBrgDefs
  = { { "NAV DME:1", "nautical miles", SIMCONNECT_DATATYPE_FLOAT64, 0.09f },
      { "NAV RADIAL:1", "degree", SIMCONNECT_DATATYPE_FLOAT64, 0.0009f },

      { "NAV DME:2", "nautical miles", SIMCONNECT_DATATYPE_FLOAT64, 0.09f },
      { "NAV RADIAL:2", "degree", SIMCONNECT_DATATYPE_FLOAT64, 0.0009f },

      { "GPS WP DISTANCE", "nautical miles", SIMCONNECT_DATATYPE_FLOAT64, 0.09f },
      { "GPS WP BEARING", "degree", SIMCONNECT_DATATYPE_FLOAT64, 0.0009f },

      { "ADF ACTIVE FREQUENCY:1", "KHz", SIMCONNECT_DATATYPE_FLOAT64, 0.09f },
      { "ADF RADIAL:1", "degree", SIMCONNECT_DATATYPE_FLOAT64, 0.0009f },
      { "PLANE HEADING DEGREES MAGNETIC", "degree", SIMCONNECT_DATATYPE_FLOAT64, 0.0009f },

      { "NAV HAS NAV:1", "Bool", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "NAV SIGNAL:1", "number", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "NAV HAS DME:1", "Bool", SIMCONNECT_DATATYPE_INT32, 0.0f },

      { "NAV HAS NAV:2", "Bool", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "NAV SIGNAL:2", "number", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "NAV HAS DME:2", "Bool", SIMCONNECT_DATATYPE_INT32, 0.0f },

      { "ADF SIGNAL:1", "number", SIMCONNECT_DATATYPE_INT32, 0.0f } };

const vector<dataDef> pfdRadioDefs
  = { { "COM ACTIVE FREQUENCY:1", "MHz", SIMCONNECT_DATATYPE_FLOAT32, 0.001f },
      { "COM ACTIVE FREQUENCY:2", "MHz", SIMCONNECT_DATATYPE_FLOAT32, 0.001f },

      { "NAV ACTIVE FREQUENCY:1", "MHz", SIMCONNECT_DATATYPE_FLOAT32, 0.01f },
      { "NAV ACTIVE FREQUENCY:2", "MHz", SIMCONNECT_DATATYPE_FLOAT32, 0.01f },

      { "COM STANDBY FREQUENCY:1", "MHz", SIMCONNECT_DATATYPE_FLOAT32, 0.001f },
      { "COM STANDBY FREQUENCY:2", "MHz", SIMCONNECT_DATATYPE_FLOAT32, 0.001f },

      { "NAV STANDBY FREQUENCY:1", "MHz", SIMCONNECT_DATATYPE_FLOAT32, 0.01f },
      { "NAV STANDBY FREQUENCY:2", "MHz", SIMCONNECT_DATATYPE_FLOAT32, 0.01f },

      { "TRANSPONDER CODE:1", "number", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "TRANSPONDER STATE:1", "number", SIMCONNECT_DATATYPE_INT32, 0.0f } };

const vector<dataDef> pfdNavInfoDefs
  = { { "GPS IS ACTIVE FLIGHT PLAN", "Bool", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "GPS IS DIRECTTO FLIGHTPLAN", "Bool", SIMCONNECT_DATATYPE_INT32, 0.0f },

      { "GPS WP ETE", "Seconds", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "GPS ETE", "Seconds", SIMCONNECT_DATATYPE_INT32, 0.0f } };

const vector<dataDef> pfdWindDefs
  = { { "PLANE HEADING DEGREES MAGNETIC", "degree", SIMCONNECT_DATATYPE_FLOAT64, 0.05f },
      { "AMBIENT WIND VELOCITY", "knots", SIMCONNECT_DATATYPE_FLOAT64, 0.05f },
      { "AMBIENT WIND DIRECTION", "degree", SIMCONNECT_DATATYPE_FLOAT64, 0.05f } };

const vector<dataDef> pfdApInfoDefs
  = { { "AUTOPILOT MASTER", "Bool", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "AUTOPILOT YAW DAMPER", "Bool", SIMCONNECT_DATATYPE_INT32, 0.0f },

      { "AUTOPILOT PITCH HOLD", "Boolean", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "AUTOPILOT FLIGHT LEVEL CHANGE", "Bool", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "AUTOPILOT ALTITUDE LOCK", "Boolean", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "AUTOPILOT VERTICAL HOLD", "Boolean", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "AUTOPILOT GLIDESLOPE ACTIVE", "Boolean", SIMCONNECT_DATATYPE_INT32, 0.0f },

      { "AUTOPILOT ALTITUDE ARM", "Boolean", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "AUTOPILOT GLIDESLOPE ARM", "Boolean", SIMCONNECT_DATATYPE_INT32, 0.0f },

      { "AUTOPILOT WING LEVELER", "Boolean", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "AUTOPILOT BANK HOLD", "Boolean", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "AUTOPILOT HEADING LOCK", "Boolean", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "AUTOPILOT NAV1 LOCK", "Boolean", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "AUTOPILOT BACKCOURSE HOLD", "Boolean", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "AUTOPILOT APPROACH HOLD", "Boolean", SIMCONNECT_DATATYPE_INT32, 0.0f },

      { "AUTOPILOT AIRSPEED HOLD VAR", "knots", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "AUTOPILOT ALTITUDE LOCK VAR", "feet", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "AUTOPILOT VERTICAL HOLD VAR", "feet per minute", SIMCONNECT_DATATYPE_INT32, 0.0f },

      { "GPS DRIVES NAV1", "Bool", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "AUTOPILOT NAV SELECTED", "Number", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "NAV HAS LOCALIZER:1", "Bool", SIMCONNECT_DATATYPE_INT32, 0.0f },
      { "NAV HAS LOCALIZER:2", "Bool", SIMCONNECT_DATATYPE_INT32, 0.0f } };
