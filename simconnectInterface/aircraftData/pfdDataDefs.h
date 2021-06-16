#ifndef PFDDATADEFS_H
#define PFDDATADEFS_H

#include "sharedStructs.h"
#include <cmath>

struct PfdDataStruct
{
    double trueHeading = 0;
    double currLat = 0;
    double currLon = 0;
    double airspeed = 0;
    double max_speed = 0;
    double altitude = 0;
    double radar_altitude = 0;
    double pressure = 0;
    double vspeed = 0;
    double nav1_gsi = 0;
    double nav2_gsi = 0;
    double gps_vert_error = 0;
    double angle_of_attack = 0;
    double bank = 0;
    double pitch = 0;
    double slipskid = 0;
    double fd_bank = 0;
    double fd_pitch = 0;
    double rotation = 0;
    double heading = 0;
    double turn_rate = 0;
    double current_track = 0;
    double nav1_loc = 0;
    double nav1_obs = 0;
    double nav1_cdi = 0;
    double nav2_loc = 0;
    double nav2_obs = 0;
    double nav2_cdi = 0;
    double gps_wp_desired_track = 0;
    double gps_wp_cross_track = 0;
    double nav1_dme = 0;
    double nav1_radial = 0;
    double nav2_dme = 0;
    double nav2_radial = 0;
    double gps_next_wp_dist = 0;
    double gps_next_wp_bearing = 0;
    double adf_active_freq = 0;
    double adf_radial = 0;
    double com1_freq = 0;
    double com2_freq = 0;
    double nav1_freq = 0;
    double nav2_freq = 0;
    double ambient_wind_velocity = 0;
    double ambient_wind_direction = 0;
    int32_t zulu_seconds = 0;
    int32_t local_seconds = 0;
    int32_t gps_wp_ete = 0;
    int32_t gps_ete = 0;
    int32_t ap_flc = 0;
    int32_t gpsDrivesNav1 = 0;
    int32_t nav1_has_glideslope = 0;
    int32_t nav2_has_glideslope = 0;
    int32_t gps_approach_active = 0;
    int32_t fd_state = 0;
    int32_t autopilot_approach_hold = 0;
    int32_t nav1_has_nav = 0;
    int32_t nav1_has_loc = 0;
    int32_t nav2_has_nav = 0;
    int32_t nav2_has_loc = 0;
    int32_t nav1_has_dme = 0;
    int32_t nav2_has_dme = 0;
    int32_t adf_has_signal = 0;
    int32_t gps_is_active_flightplan = 0;
    int32_t gps_is_directto = 0;
    int32_t ap_master = 0;
    int32_t ap_yaw_damper = 0;
    int32_t ap_pitch_hold = 0;
    int32_t ap_altitude_lock = 0;
    int32_t ap_altitude_arm = 0;
    int32_t ap_vertical_hold = 0;
    int32_t ap_glideslope_active = 0;
    int32_t ap_glideslope_arm = 0;
    int32_t ap_wing_leveler = 0;
    int32_t ap_bank_hold = 0;
    int32_t ap_heading_lock = 0;
    int32_t ap_nav1_lock = 0;
    int32_t ap_backcourse_hold = 0;
    int32_t true_airspeed = 0;
    int32_t ref_speed = 0;
    int32_t ref_altitude = 0;
    int32_t ref_vspeed = 0;
    int32_t autopilot_nav_selected = 0;
    int32_t ground_speed = 0;
    float total_air_temp = 0;
    int32_t gps_approach_approach_type = 0;
    int32_t nav1_to_from = 0;
    int32_t nav2_to_from = 0;
    int32_t nav1_has_signal = 0;
    int32_t nav2_has_signal = 0;
};

