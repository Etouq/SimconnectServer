#include "simconnectthread.ih"

void SimconnectThread::sendBlankPfdData()
{
    PfdCleanDataStruct blankData;

    //airspeed
    DataIdentifiers id = DataIdentifiers::AIRSPEED;
    QByteArray dataToSend(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.airspeed), sizeof(blankData.airspeed));

    id = DataIdentifiers::MAX_SPEED;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.max_speed), sizeof(blankData.max_speed));

    id = DataIdentifiers::TRUE_AIRSPEED;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.true_airspeed), sizeof(blankData.true_airspeed));

    id = DataIdentifiers::REF_SPEED;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.ref_speed), sizeof(blankData.ref_speed));

    id = DataIdentifiers::AP_FLC;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.ap_flc), sizeof(blankData.ap_flc));


    //altitude
    id = DataIdentifiers::ALTITUDE;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.altitude), sizeof(blankData.altitude));

    id = DataIdentifiers::RADAR_ALTITUDE;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.radar_altitude), sizeof(blankData.radar_altitude));

    id = DataIdentifiers::REF_ALTITUDE;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.ref_altitude), sizeof(blankData.ref_altitude));

    id = DataIdentifiers::PRESSURE;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.pressure), sizeof(blankData.pressure));


    //vspeed
    id = DataIdentifiers::VSPEED;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.vspeed), sizeof(blankData.vspeed));

    id = DataIdentifiers::REF_VSPEED;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.ref_vspeed), sizeof(blankData.ref_vspeed));


    //vert dev
    d_lastVertMode = 0;
    id = DataIdentifiers::VERT_DEV_MODE;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&d_lastVertMode), sizeof(d_lastVertMode));

    id = DataIdentifiers::VERT_DEV_VALUE;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.gps_vert_error), sizeof(blankData.gps_vert_error));


    //aoa
    id = DataIdentifiers::ANGLE_OF_ATTACK;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.angle_of_attack), sizeof(blankData.angle_of_attack));


    //attitude
    id = DataIdentifiers::BANK;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.bank), sizeof(blankData.bank));

    id = DataIdentifiers::PITCH;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.pitch), sizeof(blankData.pitch));

    id = DataIdentifiers::SLIPSKID;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.slipskid), sizeof(blankData.slipskid));

    id = DataIdentifiers::AP_FD_STATUS;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.fd_state), sizeof(blankData.fd_state));

    id = DataIdentifiers::FD_BANK;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.fd_bank), sizeof(blankData.fd_bank));

    id = DataIdentifiers::FD_PITCH;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.fd_pitch), sizeof(blankData.fd_pitch));


    //bottombar
    id = DataIdentifiers::ZULU_SECONDS;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.zulu_seconds), sizeof(blankData.zulu_seconds));

    id = DataIdentifiers::LOCAL_SECONDS;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.local_seconds), sizeof(blankData.local_seconds));

    id = DataIdentifiers::GROUND_SPEED;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.ground_speed), sizeof(blankData.ground_speed));

    id = DataIdentifiers::TOTAL_AIR_TEMP;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.total_air_temp), sizeof(blankData.total_air_temp));


    //hsi
    id = DataIdentifiers::ROTATION;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.rotation), sizeof(blankData.rotation));

    id = DataIdentifiers::HEADING;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.heading), sizeof(blankData.heading));

    id = DataIdentifiers::TURN_RATE;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.turn_rate), sizeof(blankData.turn_rate));

    id = DataIdentifiers::CURRENT_TRACK;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.current_track), sizeof(blankData.current_track));

    d_lastNavSource = 0;
    id = DataIdentifiers::NAV_SOURCE;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&d_lastNavSource), sizeof(d_lastNavSource));

    d_lastDisplayDeviation = false;
    id = DataIdentifiers::DISPLAY_DEVIATION;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&d_lastDisplayDeviation), sizeof(d_lastDisplayDeviation));

    d_lastCourse = 0;
    id = DataIdentifiers::COURSE;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&d_lastCourse), sizeof(d_lastCourse));

    d_lastCourseDeviation = 0;
    id = DataIdentifiers::COURSE_DEVIATION;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&d_lastCourseDeviation), sizeof(d_lastCourseDeviation));

    d_lastToFrom = 0;
    id = DataIdentifiers::TO_FROM;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&d_lastToFrom), sizeof(d_lastToFrom));


    //hsi brg
    //nav 1
    id = DataIdentifiers::NAV1_DME;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.nav1_dme), sizeof(blankData.nav1_dme));

    id = DataIdentifiers::NAV1_BEARING;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.nav1_radial), sizeof(blankData.nav1_radial));

    id = DataIdentifiers::NAV1_HAS_NAV;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.nav1_has_nav), sizeof(blankData.nav1_has_nav));

    id = DataIdentifiers::NAV1_HAS_SIGNAL;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.nav1_has_signal), sizeof(blankData.nav1_has_signal));

    id = DataIdentifiers::NAV1_HAS_DME;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.nav1_has_dme), sizeof(blankData.nav1_has_dme));

    //nav 2
    id = DataIdentifiers::NAV2_DME;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.nav2_dme), sizeof(blankData.nav2_dme));

    id = DataIdentifiers::NAV2_BEARING;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.nav2_radial), sizeof(blankData.nav2_radial));

    id = DataIdentifiers::NAV2_HAS_NAV;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.nav2_has_nav), sizeof(blankData.nav2_has_nav));

    id = DataIdentifiers::NAV2_HAS_SIGNAL;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.nav2_has_signal), sizeof(blankData.nav2_has_signal));

    id = DataIdentifiers::NAV2_HAS_DME;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.nav2_has_dme), sizeof(blankData.nav2_has_dme));

    //gps
    id = DataIdentifiers::GPS_DISTANCE;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.gps_next_wp_dist), sizeof(blankData.gps_next_wp_dist));

    d_lastPfdData.gps_next_wp_bearing = blankData.gps_next_wp_bearing;
    id = DataIdentifiers::GPS_BEARING;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.gps_next_wp_bearing), sizeof(blankData.gps_next_wp_bearing));

    //adf
    id = DataIdentifiers::ADF_HAS_SIGNAL;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.adf_has_signal), sizeof(blankData.adf_has_signal));

    id = DataIdentifiers::ADF_FREQ;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.adf_active_freq), sizeof(blankData.adf_active_freq));

    id = DataIdentifiers::ADF_RADIAL;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.adf_radial), sizeof(blankData.adf_radial));


    //radio
    id = DataIdentifiers::COM1_FREQ;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.com1_freq), sizeof(blankData.com1_freq));

    id = DataIdentifiers::COM2_FREQ;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.com2_freq), sizeof(blankData.com2_freq));

    id = DataIdentifiers::NAV1_FREQ;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.nav1_freq), sizeof(blankData.nav1_freq));

    id = DataIdentifiers::NAV2_FREQ;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.nav2_freq), sizeof(blankData.nav2_freq));


    //nav info
    id = DataIdentifiers::GPS_IS_ACTIVE_FLIGHTPLAN;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.gps_is_active_flightplan), sizeof(blankData.gps_is_active_flightplan));

    id = DataIdentifiers::LEG_IS_DIRECT_TO;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.gps_is_directto), sizeof(blankData.gps_is_directto));


    id = DataIdentifiers::GPS_WP_DTK;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.gps_wp_desired_track), sizeof(blankData.gps_wp_desired_track));

    id = DataIdentifiers::GPS_WP_ETE;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.gps_wp_ete), sizeof(blankData.gps_wp_ete));

    id = DataIdentifiers::GPS_ETE;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.gps_ete), sizeof(blankData.gps_ete));


    //wind
    id = DataIdentifiers::WIND_STRENGTH;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.wind_velocity), sizeof(blankData.wind_velocity));

    id = DataIdentifiers::WIND_TRUE_DIRECTION;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.wind_true_direction), sizeof(blankData.wind_true_direction));

    id = DataIdentifiers::WIND_DIRECTION;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.wind_direction), sizeof(blankData.wind_direction));


    //ap info
    id = DataIdentifiers::AP_STATUS;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.ap_master), sizeof(blankData.ap_master));

    id = DataIdentifiers::AP_YD_STATUS;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.ap_yaw_damper), sizeof(blankData.ap_yaw_damper));

    QByteArray stringData = "";
    uint8_t size = 0;

    id = DataIdentifiers::AP_VERTICAL_ACTIVE;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
    dataToSend.append(stringData.constData(), size);
    d_lastAP_VerticalActive = "";

    id = DataIdentifiers::AP_MODE_REFERENCE;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
    dataToSend.append(stringData.constData(), size);
    d_lastAP_ModeReference = "";

    id = DataIdentifiers::AP_ARMED;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
    dataToSend.append(stringData.constData(), size);
    d_lastAP_Armed = "";

    id = DataIdentifiers::AP_ARMED_REFERENCE;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
    dataToSend.append(stringData.constData(), size);
    d_lastAP_ArmedReference = "";

    id = DataIdentifiers::AP_LATERAL_ACTIVE;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
    dataToSend.append(stringData.constData(), size);
    d_lastAP_LateralActive = "";

    id = DataIdentifiers::AP_LATERAL_ARMED;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
    dataToSend.append(stringData.constData(), size);
    d_lastAP_LateralArmed = "";

    emit sendData(dataToSend);
}
