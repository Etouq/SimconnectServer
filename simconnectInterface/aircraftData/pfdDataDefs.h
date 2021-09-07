#ifndef PFDDATADEFS_H
#define PFDDATADEFS_H

#include "sharedStructs.h"

struct PfdAirspeedStruct
{
    double airspeed = 0;
    double max_speed = 0;

    int32_t true_airspeed = 0;
    int32_t ref_speed = 0;
};

struct PfdAltimeterRawStruct
{
    double altitude = 0;
    double radar_altitude = 0;

    double pressure = 29.92;

    double vspeed = 0;

    double nav1_gsi = 0;
    double nav2_gsi = 0;
    double gps_vert_error = 0;

    int32_t ref_altitude = 0;

    int32_t ref_vspeed = 0;

    int32_t gpsDrivesNav1 = 0;
    int32_t autopilot_nav_selected = 0;
    int32_t gps_approach_approach_type = 0;

    int32_t nav1_has_glideslope = 0;
    int32_t nav2_has_glideslope = 0;
    int32_t gps_approach_active = 0;
};

struct PfdAltimeterStruct
{
    double altitude = 0;
    double radar_altitude = 0;
    int32_t ref_altitude = 0;

    double pressure = 29.92;

    double vspeed = 0;
    int32_t ref_vspeed = 0;

    bool gpsDrivesNav1 = false;
    int32_t autopilot_nav_selected = 0;
    int32_t gps_approach_approach_type = 0;

    bool nav1_has_glideslope = false;
    bool nav2_has_glideslope = false;
    bool gps_approach_active = false;

    double nav1_gsi = 0;
    double nav2_gsi = 0;
    double gps_vert_error = 0;

    PfdAltimeterStruct() = default;
    PfdAltimeterStruct(PfdAltimeterRawStruct *data);
};

struct PfdAttitudeRawStruct // also handles aoa
{
    double angle_of_attack = 0;

    double bank = 0;
    double pitch = 0;
    double slipskid = 0;

    double fd_bank = 0;
    double fd_pitch = 0;

    int32_t fd_state = 0;
};

struct PfdAttitudeStruct // also handles aoa
{
    double angle_of_attack = 0;

    double bank = 0;
    double pitch = 0;
    double slipskid = 0;

    bool fd_state = false;
    double fd_bank = 0;
    double fd_pitch = 0;

    PfdAttitudeStruct() = default;
    PfdAttitudeStruct(PfdAttitudeRawStruct *data);
};

struct PfdBottombarStruct
{
    int32_t zulu_seconds = 0;
    int32_t local_seconds = 0;

    int32_t ground_speed = 0;
    float total_air_temp = 0;
};

struct PfdHsiRawStruct // also handles position
{
    double rotation = 0;
    double heading = 0;
    double turn_rate = 0;
    double current_track = 0;
    double gps_wp_desired_track = 0;

    double currLat = 0;
    double currLon = 0;

    double gps_wp_cross_track = 0;
    double true_heading = 0;

    double nav1_loc = 0;
    double nav1_cdi = 0;
    double nav1_obs = 0;

    double nav2_loc = 0;
    double nav2_cdi = 0;
    double nav2_obs = 0;

    int32_t autopilot_nav_selected = 0;
    int32_t gps_approach_approach_type = 0;
    int32_t gpsDrivesNav1 = 0;
    int32_t autopilot_approach_hold = 0;

    int32_t nav1_has_nav = 0;
    int32_t nav1_has_loc = 0;
    int32_t nav1_to_from = 0;

    int32_t nav2_has_nav = 0;
    int32_t nav2_has_loc = 0;
    int32_t nav2_to_from = 0;
};

struct PfdHsiStruct // also handles position
{
    double rotation = 0;
    double heading = 0;
    double turn_rate = 0;
    double current_track = 0;
    double gps_wp_desired_track = 0;

    double currLat = 0;
    double currLon = 0;

    double gps_wp_cross_track = 0;
    double true_heading = 0;

    int32_t autopilot_nav_selected = 0;
    int32_t gps_approach_approach_type = 0;
    bool gpsDrivesNav1 = false;
    bool autopilot_approach_hold = false;

    bool nav1_has_nav = false;
    bool nav1_has_loc = false;
    int32_t nav1_to_from = 0;
    double nav1_loc = 0;
    double nav1_cdi = 0;
    double nav1_obs = 0;

    bool nav2_has_nav = false;
    bool nav2_has_loc = false;
    int32_t nav2_to_from = 0;
    double nav2_loc = 0;
    double nav2_cdi = 0;
    double nav2_obs = 0;

    PfdHsiStruct() = default;
    PfdHsiStruct(PfdHsiRawStruct *data);
};