struct PfdCleanDataStruct
{
    double true_heading = 0;
    double airspeed = 0;
    double max_speed = 0;
    double altitude = 0;
    double radar_altitude = 0;
    double pressure = 0;
    double vspeed = 0;
    double nav1_gsi = 0;
    double nav2_gsi = 0;
    double gps_vert_error = 0;
    double angle_of_attack = 0;
    double bank = 0;
    double pitch = 0;
    double slipskid = 0;
    double fd_bank = 0;
    double fd_pitch = 0;
    double rotation = 0;
    double heading = 0;
    double turn_rate = 0;
    double current_track = 0;
    double nav1_loc = 0;
    double nav1_obs = 0;
    double nav1_cdi = 0;
    double nav2_loc = 0;
    double nav2_obs = 0;
    double nav2_cdi = 0;
    double gps_wp_desired_track = 0;
    double gps_wp_cross_track = 0;
    double nav1_dme = 0;
    double nav1_radial = 0;
    double nav2_dme = 0;
    double nav2_radial = 0;
    double gps_next_wp_dist = 0;
    double gps_next_wp_bearing = 0;
    double adf_active_freq = 0;
    double adf_radial = 0;
    double com1_freq = 0;
    double com2_freq = 0;
    double nav1_freq = 0;
    double nav2_freq = 0;
    double wind_velocity = 0;
    double wind_direction = 0;
    double wind_true_direction = 0;
    double currLat = 0;
    double currLon = 0;
    int32_t zulu_seconds = 0;
    int32_t local_seconds = 0;
    int32_t gps_wp_ete = 0;
    int32_t gps_ete = 0;
    int32_t true_airspeed = 0;
    int32_t ref_speed = 0;
    int32_t ref_altitude = 0;
    int32_t ref_vspeed = 0;
    int32_t autopilot_nav_selected = 0;
    int32_t ground_speed = 0;
    float total_air_temp = 0;
    int32_t gps_approach_approach_type = 0;
    int32_t nav1_to_from = 0;
    int32_t nav2_to_from = 0;
    bool ap_flc = false;
    bool gpsDrivesNav1 = false;
    bool nav1_has_glideslope = false;
    bool nav2_has_glideslope = false;
    bool gps_approach_active = false;
    bool fd_state = false;
    bool autopilot_approach_hold = false;
    bool nav1_has_nav = false;
    bool nav1_has_loc = false;
    bool nav2_has_nav = false;
    bool nav2_has_loc = false;
    bool nav1_has_signal = false;
    bool nav2_has_signal = false;
    bool nav1_has_dme = false;
    bool nav2_has_dme = false;
    bool adf_has_signal = false;
    bool gps_is_active_flightplan = false;
    bool gps_is_directto = false;
    bool ap_master = false;
    bool ap_yaw_damper = false;
    bool ap_pitch_hold = false;
    bool ap_altitude_lock = false;
    bool ap_altitude_arm = false;
    bool ap_vertical_hold = false;
    bool ap_glideslope_active = false;
    bool ap_glideslope_arm = false;
    bool ap_wing_leveler = false;
    bool ap_bank_hold = false;
    bool ap_heading_lock = false;
    bool ap_nav1_lock = false;
    bool ap_backcourse_hold = false;


    PfdCleanDataStruct() {}

