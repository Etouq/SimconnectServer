#include "simconnectthread.ih"

void SimconnectThread::sendBlankPfdData()
{
    sendBlankAirspeedData();

    sendBlankAltimeterData();

    sendBlankAttitudeData();

    sendBlankBottombarData();

    sendBlankHsiData();

    sendBlankHsiBrgData();

    sendBlankRadioData();

    sendBlankNavInfoData();

    sendBlankWindData();

    sendBlankApInfoData();
}

void SimconnectThread::sendBlankAirspeedData()
{
    d_lastAirspeedData = PfdAirspeedStruct();

    DataIdentifiers id = DataIdentifiers::AIRSPEED;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastAirspeedData.airspeed), sizeof(d_lastAirspeedData.airspeed));

    id = DataIdentifiers::MAX_SPEED;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastAirspeedData.max_speed), sizeof(d_lastAirspeedData.max_speed));

    id = DataIdentifiers::TRUE_AIRSPEED;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastAirspeedData.true_airspeed), sizeof(d_lastAirspeedData.true_airspeed));

    id = DataIdentifiers::REF_SPEED;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastAirspeedData.ref_speed), sizeof(d_lastAirspeedData.ref_speed));

    emit sendData(dataToSend);
}

void SimconnectThread::sendBlankAltimeterData()
{
    d_lastAltimeterData = PfdAltimeterStruct();

    DataIdentifiers id = DataIdentifiers::ALTITUDE;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastAltimeterData.altitude), sizeof(d_lastAltimeterData.altitude));

    id = DataIdentifiers::RADAR_ALTITUDE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastAltimeterData.radar_altitude), sizeof(d_lastAltimeterData.radar_altitude));

    id = DataIdentifiers::REF_ALTITUDE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastAltimeterData.ref_altitude), sizeof(d_lastAltimeterData.ref_altitude));

    id = DataIdentifiers::PRESSURE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastAltimeterData.pressure), sizeof(d_lastAltimeterData.pressure));

    id = DataIdentifiers::VSPEED;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastAltimeterData.vspeed), sizeof(d_lastAltimeterData.vspeed));

    id = DataIdentifiers::REF_VSPEED;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastAltimeterData.ref_vspeed), sizeof(d_lastAltimeterData.ref_vspeed));

    id = DataIdentifiers::VERT_DEV_VALUE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastAltimeterData.nav1_gsi), sizeof(d_lastAltimeterData.nav1_gsi));

    d_lastVertMode = 0;
    id = DataIdentifiers::VERT_DEV_MODE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastVertMode), sizeof(d_lastVertMode));

    emit sendData(dataToSend);
}

void SimconnectThread::sendBlankAttitudeData()
{
    d_lastAttitudeData = PfdAttitudeStruct();

    DataIdentifiers id = DataIdentifiers::BANK;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastAttitudeData.bank), sizeof(d_lastAttitudeData.bank));

    id = DataIdentifiers::PITCH;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastAttitudeData.pitch), sizeof(d_lastAttitudeData.pitch));

    id = DataIdentifiers::SLIPSKID;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastAttitudeData.slipskid), sizeof(d_lastAttitudeData.slipskid));

    id = DataIdentifiers::ANGLE_OF_ATTACK;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastAttitudeData.angle_of_attack), sizeof(d_lastAttitudeData.angle_of_attack));

    id = DataIdentifiers::AP_FD_STATUS;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastAttitudeData.fd_state), sizeof(d_lastAttitudeData.fd_state));

    id = DataIdentifiers::FD_BANK;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastAttitudeData.fd_bank), sizeof(d_lastAttitudeData.fd_bank));

    id = DataIdentifiers::FD_PITCH;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastAttitudeData.fd_pitch), sizeof(d_lastAttitudeData.fd_pitch));

    emit sendData(dataToSend);
}

void SimconnectThread::sendBlankBottombarData()
{
    d_lastBottombarData = PfdBottombarStruct();

    DataIdentifiers id = DataIdentifiers::ZULU_SECONDS;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastBottombarData.zulu_seconds), sizeof(d_lastBottombarData.zulu_seconds));

    id = DataIdentifiers::LOCAL_SECONDS;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastBottombarData.local_seconds), sizeof(d_lastBottombarData.local_seconds));

    id = DataIdentifiers::GROUND_SPEED;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastBottombarData.ground_speed), sizeof(d_lastBottombarData.ground_speed));

    id = DataIdentifiers::TOTAL_AIR_TEMP;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastBottombarData.total_air_temp), sizeof(d_lastBottombarData.total_air_temp));

    emit sendData(dataToSend);
}