struct PfdHsiBrgRawStruct
{
    double nav1_dme = 0;
    double nav1_radial = 0;

    double nav2_dme = 0;
    double nav2_radial = 0;

    double gps_next_wp_dist = 0;
    double gps_next_wp_bearing = 0;

    double adf_active_freq = 0;
    double adf_radial = 0;
    double rotation = 0;

    int32_t nav1_has_nav = 0;
    int32_t nav1_has_signal = 0;
    int32_t nav1_has_dme = 0;

    int32_t nav2_has_nav = 0;
    int32_t nav2_has_signal = 0;
    int32_t nav2_has_dme = 0;

    int32_t adf_has_signal = 0;
};

struct PfdHsiBrgStruct
{
    double nav1_dme = 0;
    double nav1_radial = 0;
    bool nav1_has_nav = false;
    bool nav1_has_signal = false;
    bool nav1_has_dme = false;

    double nav2_dme = 0;
    double nav2_radial = 0;
    bool nav2_has_nav = false;
    bool nav2_has_signal = false;
    bool nav2_has_dme = false;

    double gps_next_wp_dist = 0;
    double gps_next_wp_bearing = 0;

    double adf_active_freq = 0;
    double adf_radial = 0;
    bool adf_has_signal = false;

    PfdHsiBrgStruct() = default;
    PfdHsiBrgStruct(PfdHsiBrgRawStruct *data);
};

struct PfdRadioStruct
{
    float com1_freq = 0;
    float com2_freq = 0;

    float nav1_freq = 0;
    float nav2_freq = 0;

    float com1_stby = 0;
    float com2_stby = 0;

    float nav1_stby = 0;
    float nav2_stby = 0;

    int32_t xpdr_code = 0;
    int32_t xpdr_state = 0;
};

struct PfdNavInfoRawStruct
{
    int32_t gps_is_active_flightplan = 0;
    int32_t gps_is_directto = 0;

    int32_t gps_wp_ete = 0;
    int32_t gps_ete = 0;
};

struct PfdNavInfoStruct
{
    bool gps_is_active_flightplan = false;
    bool gps_is_directto = false;

    int32_t gps_wp_ete = 0;
    int32_t gps_ete = 0;

    PfdNavInfoStruct() = default;
    PfdNavInfoStruct(PfdNavInfoRawStruct *data);
};

struct PfdWindRawStruct
{
    double rotation = 0;
    double ambient_wind_velocity = 0;
    double ambient_wind_direction = 0;
};

struct PfdWindStruct
{
    double wind_velocity = 0;
    double wind_direction = 0;
    double wind_true_direction = 0;

    PfdWindStruct() = default;
    PfdWindStruct(PfdWindRawStruct *data);
};

struct PfdApInfoRawStruct
{
    int32_t ap_master = 0;
    int32_t ap_yaw_damper = 0;

    int32_t ap_pitch_hold = 0;
    int32_t ap_flc = 0;
    int32_t ap_altitude_lock = 0;
    int32_t ap_vertical_hold = 0;
    int32_t ap_glideslope_active = 0;

    int32_t ap_altitude_arm = 0;
    int32_t ap_glideslope_arm = 0;

    int32_t ap_wing_leveler = 0;
    int32_t ap_bank_hold = 0;
    int32_t ap_heading_lock = 0;
    int32_t ap_nav1_lock = 0;
    int32_t ap_backcourse_hold = 0;
    int32_t autopilot_approach_hold = 0;

    int32_t ref_speed = 0;
    int32_t ref_altitude = 0;
    int32_t ref_vspeed = 0;

    int32_t gpsDrivesNav1 = 0;
    int32_t autopilot_nav_selected = 0;
    int32_t nav1_has_loc = 0;
    int32_t nav2_has_loc = 0;
};

struct PfdApInfoStruct
{
    bool ap_master = false;
    bool ap_yaw_damper = false;

    bool ap_pitch_hold = false;
    bool ap_flc = false;
    bool ap_altitude_lock = false;
    bool ap_vertical_hold = false;
    bool ap_glideslope_active = false;

    bool ap_altitude_arm = false;
    bool ap_glideslope_arm = false;

    bool ap_wing_leveler = false;
    bool ap_bank_hold = false;
    bool ap_heading_lock = false;
    bool ap_nav1_lock = false;
    bool ap_backcourse_hold = false;
    bool autopilot_approach_hold = false;

    int32_t ref_speed = 0;
    int32_t ref_altitude = 0;
    int32_t ref_vspeed = 0;

    bool gpsDrivesNav1 = false;
    int32_t autopilot_nav_selected = 0;
    bool nav1_has_loc = false;
    bool nav2_has_loc = false;

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

#endif // PFDDATADEFS_H