    PfdCleanDataStruct(PfdDataStruct *rhs)
    {
        //airspeed
        airspeed = rhs->airspeed;
        max_speed = rhs->max_speed;
        true_airspeed = rhs->true_airspeed;
        ref_speed = rhs->ref_speed;
        ap_flc = rhs->ap_flc != 0;

        //altimeter
        altitude = rhs->altitude;
        radar_altitude = rhs->radar_altitude;
        ref_altitude = rhs->ref_altitude;
        pressure = rhs->pressure;

        //vspeed
        vspeed = rhs->vspeed;
        ref_vspeed = rhs->ref_vspeed;

        //vert dev
        gpsDrivesNav1 = rhs->gpsDrivesNav1 != 0;
        autopilot_nav_selected = rhs->autopilot_nav_selected;
        nav1_has_glideslope = rhs->nav1_has_glideslope != 0;
        nav2_has_glideslope = rhs->nav2_has_glideslope != 0;
        gps_approach_active = rhs->gps_approach_active != 0;
        nav1_gsi = rhs->nav1_gsi;
        nav2_gsi = rhs->nav2_gsi;
        gps_vert_error = rhs->gps_vert_error;

        //aoa
        angle_of_attack = rhs->angle_of_attack;

        //attitude
        bank = rhs->bank;
        pitch = rhs->pitch;
        slipskid = rhs->slipskid;
        fd_state = rhs->fd_state != 0;
        fd_bank = rhs->fd_bank;
        fd_pitch = rhs->fd_pitch;

        //bottombar
        zulu_seconds = rhs->zulu_seconds;
        local_seconds = rhs->local_seconds;
        ground_speed = rhs->ground_speed;
        total_air_temp = rhs->total_air_temp;

        //hsi
        rotation = rhs->rotation;
        heading = rhs->heading;
        turn_rate = rhs->turn_rate;
        current_track = rhs->current_track;
        autopilot_approach_hold = rhs->autopilot_approach_hold != 0;
        gps_approach_approach_type = rhs->gps_approach_approach_type;
        nav1_has_nav = rhs->nav1_has_nav != 0;
        nav1_has_loc = rhs->nav1_has_loc != 0;
        nav1_loc = rhs->nav1_loc;
        nav1_obs = rhs->nav1_obs;
        nav1_cdi = rhs->nav1_cdi;
        nav1_to_from = rhs->nav1_to_from;
        nav2_has_nav = rhs->nav2_has_nav != 0;
        nav2_has_loc = rhs->nav2_has_loc != 0;
        nav2_loc = rhs->nav2_loc;
        nav2_obs = rhs->nav2_obs;
        nav2_cdi = rhs->nav2_cdi;
        nav2_to_from = rhs->nav2_to_from;
        gps_wp_desired_track = rhs->gps_wp_desired_track;
        gps_wp_cross_track = rhs->gps_wp_cross_track;
        nav1_has_signal = rhs->nav1_has_signal != 0;
        nav2_has_signal = rhs->nav2_has_signal != 0;
        nav1_has_dme = rhs->nav1_has_dme != 0;
        nav1_dme = rhs->nav1_dme;
        nav1_radial = rhs->nav1_radial;
        nav2_has_dme = rhs->nav2_has_dme != 0;
        nav2_dme = rhs->nav2_dme;
        nav2_radial = rhs->nav2_radial;
        gps_next_wp_dist = rhs->gps_next_wp_dist;
        gps_next_wp_bearing = rhs->gps_next_wp_bearing;
        adf_has_signal = rhs->adf_has_signal != 0;
        adf_active_freq = rhs->adf_active_freq;
        adf_radial = rhs->adf_radial + rotation;
        if (adf_radial > 360.0)
            adf_radial -= 360.0;

        true_heading = rhs->trueHeading;

        //radio
        com1_freq = rhs->com1_freq;
        com2_freq = rhs->com2_freq;
        nav1_freq = rhs->nav1_freq;
        nav2_freq = rhs->nav2_freq;

        //nav info
        gps_is_active_flightplan = rhs->gps_is_active_flightplan != 0;
        gps_is_directto = rhs->gps_is_directto != 0;

        //wind
        wind_velocity = rhs->ambient_wind_velocity;
        wind_true_direction = rhs->ambient_wind_direction;
        wind_direction = std::fmod(360.0 + std::fmod(rhs->ambient_wind_direction + 180.0 - rotation, 360.0), 360.0);

        gps_wp_ete = rhs->gps_wp_ete;
        gps_ete = rhs->gps_ete;

        currLat = rhs->currLat;
        currLon = rhs->currLon;

        //ap info
        ap_master = rhs->ap_master != 0;
        ap_yaw_damper = rhs->ap_yaw_damper != 0;
        ap_pitch_hold = rhs->ap_pitch_hold != 0;
        ap_altitude_lock = rhs->ap_altitude_lock != 0;
        ap_altitude_arm = rhs->ap_altitude_arm != 0;
        ap_vertical_hold = rhs->ap_vertical_hold != 0;
        ap_glideslope_active = rhs->ap_glideslope_active != 0;
        ap_glideslope_arm = rhs->ap_glideslope_arm != 0;
        ap_wing_leveler = rhs->ap_wing_leveler != 0;
        ap_bank_hold = rhs->ap_bank_hold != 0;
        ap_heading_lock = rhs->ap_heading_lock != 0;
        ap_nav1_lock = rhs->ap_nav1_lock != 0;
        ap_backcourse_hold = rhs->ap_backcourse_hold != 0;
    }
};


extern const std::vector<dataDef> pfdDataDefVector;