void SimconnectThread::sendBlankHsiData()
{
    d_lastHsiData = PfdHsiStruct();

    DataIdentifiers id = DataIdentifiers::ROTATION;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiData.rotation), sizeof(d_lastHsiData.rotation));

    id = DataIdentifiers::HEADING;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiData.heading), sizeof(d_lastHsiData.heading));

    id = DataIdentifiers::TURN_RATE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiData.turn_rate), sizeof(d_lastHsiData.turn_rate));

    id = DataIdentifiers::CURRENT_TRACK;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiData.current_track), sizeof(d_lastHsiData.current_track));

    id = DataIdentifiers::GPS_WP_DTK;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiData.gps_wp_desired_track), sizeof(d_lastHsiData.gps_wp_desired_track));

    id = DataIdentifiers::COORDINATES;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiData.currLat), sizeof(d_lastHsiData.currLat));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiData.currLon), sizeof(d_lastHsiData.currLon));

    id = DataIdentifiers::TRUE_HEADING;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiData.true_heading), sizeof(d_lastHsiData.true_heading));

    d_lastNavSource = 0;
    id = DataIdentifiers::NAV_SOURCE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastNavSource), sizeof(d_lastNavSource));

    d_lastDisplayDeviation = false;
    id = DataIdentifiers::DISPLAY_DEVIATION;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastDisplayDeviation), sizeof(d_lastDisplayDeviation));

    d_lastCourse = 0;
    id = DataIdentifiers::COURSE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiData.gps_wp_desired_track), sizeof(d_lastHsiData.gps_wp_desired_track));

    d_lastCourseDeviation = 0;
    id = DataIdentifiers::COURSE_DEVIATION;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiData.gps_wp_cross_track), sizeof(d_lastHsiData.gps_wp_cross_track));

    d_lastToFrom = 0;
    id = DataIdentifiers::TO_FROM;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastToFrom), sizeof(d_lastToFrom));

    emit sendData(dataToSend);
}

void SimconnectThread::sendBlankHsiBrgData()
{
    d_lastHsiBrgData = PfdHsiBrgStruct();

    DataIdentifiers id = DataIdentifiers::NAV1_DME;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiBrgData.nav1_dme), sizeof(d_lastHsiBrgData.nav1_dme));

    id = DataIdentifiers::NAV1_BEARING;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiBrgData.nav1_radial), sizeof(d_lastHsiBrgData.nav1_radial));

    id = DataIdentifiers::NAV1_HAS_NAV;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiBrgData.nav1_has_nav), sizeof(d_lastHsiBrgData.nav1_has_nav));

    id = DataIdentifiers::NAV1_HAS_SIGNAL;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiBrgData.nav1_has_signal), sizeof(d_lastHsiBrgData.nav1_has_signal));

    id = DataIdentifiers::NAV1_HAS_DME;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiBrgData.nav1_has_dme), sizeof(d_lastHsiBrgData.nav1_has_dme));

    id = DataIdentifiers::NAV2_DME;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiBrgData.nav2_dme), sizeof(d_lastHsiBrgData.nav2_dme));

    id = DataIdentifiers::NAV2_BEARING;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiBrgData.nav2_radial), sizeof(d_lastHsiBrgData.nav2_radial));

    id = DataIdentifiers::NAV2_HAS_NAV;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiBrgData.nav2_has_nav), sizeof(d_lastHsiBrgData.nav2_has_nav));

    id = DataIdentifiers::NAV2_HAS_SIGNAL;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiBrgData.nav2_has_signal), sizeof(d_lastHsiBrgData.nav2_has_signal));

    id = DataIdentifiers::NAV2_HAS_DME;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiBrgData.nav2_has_dme), sizeof(d_lastHsiBrgData.nav2_has_dme));

    id = DataIdentifiers::GPS_DISTANCE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiBrgData.gps_next_wp_dist), sizeof(d_lastHsiBrgData.gps_next_wp_dist));

    id = DataIdentifiers::GPS_BEARING;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiBrgData.gps_next_wp_bearing), sizeof(d_lastHsiBrgData.gps_next_wp_bearing));

    id = DataIdentifiers::ADF_HAS_SIGNAL;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiBrgData.adf_has_signal), sizeof(d_lastHsiBrgData.adf_has_signal));

    id = DataIdentifiers::ADF_FREQ;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiBrgData.adf_active_freq), sizeof(d_lastHsiBrgData.adf_active_freq));

    id = DataIdentifiers::ADF_RADIAL;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiBrgData.adf_radial), sizeof(d_lastHsiBrgData.adf_radial));

    emit sendData(dataToSend);
}

