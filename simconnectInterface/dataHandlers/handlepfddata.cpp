#include "../simconnectthread.ih"
#include <QDebug>

void SimconnectThread::handlePfdData(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData)
{
    PfdCleanDataStruct newData(reinterpret_cast<PfdDataStruct *>(&pObjData->dwData));

    DataIdentifiers id = DataIdentifiers::AIRSPEED;

    QByteArray dataToSend(reinterpret_cast<char *>(&id), sizeof(id));

    //airspeed
    d_lastPfdData.airspeed = newData.airspeed;
    dataToSend.append(reinterpret_cast<char *>(&newData.airspeed), sizeof(newData.airspeed));

    if (fabs(d_lastPfdData.max_speed - newData.max_speed) >= 0.09)
    {
        d_lastPfdData.max_speed = newData.max_speed;
        id = DataIdentifiers::MAX_SPEED;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.max_speed), sizeof(newData.max_speed));
    }

    if (d_lastPfdData.true_airspeed != newData.true_airspeed)
    {
        d_lastPfdData.true_airspeed = newData.true_airspeed;
        id = DataIdentifiers::TRUE_AIRSPEED;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.true_airspeed), sizeof(newData.true_airspeed));
    }

    if (d_lastPfdData.ref_speed != newData.ref_speed)
    {
        d_lastPfdData.ref_speed = newData.ref_speed;
        id = DataIdentifiers::REF_SPEED;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.ref_speed), sizeof(newData.ref_speed));
    }

    if(d_lastPfdData.ap_flc != newData.ap_flc)
    {
        d_lastPfdData.ap_flc = newData.ap_flc;
        id = DataIdentifiers::AP_FLC;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.ap_flc), sizeof(newData.ap_flc));
    }


    //altimeter
    if (fabs(d_lastPfdData.altitude - newData.altitude) >= 0.09)
    {
        d_lastPfdData.altitude = newData.altitude;
        id = DataIdentifiers::ALTITUDE;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.altitude), sizeof(newData.altitude));
    }

    if (fabs(d_lastPfdData.radar_altitude - newData.radar_altitude) >= 0.09)
    {
        d_lastPfdData.radar_altitude = newData.radar_altitude;
        id = DataIdentifiers::RADAR_ALTITUDE;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.radar_altitude), sizeof(newData.radar_altitude));
    }

    if (d_lastPfdData.ref_altitude != newData.ref_altitude)
    {
        d_lastPfdData.ref_altitude = newData.ref_altitude;
        id = DataIdentifiers::REF_ALTITUDE;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.ref_altitude), sizeof(newData.ref_altitude));
    }

    if (fabs(d_lastPfdData.pressure - newData.pressure) >= 0.009)
    {
        d_lastPfdData.pressure = newData.pressure;
        id = DataIdentifiers::PRESSURE;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.pressure), sizeof(newData.pressure));
    }

    //vspeed
    if (fabs(d_lastPfdData.vspeed - newData.vspeed) >= 0.009)
    {
        d_lastPfdData.vspeed = newData.vspeed;
        id = DataIdentifiers::VSPEED;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.vspeed), sizeof(newData.vspeed));
    }

    if (d_lastPfdData.ref_vspeed != newData.ref_vspeed)
    {
        d_lastPfdData.ref_vspeed = newData.ref_vspeed;
        id = DataIdentifiers::REF_VSPEED;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.ref_vspeed), sizeof(newData.ref_vspeed));
    }

    //vert dev
    int32_t cdiSource = newData.gpsDrivesNav1 ? 3 : newData.autopilot_nav_selected;
    switch(cdiSource)
    {
        case 1: //nav1
        {
            if(newData.nav1_has_glideslope)
            {
                if(d_lastVertMode != 2)
                {
                    d_lastVertMode = 2;
                    id = DataIdentifiers::VERT_DEV_MODE;
                    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<char *>(&d_lastVertMode), sizeof(d_lastVertMode));

                    //make sure all other values get evaluated
                    d_lastPfdData.nav1_gsi = newData.nav1_gsi + 5.0;
                }
                if(fabs(d_lastPfdData.nav1_gsi - newData.nav1_gsi) >= 0.1)
                {
                    d_lastPfdData.nav1_gsi = newData.nav1_gsi;
                    newData.nav1_gsi /= 127.0;
                    id = DataIdentifiers::VERT_DEV_VALUE;
                    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<char *>(&newData.nav1_gsi), sizeof(newData.nav1_gsi));
                }
            }
            else
            {
                if(d_lastVertMode != 0)
                {
                    d_lastVertMode = 0;
                    id = DataIdentifiers::VERT_DEV_MODE;
                    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<char *>(&d_lastVertMode), sizeof(d_lastVertMode));
                }
            }
            break;
        }
        case 2: //nav2
        {
            if(newData.nav2_has_glideslope)
            {
                if(d_lastVertMode != 2)
                {
                    d_lastVertMode = 2;
                    id = DataIdentifiers::VERT_DEV_MODE;
                    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<char *>(&d_lastVertMode), sizeof(d_lastVertMode));

                    //make sure all other values get evaluated
                    d_lastPfdData.nav2_gsi = newData.nav2_gsi + 5.0;
                }
                if(fabs(d_lastPfdData.nav2_gsi - newData.nav2_gsi) >= 0.1)
                {
                    d_lastPfdData.nav2_gsi = newData.nav2_gsi;
                    newData.nav2_gsi /= 127.0;
                    id = DataIdentifiers::VERT_DEV_VALUE;
                    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<char *>(&newData.nav2_gsi), sizeof(newData.nav2_gsi));
                }
            }
            else
            {
                if(d_lastVertMode != 0)
                {
                    d_lastVertMode = 0;
                    id = DataIdentifiers::VERT_DEV_MODE;
                    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<char *>(&d_lastVertMode), sizeof(d_lastVertMode));
                }
            }
            break;
        }
        case 3: //gps
        {
            if(newData.gps_approach_active && newData.gps_approach_approach_type == 10) //10 = rnav
            {
                if(d_lastVertMode != 3)
                {
                    d_lastVertMode = 3;
                    id = DataIdentifiers::VERT_DEV_MODE;
                    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<char *>(&d_lastVertMode), sizeof(d_lastVertMode));

                    //make sure all other values get evaluated
                    d_lastPfdData.gps_vert_error = newData.gps_vert_error + 5.0;
                }
                if(fabs(d_lastPfdData.gps_vert_error - newData.gps_vert_error) >= 0.1)
                {
                    d_lastPfdData.gps_vert_error = newData.gps_vert_error;
                    newData.gps_vert_error /= 150.0;
                    id = DataIdentifiers::VERT_DEV_VALUE;
                    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<char *>(&newData.gps_vert_error), sizeof(newData.gps_vert_error));
                }
            }
            else if(newData.nav1_has_glideslope)
            {
                if(d_lastVertMode != 4)
                {
                    d_lastVertMode = 4;
                    id = DataIdentifiers::VERT_DEV_MODE;
                    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<char *>(&d_lastVertMode), sizeof(d_lastVertMode));

                    //make sure all other values get evaluated
                    d_lastPfdData.nav1_gsi = newData.nav1_gsi + 5.0;
                }
                if(fabs(d_lastPfdData.nav1_gsi - newData.nav1_gsi) >= 0.1)
                {
                    d_lastPfdData.nav1_gsi = newData.nav1_gsi;
                    newData.nav1_gsi /= 127.0;
                    id = DataIdentifiers::VERT_DEV_VALUE;
                    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<char *>(&newData.nav1_gsi), sizeof(newData.nav1_gsi));
                }
            }
            else if(newData.nav2_has_glideslope)
            {
                if(d_lastVertMode != 4)
                {
                    d_lastVertMode = 4;
                    id = DataIdentifiers::VERT_DEV_MODE;
                    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<char *>(&d_lastVertMode), sizeof(d_lastVertMode));

                    //make sure all other values get evaluated
                    d_lastPfdData.nav2_gsi = newData.nav2_gsi + 5.0;
                }
                if(fabs(d_lastPfdData.nav2_gsi - newData.nav2_gsi) >= 0.1)
                {
                    d_lastPfdData.nav2_gsi = newData.nav2_gsi;
                    newData.nav2_gsi /= 127.0;
                    id = DataIdentifiers::VERT_DEV_VALUE;
                    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<char *>(&newData.nav2_gsi), sizeof(newData.nav2_gsi));
                }
            }
            else
            {
                if(d_lastVertMode != 0)
                {
                    d_lastVertMode = 0;
                    id = DataIdentifiers::VERT_DEV_MODE;
                    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<char *>(&d_lastVertMode), sizeof(d_lastVertMode));
                }
            }

            break;
        }
    }


    //aoa
    if (fabs(d_lastPfdData.angle_of_attack - newData.angle_of_attack) >= 0.25)
    {
        d_lastPfdData.angle_of_attack = newData.angle_of_attack;
        id = DataIdentifiers::ANGLE_OF_ATTACK;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.angle_of_attack), sizeof(newData.angle_of_attack));
    }


    //attitude
    id = DataIdentifiers::BANK;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&newData.bank), sizeof(newData.bank));

    id = DataIdentifiers::PITCH;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&newData.pitch), sizeof(newData.pitch));

    id = DataIdentifiers::SLIPSKID;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&newData.slipskid), sizeof(newData.slipskid));

    if (d_lastPfdData.fd_state != newData.fd_state)
    {
        d_lastPfdData.fd_state = newData.fd_state;
        id = DataIdentifiers::AP_FD_STATUS;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.fd_state), sizeof(newData.fd_state));
    }

    if(newData.fd_state)
    {
        id = DataIdentifiers::FD_BANK;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.fd_bank), sizeof(newData.fd_bank));

        id = DataIdentifiers::FD_PITCH;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.fd_pitch), sizeof(newData.fd_pitch));
    }


    //bottombar
    if (d_lastPfdData.zulu_seconds != newData.zulu_seconds)
    {
        d_lastPfdData.zulu_seconds = newData.zulu_seconds;
        id = DataIdentifiers::ZULU_SECONDS;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.zulu_seconds), sizeof(newData.zulu_seconds));
    }
    if (d_lastPfdData.local_seconds != newData.local_seconds)
    {
        d_lastPfdData.local_seconds = newData.local_seconds;
        id = DataIdentifiers::LOCAL_SECONDS;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.local_seconds), sizeof(newData.local_seconds));
    }
    if (d_lastPfdData.ground_speed != newData.ground_speed)
    {
        d_lastPfdData.ground_speed = newData.ground_speed;
        id = DataIdentifiers::GROUND_SPEED;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.ground_speed), sizeof(newData.ground_speed));
    }
    if (fabs(d_lastPfdData.total_air_temp != newData.total_air_temp) >= 0.4)
    {
        d_lastPfdData.total_air_temp = newData.total_air_temp;
        id = DataIdentifiers::TOTAL_AIR_TEMP;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.total_air_temp), sizeof(newData.total_air_temp));
    }


    //hsi
    if (fabs(d_lastPfdData.rotation - newData.rotation) >= 0.0009)
    {
        d_lastPfdData.rotation = newData.rotation;
        id = DataIdentifiers::ROTATION;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.rotation), sizeof(newData.rotation));
    }
    if (fabs(d_lastPfdData.heading - newData.heading) >= 0.0009)
    {
        d_lastPfdData.heading = newData.heading;
        id = DataIdentifiers::HEADING;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.heading), sizeof(newData.heading));
    }
    if (fabs(d_lastPfdData.turn_rate - newData.turn_rate) >= 0.0009)
    {
        d_lastPfdData.turn_rate = newData.turn_rate;
        id = DataIdentifiers::TURN_RATE;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.turn_rate), sizeof(newData.turn_rate));
    }
    if (fabs(d_lastPfdData.current_track - newData.current_track) >= 0.0009)
    {
        d_lastPfdData.current_track = newData.current_track;
        id = DataIdentifiers::CURRENT_TRACK;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.current_track), sizeof(newData.current_track));
    }

    if (fabs(d_lastPfdData.gps_wp_desired_track - newData.gps_wp_desired_track) >= 0.009)
    {
        d_lastPfdData.gps_wp_desired_track = newData.gps_wp_desired_track;
        id = DataIdentifiers::GPS_WP_DTK;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.gps_wp_desired_track), sizeof(newData.gps_wp_desired_track));
    }

    cdiSource = 3;
    if (!newData.gpsDrivesNav1 || (newData.autopilot_approach_hold && newData.gps_approach_approach_type == 10)) //10 = rnav
    {
        cdiSource = newData.autopilot_nav_selected;
    }
    switch (cdiSource)
    {
        case 1: //nav1
        {
            if(d_lastDisplayDeviation != newData.nav1_has_nav)
            {
                d_lastDisplayDeviation = newData.nav1_has_nav;
                id = DataIdentifiers::DISPLAY_DEVIATION;
                dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<char *>(&newData.nav1_has_nav), sizeof(newData.nav1_has_nav));
            }
            if(newData.nav1_has_loc)
            {
                if(d_lastNavSource != 2)
                {
                    d_lastNavSource = 2;
                    id = DataIdentifiers::NAV_SOURCE;
                    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<char *>(&d_lastNavSource), sizeof(d_lastNavSource));

                    //make sure all values get updated because of the modeswitch
                    d_lastCourseDeviation = newData.nav1_cdi + 5.0;
                }

                if (fabs(d_lastCourse - newData.nav1_loc) >= 0.0009)
                {
                    d_lastCourse = newData.nav1_loc;
                    id = DataIdentifiers::COURSE;
                    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<char *>(&newData.nav1_loc), sizeof(newData.nav1_loc));
                }
            }
            else
            {
                if(d_lastNavSource != 1)
                {
                    d_lastNavSource = 1;
                    id = DataIdentifiers::NAV_SOURCE;
                    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<char *>(&d_lastNavSource), sizeof(d_lastNavSource));

                    //make sure all values get updated because of the modeswitch
                    d_lastCourseDeviation = newData.nav1_cdi + 5.0;
                }

                if (fabs(d_lastCourse - newData.nav1_obs) >= 0.0009)
                {
                    d_lastCourse = newData.nav1_obs;
                    id = DataIdentifiers::COURSE;
                    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<char *>(&newData.nav1_obs), sizeof(newData.nav1_obs));
                }
            }

            if (fabs(d_lastCourseDeviation - newData.nav1_cdi) >= 0.3)
            {
                d_lastCourseDeviation = newData.nav1_cdi;
                newData.nav1_cdi /= 127.0;
                id = DataIdentifiers::COURSE_DEVIATION;
                dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<char *>(&newData.nav1_cdi), sizeof(newData.nav1_cdi));
            }

            if (d_lastToFrom != newData.nav1_to_from)
            {
                d_lastToFrom = newData.nav1_to_from;
                id = DataIdentifiers::TO_FROM;
                dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<char *>(&newData.nav1_to_from), sizeof(newData.nav1_to_from));
            }
            break;
        }
        case 2: //nav2
        {
            if(d_lastDisplayDeviation != newData.nav2_has_nav)
            {
                d_lastDisplayDeviation = newData.nav2_has_nav;
                id = DataIdentifiers::DISPLAY_DEVIATION;
                dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<char *>(&newData.nav2_has_nav), sizeof(newData.nav2_has_nav));
            }

            if(newData.nav2_has_loc)
            {
                if(d_lastNavSource != 4)
                {
                    d_lastNavSource = 4;
                    id = DataIdentifiers::NAV_SOURCE;
                    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<char *>(&d_lastNavSource), sizeof(d_lastNavSource));

                    //make sure all values get updated because of the modeswitch
                    d_lastCourseDeviation = newData.nav2_cdi + 5.0;
                }

                if (fabs(d_lastCourse - newData.nav2_loc) >= 0.0009)
                {
                    d_lastCourse = newData.nav2_loc;
                    id = DataIdentifiers::COURSE;
                    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<char *>(&newData.nav2_loc), sizeof(newData.nav2_loc));
                }
            }
            else
            {
                if(d_lastNavSource != 3)
                {
                    d_lastNavSource = 3;
                    id = DataIdentifiers::NAV_SOURCE;
                    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<char *>(&d_lastNavSource), sizeof(d_lastNavSource));

                    //make sure all values get updated because of the modeswitch
                    d_lastCourseDeviation = newData.nav2_cdi + 5.0;
                }

                if (fabs(d_lastCourse - newData.nav2_obs) >= 0.0009)
                {
                    d_lastCourse = newData.nav2_obs;
                    id = DataIdentifiers::COURSE;
                    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<char *>(&newData.nav2_obs), sizeof(newData.nav2_obs));
                }
            }

            if (fabs(d_lastCourseDeviation - newData.nav2_cdi) >= 0.009)
            {
                d_lastCourseDeviation = newData.nav2_cdi;
                newData.nav2_cdi /= 127.0;
                id = DataIdentifiers::COURSE_DEVIATION;
                dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<char *>(&newData.nav2_cdi), sizeof(newData.nav2_cdi));
            }

            if (d_lastToFrom != newData.nav2_to_from)
            {
                d_lastToFrom = newData.nav2_to_from;
                id = DataIdentifiers::TO_FROM;
                dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<char *>(&newData.nav2_to_from), sizeof(newData.nav2_to_from));
            }
            break;
        }
        case 3: //gps
        {
            if(d_lastNavSource != 0)
            {
                d_lastNavSource = 0;
                id = DataIdentifiers::NAV_SOURCE;
                dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<char *>(&d_lastNavSource), sizeof(d_lastNavSource));

                //make sure all values get updated because of the modeswitch
                d_lastCourseDeviation = newData.gps_wp_cross_track + 5.0;
            }

            //should be implemented using 'gps_next_wp_id != ""'
            if(d_lastDisplayDeviation != (d_lastStringsData.gps_wp_next_id != ""))
            {
                d_lastDisplayDeviation = (d_lastStringsData.gps_wp_next_id != "");
                id = DataIdentifiers::DISPLAY_DEVIATION;
                dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<char *>(&d_lastDisplayDeviation), sizeof(d_lastDisplayDeviation));
            }

            if (fabs(d_lastCourse - newData.gps_wp_desired_track) >= 0.0009)
            {
                d_lastCourse = newData.gps_wp_desired_track;
                id = DataIdentifiers::COURSE;
                dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<char *>(&newData.gps_wp_desired_track), sizeof(newData.gps_wp_desired_track));
            }

            if (fabs(d_lastCourseDeviation - newData.gps_wp_cross_track) >= 0.3)
            {
                d_lastCourseDeviation = newData.gps_wp_cross_track;
                id = DataIdentifiers::COURSE_DEVIATION;
                dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<char *>(&newData.gps_wp_cross_track), sizeof(newData.gps_wp_cross_track));
            }

            //maybe change to zero if preferred
            if (d_lastToFrom != 1)
            {
                d_lastToFrom = 1;
                id = DataIdentifiers::TO_FROM;
                dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<char *>(&d_lastToFrom), sizeof(d_lastToFrom));
            }

            break;
        }
    }

    if (fabs(d_lastPfdData.true_heading - newData.true_heading) >= 0.0009)
    {
        d_lastPfdData.true_heading = newData.true_heading;
        id = DataIdentifiers::TRUE_HEADING;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.true_heading), sizeof(newData.true_heading));
    }


    //hsi brg
    //nav1
    if (fabs(d_lastPfdData.nav1_dme - newData.nav1_dme) >= 0.09)
    {
        d_lastPfdData.nav1_dme = newData.nav1_dme;
        id = DataIdentifiers::NAV1_DME;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.nav1_dme), sizeof(newData.nav1_dme));
    }
    if (fabs(d_lastPfdData.nav1_radial - newData.nav1_radial) >= 0.0009)
    {
        d_lastPfdData.nav1_radial = newData.nav1_radial;
        id = DataIdentifiers::NAV1_BEARING;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.nav1_radial), sizeof(newData.nav1_radial));
    }
    if (d_lastPfdData.nav1_has_nav != newData.nav1_has_nav)
    {
        d_lastPfdData.nav1_has_nav = newData.nav1_has_nav;
        id = DataIdentifiers::NAV1_HAS_NAV;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.nav1_has_nav), sizeof(newData.nav1_has_nav));
    }
    if (d_lastPfdData.nav1_has_signal != newData.nav1_has_signal)
    {
        d_lastPfdData.nav1_has_signal = newData.nav1_has_signal;
        id = DataIdentifiers::NAV1_HAS_SIGNAL;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.nav1_has_signal), sizeof(newData.nav1_has_signal));
    }
    if (d_lastPfdData.nav1_has_dme != newData.nav1_has_dme)
    {
        d_lastPfdData.nav1_has_dme = newData.nav1_has_dme;
        id = DataIdentifiers::NAV1_HAS_DME;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.nav1_has_dme), sizeof(newData.nav1_has_dme));
    }

    //nav2
    if (fabs(d_lastPfdData.nav2_dme - newData.nav2_dme) >= 0.09)
    {
        d_lastPfdData.nav2_dme = newData.nav2_dme;
        id = DataIdentifiers::NAV2_DME;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.nav2_dme), sizeof(newData.nav2_dme));
    }
    if (fabs(d_lastPfdData.nav2_radial - newData.nav2_radial) >= 0.0009)
    {
        d_lastPfdData.nav2_radial = newData.nav2_radial;
        id = DataIdentifiers::NAV2_BEARING;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.nav2_radial), sizeof(newData.nav2_radial));
    }
    if (d_lastPfdData.nav2_has_nav != newData.nav2_has_nav)
    {
        d_lastPfdData.nav2_has_nav = newData.nav2_has_nav;
        id = DataIdentifiers::NAV2_HAS_NAV;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.nav2_has_nav), sizeof(newData.nav2_has_nav));
    }
    if (d_lastPfdData.nav2_has_signal != newData.nav2_has_signal)
    {
        d_lastPfdData.nav2_has_signal = newData.nav2_has_signal;
        id = DataIdentifiers::NAV2_HAS_SIGNAL;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.nav2_has_signal), sizeof(newData.nav2_has_signal));
    }
    if (d_lastPfdData.nav2_has_dme != newData.nav2_has_dme)
    {
        d_lastPfdData.nav2_has_dme = newData.nav2_has_dme;
        id = DataIdentifiers::NAV2_HAS_DME;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.nav2_has_dme), sizeof(newData.nav2_has_dme));
    }

    //gps
    if (fabs(d_lastPfdData.gps_next_wp_dist - newData.gps_next_wp_dist) >= 0.09)
    {
        d_lastPfdData.gps_next_wp_dist = newData.gps_next_wp_dist;
        id = DataIdentifiers::GPS_DISTANCE;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.gps_next_wp_dist), sizeof(newData.gps_next_wp_dist));
    }
    if (fabs(d_lastPfdData.gps_next_wp_bearing - newData.gps_next_wp_bearing) >= 0.0009)
    {
        d_lastPfdData.gps_next_wp_bearing = newData.gps_next_wp_bearing;
        id = DataIdentifiers::GPS_BEARING;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.gps_next_wp_bearing), sizeof(newData.gps_next_wp_bearing));
    }

    //adf
    if (d_lastPfdData.adf_has_signal != newData.adf_has_signal)
    {
        d_lastPfdData.adf_has_signal = newData.adf_has_signal;
        id = DataIdentifiers::ADF_HAS_SIGNAL;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.adf_has_signal), sizeof(newData.adf_has_signal));
    }
    if (fabs(d_lastPfdData.adf_active_freq - newData.adf_active_freq) >= 0.09)
    {
        d_lastPfdData.adf_active_freq = newData.adf_active_freq;
        id = DataIdentifiers::ADF_FREQ;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.adf_active_freq), sizeof(newData.adf_active_freq));
    }
    if (fabs(d_lastPfdData.adf_radial - newData.adf_radial) >= 0.0009)
    {
        d_lastPfdData.adf_radial = newData.adf_radial;
        id = DataIdentifiers::ADF_RADIAL;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.adf_radial), sizeof(newData.adf_radial));
    }


    //radio
    if (fabs(d_lastPfdData.com1_freq - newData.com1_freq) >= 0.001)
    {
        d_lastPfdData.com1_freq = newData.com1_freq;
        id = DataIdentifiers::COM1_FREQ;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.com1_freq), sizeof(newData.com1_freq));
    }
    if (fabs(d_lastPfdData.com2_freq - newData.com2_freq) >= 0.001)
    {
        d_lastPfdData.com2_freq = newData.com2_freq;
        id = DataIdentifiers::COM2_FREQ;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.com2_freq), sizeof(newData.com2_freq));
    }

    if (fabs(d_lastPfdData.nav1_freq - newData.nav1_freq) >= 0.009)
    {
        d_lastPfdData.nav1_freq = newData.nav1_freq;
        id = DataIdentifiers::NAV1_FREQ;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.nav1_freq), sizeof(newData.nav1_freq));
    }
    if (fabs(d_lastPfdData.nav2_freq - newData.nav2_freq) >= 0.009)
    {
        d_lastPfdData.nav2_freq = newData.nav2_freq;
        id = DataIdentifiers::NAV2_FREQ;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.nav2_freq), sizeof(newData.nav2_freq));
    }


    //nav info
    if (d_lastPfdData.gps_is_active_flightplan != newData.gps_is_active_flightplan)
    {
        d_lastPfdData.gps_is_active_flightplan = newData.gps_is_active_flightplan;
        id = DataIdentifiers::GPS_IS_ACTIVE_FLIGHTPLAN;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.gps_is_active_flightplan), sizeof(newData.gps_is_active_flightplan));
    }
    if (d_lastPfdData.gps_is_directto != newData.gps_is_directto)
    {
        d_lastPfdData.gps_is_directto = newData.gps_is_directto;
        id = DataIdentifiers::LEG_IS_DIRECT_TO;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.gps_is_directto), sizeof(newData.gps_is_directto));
    }


    if (d_lastPfdData.gps_wp_ete != newData.gps_wp_ete)
    {
        d_lastPfdData.gps_wp_ete = newData.gps_wp_ete;
        id = DataIdentifiers::GPS_WP_ETE;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.gps_wp_ete), sizeof(newData.gps_wp_ete));
    }

    if (d_lastPfdData.gps_ete != newData.gps_ete)
    {
        d_lastPfdData.gps_ete = newData.gps_ete;
        id = DataIdentifiers::GPS_ETE;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.gps_ete), sizeof(newData.gps_ete));
    }


    //wind
    if (fabs(d_lastPfdData.wind_velocity - newData.wind_velocity) >= 0.1)
    {
        d_lastPfdData.wind_velocity = newData.wind_velocity;
        id = DataIdentifiers::WIND_STRENGTH;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.wind_velocity), sizeof(newData.wind_velocity));
    }
    if (fabs(d_lastPfdData.wind_true_direction - newData.wind_true_direction) >= 0.1)
    {
        d_lastPfdData.wind_true_direction = newData.wind_true_direction;
        id = DataIdentifiers::WIND_TRUE_DIRECTION;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.wind_true_direction), sizeof(newData.wind_true_direction));
    }
    if (fabs(d_lastPfdData.wind_direction - newData.wind_direction) >= 0.1)
    {
        d_lastPfdData.wind_direction = newData.wind_direction;
        id = DataIdentifiers::WIND_DIRECTION;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.wind_direction), sizeof(newData.wind_direction));
    }


    //position
    id = DataIdentifiers::COORDINATES;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&newData.currLat), sizeof(newData.currLat));
    dataToSend.append(reinterpret_cast<char *>(&newData.currLon), sizeof(newData.currLon));





    //ap info
    if (d_lastSlowData.hasAp)
    {

        if (d_lastPfdData.ap_master != newData.ap_master)
        {
            d_lastPfdData.ap_master = newData.ap_master;
            id = DataIdentifiers::AP_STATUS;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData.ap_master), sizeof(newData.ap_master));
        }
        if (d_lastPfdData.ap_yaw_damper != newData.ap_yaw_damper)
        {
            d_lastPfdData.ap_yaw_damper = newData.ap_yaw_damper;
            id = DataIdentifiers::AP_YD_STATUS;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData.ap_yaw_damper), sizeof(newData.ap_yaw_damper));
        }

        QByteArray AP_VerticalActive = "";
        QByteArray AP_ModeReference = "";
        QByteArray AP_Armed = "";
        QByteArray AP_ArmedReference = "";
        QByteArray AP_LateralActive = "";
        QByteArray AP_LateralArmed = "";


        if (newData.ap_pitch_hold)
        {
            AP_VerticalActive = "PIT";
            AP_ModeReference = "";
        }
        else if(newData.ap_flc)
        {
            AP_VerticalActive = "PIT";
            AP_ModeReference = QByteArray::number(newData.ref_speed) + "KT";
        }
        else if(newData.ap_altitude_lock)
        {
            AP_VerticalActive = newData.ap_altitude_arm ? "ALTS" : "ALT";
            AP_ModeReference = QByteArray::number(newData.ref_altitude) + "FT";
        }
        else if(newData.ap_vertical_hold)
        {
            AP_VerticalActive = "VS";
            AP_ModeReference = QByteArray::number(newData.ref_vspeed) + "FPM";
        }
        else if(newData.ap_glideslope_active)
        {
            AP_VerticalActive = newData.gpsDrivesNav1 ? "GP" : "GS";
            AP_ModeReference = "";
        }
        else
        {
            AP_VerticalActive = "";
            AP_ModeReference = "";
        }


        if(newData.ap_altitude_arm)
        {
            AP_Armed = "ALT";
            AP_ArmedReference = "";
        }
        else if(newData.ap_glideslope_arm)
        {
            if (newData.gpsDrivesNav1)
            {
                AP_Armed = "V ALT";
                AP_ArmedReference = "GP";
            }
            else
            {
                AP_Armed = "GS";
                AP_ArmedReference = "";
            }
        }
        else if(newData.ap_vertical_hold)
        {
            AP_Armed = "ALTS";
            AP_ArmedReference = "";
        }
        else
        {
            AP_Armed = "";
            AP_ArmedReference = "";
        }


        if (newData.ap_wing_leveler)
        {
            AP_LateralActive = "LVL";
        }
        else if(newData.ap_bank_hold)
        {
            AP_LateralActive = "ROL";
        }
        else if(newData.ap_heading_lock)
        {
            AP_LateralActive = "HDG";
        }
        else if(newData.ap_nav1_lock)
        {
            if(newData.gpsDrivesNav1)
            {
                AP_LateralActive = "GPS";
            }
            else
            {
                if((newData.autopilot_nav_selected == 1 && newData.nav1_has_loc) || (newData.autopilot_nav_selected == 2 && newData.nav2_has_loc))
                {
                    AP_LateralActive = "LOC";
                }
                else
                {
                    AP_LateralActive = "VOR";
                }
            }
        }
        else if(newData.ap_backcourse_hold)
        {
            AP_LateralActive = "BC";
        }
        else if(newData.autopilot_approach_hold)
        {
            if (newData.gpsDrivesNav1)
            {
                AP_LateralActive = "GPS";
            }
            else
            {
                if((newData.autopilot_nav_selected == 1 && newData.nav1_has_loc) || (newData.autopilot_nav_selected == 2 && newData.nav2_has_loc))
                {
                    AP_LateralActive = "LOC";
                }
                else
                {
                    AP_LateralActive = "VOR";
                }
            }
        }
        else
        {
            AP_LateralActive = "";
        }


        if (newData.ap_heading_lock || newData.ap_wing_leveler)
        {
            if(newData.ap_nav1_lock)
            {
                if (newData.gpsDrivesNav1)
                {
                    AP_LateralArmed = "GPS";
                }
                else
                {
                    if((newData.autopilot_nav_selected == 1 && newData.nav1_has_loc) || (newData.autopilot_nav_selected == 2 && newData.nav2_has_loc))
                    {
                        AP_LateralArmed = "LOC";
                    }
                    else
                    {
                        AP_LateralArmed = "VOR";
                    }
                }
            }
            else if(newData.ap_backcourse_hold)
            {
                AP_LateralArmed = "BC";
            }
            else if(newData.autopilot_approach_hold)
            {
                if (newData.gpsDrivesNav1)
                {
                    AP_LateralArmed = "GPS";
                }
                else
                {
                    if((newData.autopilot_nav_selected == 1 && newData.nav1_has_loc) || (newData.autopilot_nav_selected == 2 && newData.nav2_has_loc))
                    {
                        AP_LateralArmed = "LOC";
                    }
                    else
                    {
                        AP_LateralArmed = "VOR";
                    }
                }
            }
            else
            {
                AP_LateralArmed = "";
            }
        }
        else
        {
            AP_LateralArmed = "";
        }


        uint8_t size = 0;

        if(d_lastAP_VerticalActive != AP_VerticalActive)
        {
            d_lastAP_VerticalActive = AP_VerticalActive;
            size = AP_VerticalActive.size();
            id = DataIdentifiers::AP_VERTICAL_ACTIVE;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
            dataToSend.append(AP_VerticalActive.constData(), size);
        }

        if (d_lastAP_ModeReference != AP_ModeReference)
        {
            d_lastAP_ModeReference = AP_ModeReference;
            size = AP_ModeReference.size();
            id = DataIdentifiers::AP_MODE_REFERENCE;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
            dataToSend.append(AP_ModeReference.constData(), size);
        }

        if (d_lastAP_Armed != AP_Armed)
        {
            d_lastAP_Armed = AP_Armed;
            size = AP_Armed.size();
            id = DataIdentifiers::AP_ARMED;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
            dataToSend.append(AP_Armed.constData(), size);
        }

        if (d_lastAP_ArmedReference != AP_ArmedReference)
        {
            d_lastAP_ArmedReference = AP_ArmedReference;
            size = AP_ArmedReference.size();
            id = DataIdentifiers::AP_ARMED_REFERENCE;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
            dataToSend.append(AP_ArmedReference.constData(), size);
        }

        if (d_lastAP_LateralActive != AP_LateralActive)
        {
            d_lastAP_LateralActive = AP_LateralActive;
            size = AP_LateralActive.size();
            id = DataIdentifiers::AP_LATERAL_ACTIVE;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
            dataToSend.append(AP_LateralActive.constData(), size);
        }

        if (d_lastAP_LateralArmed != AP_LateralArmed)
        {
            d_lastAP_LateralArmed = AP_LateralArmed;
            size = AP_LateralArmed.size();
            id = DataIdentifiers::AP_LATERAL_ARMED;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
            dataToSend.append(AP_LateralArmed.constData(), size);
        }



    }


    emit sendData(dataToSend);

}