#endif // PFDDATADEFS_H
/*struct PfdDataStruct
{
    //airspeed
    double airspeed = 0;
    double max_speed = 0;
    int32_t true_airspeed = 0;
    int32_t ref_speed = 0;
    float ap_flc = 0;
    //altimeter
    double altitude = 0;
    double radar_altitude = 0;
    int32_t ref_altitude = 0;
    double pressure = 0;
    //vspeed
    double vspeed = 0;
    int32_t ref_vspeed = 0;
    //vert dev
    float gpsDrivesNav1 = 0;
    int32_t autopilot_nav_selected = 0;
    float nav1_has_glideslope = 0;
    float nav2_has_glideslope = 0;
    float gps_approach_active = 0;
    double nav1_gsi = 0;
    double nav2_gsi = 0;
    double gps_vert_error = 0;
    //aoa
    double angle_of_attack = 0;
    //attitude
    double bank = 0;
    double pitch = 0;
    double slipskid = 0;
    float fd_state = 0;
    double fd_bank = 0;
    double fd_pitch = 0;
    //bottombar
    int64_t zulu_seconds = 0;
    int64_t local_seconds = 0;
    int32_t ground_speed = 0;
    int32_t total_air_temp = 0;
    //hsi
    double rotation = 0;
    double heading = 0;
    double turn_rate = 0;
    double current_track = 0;
    float autopilot_approach_hold = 0;
    int32_t gps_approach_approach_type = 0;
    float nav1_has_nav = 0;
    float nav1_has_loc = 0;
    double nav1_loc = 0;
    double nav1_obs = 0;
    double nav1_cdi = 0;
    int32_t nav1_to_from = 0;
    float nav2_has_nav = 0;
    float nav2_has_loc = 0;
    double nav2_loc = 0;
    double nav2_obs = 0;
    double nav2_cdi = 0;
    int32_t nav2_to_from = 0;
    double gps_wp_desired_track = 0;
    double gps_wp_cross_track = 0;
    int32_t nav1_has_signal = 0;
    int32_t nav2_has_signal = 0;
    float nav1_has_dme = 0;
    double nav1_dme = 0;
    double nav1_radial = 0;
    float nav2_has_dme = 0;
    double nav2_dme = 0;
    double nav2_radial = 0;
    double gps_next_wp_dist = 0;
    double gps_next_wp_bearing = 0;
    float adf_has_signal = 0;
    double adf_active_freq = 0;
    double adf_radial = 0;
    double com1_freq = 0;
    double com2_freq = 0;
    double nav1_freq = 0;
    double nav2_freq = 0;
    //nav info
    float gps_is_active_flightplan = 0;
    float gps_is_directto = 0;
    //wind
    double ambient_wind_velocity = 0;
    double ambient_wind_direction = 0;
    //ap info
    float ap_master = 0;
    float ap_yaw_damper = 0;
    float ap_pitch_hold = 0;
    float ap_altitude_lock = 0;
    float ap_altitude_arm = 0;
    float ap_vertical_hold = 0;
    float ap_glideslope_active = 0;
    float ap_glideslope_arm = 0;
    float ap_wing_leveler = 0;
    float ap_bank_hold = 0;
    float ap_heading_lock = 0;
    float ap_nav1_lock = 0;
    float ap_backcourse_hold = 0;
};

struct PfdCleanDataStruct
{
    //airspeed
    double airspeed = 0;
    double max_speed = 0;
    int32_t true_airspeed = 0;
    int32_t ref_speed = 0;
    bool ap_flc = false;
    //altimeter
    double altitude = 0;
    double radar_altitude = 0;
    int32_t ref_altitude = 0;
    double pressure = 0;
    //vspeed
    double vspeed = 0;
    int32_t ref_vspeed = 0;
    //vert dev
    bool gpsDrivesNav1 = false;
    int32_t autopilot_nav_selected = 0;
    bool nav1_has_glideslope = false;
    bool nav2_has_glideslope = false;
    bool gps_approach_active = false;
    double nav1_gsi = 0;
    double nav2_gsi = 0;
    double gps_vert_error = 0;
    //aoa
    double angle_of_attack = 0;
    //attitude
    double bank = 0;
    double pitch = 0;
    double slipskid = 0;
    bool fd_state = false;
    double fd_bank = 0;
    double fd_pitch = 0;
    //bottombar
    int64_t zulu_seconds = 0;
    int64_t local_seconds = 0;
    int32_t ground_speed = 0;
    int32_t total_air_temp = 0;
    //hsi
    double rotation = 0;
    double heading = 0;
    double turn_rate = 0;
    double current_track = 0;
    bool autopilot_approach_hold = false;
    int32_t gps_approach_approach_type = 0;
    bool nav1_has_nav = false;
    bool nav1_has_loc = false;
    double nav1_loc = 0;
    double nav1_obs = 0;
    double nav1_cdi = 0;
    int32_t nav1_to_from = 0;
    bool nav2_has_nav = false;
    bool nav2_has_loc = false;
    double nav2_loc = 0;
    double nav2_obs = 0;
    double nav2_cdi = 0;
    int32_t nav2_to_from = 0;
    double gps_wp_desired_track = 0;
    double gps_wp_cross_track = 0;
    bool nav1_has_signal = false;
    bool nav2_has_signal = false;
    bool nav1_has_dme = false;
    double nav1_dme = 0;
    double nav1_radial = 0;
    bool nav2_has_dme = false;
    double nav2_dme = 0;
    double nav2_radial = 0;
    double gps_next_wp_dist = 0;
    double gps_next_wp_bearing = 0;
    bool adf_has_signal = false;
    double adf_active_freq = 0;
    double adf_radial = 0;
    double com1_freq = 0;
    double com2_freq = 0;
    double nav1_freq = 0;
    double nav2_freq = 0;
    //nav info
    bool gps_is_active_flightplan = false;
    bool gps_is_directto = false;
    //wind
    double wind_velocity = 0;
    double wind_direction = 0;
    int32_t wind_true_direction = 0;
    //ap info
    bool ap_master = false;
    bool ap_yaw_damper = false;
    bool ap_pitch_hold = false;
    bool ap_altitude_lock = false;
    bool ap_altitude_arm = false;
    bool ap_vertical_hold = false;
    bool ap_glideslope_active = false;
    bool ap_glideslope_arm = false;
    bool ap_wing_leveler = false;
    bool ap_bank_hold = false;
    bool ap_heading_lock = false;
    bool ap_nav1_lock = false;
    bool ap_backcourse_hold = false;

    PfdCleanDataStruct() {}

    PfdCleanDataStruct(PfdDataStruct *rhs)
    {
        //airspeed
        airspeed = rhs->airspeed;
        max_speed = rhs->max_speed;
        true_airspeed = rhs->true_airspeed;
        ref_speed = rhs->ref_speed;
        ap_flc = rhs->ap_flc > 0.1 || rhs->ap_flc < -0.1;

        //altimeter
        altitude = rhs->altitude;
        radar_altitude = rhs->radar_altitude;
        ref_altitude = rhs->ref_altitude;
        pressure = rhs->pressure;

        //vspeed
        vspeed = rhs->vspeed;
        ref_vspeed = rhs->ref_vspeed;

        //vert dev
        gpsDrivesNav1 = rhs->gpsDrivesNav1 > 0.1 || rhs->gpsDrivesNav1 < -0.1;
        autopilot_nav_selected = rhs->autopilot_nav_selected;
        nav1_has_glideslope = rhs->nav1_has_glideslope > 0.1 || rhs->nav1_has_glideslope < -0.1;
        nav2_has_glideslope = rhs->nav2_has_glideslope > 0.1 || rhs->nav2_has_glideslope < -0.1;
        gps_approach_active = rhs->gps_approach_active > 0.1 || rhs->gps_approach_active < -0.1;
        nav1_gsi = rhs->nav1_gsi;
        nav2_gsi = rhs->nav2_gsi;
        gps_vert_error = rhs->gps_vert_error;

        //aoa
        angle_of_attack = rhs->angle_of_attack;

        //attitude
        bank = rhs->bank;
        pitch = rhs->pitch;
        slipskid = rhs->slipskid;
        fd_state = rhs->fd_state > 0.1 || rhs->fd_state < -0.1;
        fd_bank = rhs->fd_bank;
        fd_pitch = rhs->fd_pitch;

        //bottombar
        zulu_seconds = rhs->zulu_seconds;
        local_seconds = rhs->local_seconds;
        ground_speed = rhs->ground_speed;
        total_air_temp = rhs->total_air_temp;

        //hsi
        rotation = rhs->rotation;
        heading = rhs->heading;
        turn_rate = rhs->turn_rate;
        current_track = rhs->current_track;
        autopilot_approach_hold = rhs->autopilot_approach_hold > 0.1 || rhs->autopilot_approach_hold < -0.1;
        gps_approach_approach_type = rhs->gps_approach_approach_type;
        nav1_has_nav = rhs->nav1_has_nav > 0.1 || rhs->nav1_has_nav < -0.1;
        nav1_has_loc = rhs->nav1_has_loc > 0.1 || rhs->nav1_has_loc < -0.1;
        nav1_loc = rhs->nav1_loc;
        nav1_obs = rhs->nav1_obs;
        nav1_cdi = rhs->nav1_cdi;
        nav1_to_from = rhs->nav1_to_from;
        nav2_has_nav = rhs->nav2_has_nav > 0.1 || rhs->nav2_has_nav < -0.1;
        nav2_has_loc = rhs->nav2_has_loc > 0.1 || rhs->nav2_has_loc < -0.1;
        nav2_loc = rhs->nav2_loc;
        nav2_obs = rhs->nav2_obs;
        nav2_cdi = rhs->nav2_cdi;
        nav2_to_from = rhs->nav2_to_from;
        gps_wp_desired_track = rhs->gps_wp_desired_track;
        gps_wp_cross_track = rhs->gps_wp_cross_track;
        nav1_has_signal = rhs->nav1_has_signal != 0;
        nav2_has_signal = rhs->nav2_has_signal != 0;
        nav1_has_dme = rhs->nav1_has_dme > 0.1 || rhs->nav1_has_dme < -0.1;
        nav1_dme = rhs->nav1_dme;
        nav1_radial = rhs->nav1_radial;
        nav2_has_dme = rhs->nav2_has_dme > 0.1 || rhs->nav2_has_dme < -0.1;
        nav2_dme = rhs->nav2_dme;
        nav2_radial = rhs->nav2_radial;
        gps_next_wp_dist = rhs->gps_next_wp_dist;
        gps_next_wp_bearing = rhs->gps_next_wp_bearing;
        adf_has_signal = rhs->adf_has_signal > 0.1 || rhs->adf_has_signal < -0.1;
        adf_active_freq = rhs->adf_active_freq;
        adf_radial = rhs->adf_radial + rotation;
        if (adf_radial > 360.0)
            adf_radial -= 360.0;

        //radio
        com1_freq = rhs->com1_freq;
        com2_freq = rhs->com2_freq;
        nav1_freq = rhs->nav1_freq;
        nav2_freq = rhs->nav2_freq;

        //nav info
        gps_is_active_flightplan = rhs->gps_is_active_flightplan > 0.1 || rhs->gps_is_active_flightplan < -0.1;
        gps_is_directto = rhs->gps_is_directto > 0.1 || rhs->gps_is_directto < -0.1;

        //wind
        wind_velocity = rhs->ambient_wind_velocity;
        wind_true_direction = std::lround(rhs->ambient_wind_direction);
        wind_direction = rhs->ambient_wind_direction >= 180.0 ? rhs->ambient_wind_direction - 180.0 + rotation : rhs->ambient_wind_direction + 180.0 + rotation;

        //ap info
        ap_master = rhs->ap_master > 0.1 || rhs->ap_master < -0.1;
        ap_yaw_damper = rhs->ap_yaw_damper > 0.1 || rhs->ap_yaw_damper < -0.1;
        ap_pitch_hold = rhs->ap_pitch_hold > 0.1 || rhs->ap_pitch_hold < -0.1;
        ap_altitude_lock = rhs->ap_altitude_lock > 0.1 || rhs->ap_altitude_lock < -0.1;
        ap_altitude_arm = rhs->ap_altitude_arm > 0.1 || rhs->ap_altitude_arm < -0.1;
        ap_vertical_hold = rhs->ap_vertical_hold > 0.1 || rhs->ap_vertical_hold < -0.1;
        ap_glideslope_active = rhs->ap_glideslope_active > 0.1 || rhs->ap_glideslope_active < -0.1;
        ap_glideslope_arm = rhs->ap_glideslope_arm > 0.1 || rhs->ap_glideslope_arm < -0.1;
        ap_wing_leveler = rhs->ap_wing_leveler > 0.1 || rhs->ap_wing_leveler < -0.1;
        ap_bank_hold = rhs->ap_bank_hold > 0.1 || rhs->ap_bank_hold < -0.1;
        ap_heading_lock = rhs->ap_heading_lock > 0.1 || rhs->ap_heading_lock < -0.1;
        ap_nav1_lock = rhs->ap_nav1_lock > 0.1 || rhs->ap_nav1_lock < -0.1;
        ap_backcourse_hold = rhs->ap_backcourse_hold > 0.1 || rhs->ap_backcourse_hold < -0.1;
    }
};
*/
