#include "pfdDataDefs.hpp"

#include <cmath>
using namespace std;


PfdAltimeterStruct::PfdAltimeterStruct(PfdAltimeterRawStruct *data)
{
    altitude = data->altitude;
    radar_altitude = data->radar_altitude;
    ref_altitude = data->ref_altitude;

    pressure = data->pressure;

    vspeed = data->vspeed;
    ref_vspeed = data->ref_vspeed;

    gpsDrivesNav1 = data->gpsDrivesNav1 != 0;
    autopilot_nav_selected = data->autopilot_nav_selected;
    gps_approach_approach_type = data->gps_approach_approach_type;

    nav1_has_glideslope = data->nav1_has_glideslope != 0;
    nav2_has_glideslope = data->nav2_has_glideslope != 0;
    gps_approach_active = data->gps_approach_active != 0;

    nav1_gsi = data->nav1_gsi;
    nav2_gsi = data->nav2_gsi;
    gps_vert_error = data->gps_vert_error;
}

PfdAttitudeStruct::PfdAttitudeStruct(PfdAttitudeRawStruct *data)
{
    angle_of_attack = data->angle_of_attack;
    bank = data->bank;
    pitch = data->pitch;
    slipskid = data->slipskid;
    fd_bank = data->fd_bank;
    fd_pitch = data->fd_pitch;
    fd_state = data->fd_state != 0;
}

PfdHsiStruct::PfdHsiStruct(PfdHsiRawStruct *data)
{
    rotation = data->rotation;
    heading = data->heading;
    turn_rate = data->turn_rate;
    current_track = data->current_track;
    gps_wp_desired_track = data->gps_wp_desired_track;

    currLat = data->currLat;
    currLon = data->currLon;

    gps_wp_cross_track = data->gps_wp_cross_track;
    true_heading = data->true_heading;

    autopilot_nav_selected = data->autopilot_nav_selected;
    gps_approach_approach_type = data->gps_approach_approach_type;
    gpsDrivesNav1 = data->gpsDrivesNav1 != 0;
    autopilot_approach_hold = data->autopilot_approach_hold != 0;

    nav1_has_nav = data->nav1_has_nav != 0;
    nav1_has_loc = data->nav1_has_loc != 0;
    nav1_to_from = data->nav1_to_from;
    nav1_loc = data->nav1_loc;
    nav1_cdi = data->nav1_cdi;
    nav1_obs = data->nav1_obs;

    nav2_has_nav = data->nav2_has_nav != 0;
    nav2_has_loc = data->nav2_has_loc != 0;
    nav2_to_from = data->nav2_to_from;
    nav2_loc = data->nav2_loc;
    nav2_cdi = data->nav2_cdi;
    nav2_obs = data->nav2_obs;
}

PfdHsiBrgStruct::PfdHsiBrgStruct(PfdHsiBrgRawStruct *data)
{
    nav1_dme = data->nav1_dme;
    nav1_radial = data->nav1_radial;
    nav1_has_nav = data->nav1_has_nav != 0;
    nav1_has_signal = data->nav1_has_signal != 0;
    nav1_has_dme = data->nav1_has_dme != 0;

    nav2_dme = data->nav2_dme;
    nav2_radial = data->nav2_radial;
    nav2_has_nav = data->nav2_has_nav != 0;
    nav2_has_signal = data->nav2_has_signal != 0;
    nav2_has_dme = data->nav2_has_dme != 0;

    gps_next_wp_dist = data->gps_next_wp_dist;
    gps_next_wp_bearing = fmod(360.0 + fmod(data->gps_next_wp_bearing, 360.0), 360.0);

    adf_active_freq = data->adf_active_freq;
    adf_radial = data->adf_radial + data->rotation;
    adf_has_signal = data->adf_has_signal != 0;
    if (adf_radial > 360.0)
        adf_radial -= 360.0;
}

PfdNavInfoStruct::PfdNavInfoStruct(PfdNavInfoRawStruct *data)
{
    gps_is_active_flightplan = data->gps_is_active_flightplan != 0;
    gps_is_directto = data->gps_is_directto != 0;

    gps_wp_ete = data->gps_wp_ete;
    gps_ete = data->gps_ete;
}

PfdWindStruct::PfdWindStruct(PfdWindRawStruct *data)
{
    wind_velocity = data->ambient_wind_velocity;
    wind_true_direction = data->ambient_wind_direction;
    wind_direction
      = fmod(360.0 + fmod(data->ambient_wind_direction + 180.0 - data->rotation, 360.0), 360.0);
}

PfdApInfoStruct::PfdApInfoStruct(PfdApInfoRawStruct *data)
{
    ap_master = data->ap_master != 0;
    ap_yaw_damper = data->ap_yaw_damper != 0;

    ap_pitch_hold = data->ap_pitch_hold != 0;
    ap_flc = data->ap_flc != 0;
    ap_altitude_lock = data->ap_altitude_lock != 0;
    ap_vertical_hold = data->ap_vertical_hold != 0;
    ap_glideslope_active = data->ap_glideslope_active != 0;

    ap_altitude_arm = data->ap_altitude_arm != 0;
    ap_glideslope_arm = data->ap_glideslope_arm != 0;

    ap_wing_leveler = data->ap_wing_leveler != 0;
    ap_bank_hold = data->ap_bank_hold != 0;
    ap_heading_lock = data->ap_heading_lock != 0;
    ap_nav1_lock = data->ap_nav1_lock != 0;
    ap_backcourse_hold = data->ap_backcourse_hold != 0;
    autopilot_approach_hold = data->autopilot_approach_hold != 0;

    ref_speed = data->ref_speed;
    ref_altitude = data->ref_altitude;
    ref_vspeed = data->ref_vspeed;

    gpsDrivesNav1 = data->gpsDrivesNav1 != 0;
    autopilot_nav_selected = data->autopilot_nav_selected;
    nav1_has_loc = data->nav1_has_loc != 0;
    nav2_has_loc = data->nav2_has_loc != 0;
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