void SimconnectThread::sendBlankRadioData()
{
    d_lastRadioData = PfdRadioStruct();

    DataIdentifiers id = DataIdentifiers::COM1_FREQ;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastRadioData.com1_freq), sizeof(d_lastRadioData.com1_freq));

    id = DataIdentifiers::COM2_FREQ;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastRadioData.com2_freq), sizeof(d_lastRadioData.com2_freq));

    id = DataIdentifiers::NAV1_FREQ;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastRadioData.nav1_freq), sizeof(d_lastRadioData.nav1_freq));

    id = DataIdentifiers::NAV2_FREQ;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastRadioData.nav2_freq), sizeof(d_lastRadioData.nav2_freq));

    emit sendData(dataToSend);
}

void SimconnectThread::sendBlankNavInfoData()
{
    d_lastNavInfoData = PfdNavInfoStruct();

    DataIdentifiers id = DataIdentifiers::GPS_IS_ACTIVE_FLIGHTPLAN;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastNavInfoData.gps_is_active_flightplan), sizeof(d_lastNavInfoData.gps_is_active_flightplan));

    id = DataIdentifiers::LEG_IS_DIRECT_TO;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastNavInfoData.gps_is_directto), sizeof(d_lastNavInfoData.gps_is_directto));

    id = DataIdentifiers::GPS_WP_ETE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastNavInfoData.gps_wp_ete), sizeof(d_lastNavInfoData.gps_wp_ete));

    id = DataIdentifiers::GPS_ETE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastNavInfoData.gps_ete), sizeof(d_lastNavInfoData.gps_ete));

    emit sendData(dataToSend);
}

void SimconnectThread::sendBlankWindData()
{
    d_lastWindData = PfdWindStruct();

    DataIdentifiers id = DataIdentifiers::WIND_STRENGTH;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastWindData.wind_velocity), sizeof(d_lastWindData.wind_velocity));

    id = DataIdentifiers::WIND_TRUE_DIRECTION;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastWindData.wind_true_direction), sizeof(d_lastWindData.wind_true_direction));

    id = DataIdentifiers::WIND_DIRECTION;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastWindData.wind_direction), sizeof(d_lastWindData.wind_direction));

    emit sendData(dataToSend);
}

void SimconnectThread::sendBlankApInfoData()
{
    d_lastApInfoData = PfdApInfoStruct();

    DataIdentifiers id = DataIdentifiers::AP_STATUS;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastApInfoData.ap_master), sizeof(d_lastApInfoData.ap_master));

    id = DataIdentifiers::AP_YD_STATUS;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&d_lastApInfoData.ap_yaw_damper), sizeof(d_lastApInfoData.ap_yaw_damper));

    d_lastAP_VerticalActive = "";
    uint8_t size = d_lastAP_VerticalActive.size();
    id = DataIdentifiers::AP_VERTICAL_ACTIVE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
    dataToSend.append(d_lastAP_VerticalActive.constData(), size);

    d_lastAP_ModeReference = "";
    size = d_lastAP_ModeReference.size();
    id = DataIdentifiers::AP_MODE_REFERENCE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
    dataToSend.append(d_lastAP_ModeReference.constData(), size);

    d_lastAP_Armed = "";
    size = d_lastAP_Armed.size();
    id = DataIdentifiers::AP_ARMED;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
    dataToSend.append(d_lastAP_Armed.constData(), size);

    d_lastAP_ArmedReference = "";
    size = d_lastAP_ArmedReference.size();
    id = DataIdentifiers::AP_ARMED_REFERENCE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
    dataToSend.append(d_lastAP_ArmedReference.constData(), size);

    d_lastAP_LateralActive = "";
    size = d_lastAP_LateralActive.size();
    id = DataIdentifiers::AP_LATERAL_ACTIVE;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
    dataToSend.append(d_lastAP_LateralActive.constData(), size);

    d_lastAP_LateralArmed = "";
    size = d_lastAP_LateralArmed.size();
    id = DataIdentifiers::AP_LATERAL_ARMED;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&size), sizeof(size));
    dataToSend.append(d_lastAP_LateralArmed.constData(), size);

    emit sendData(dataToSend);
}

















