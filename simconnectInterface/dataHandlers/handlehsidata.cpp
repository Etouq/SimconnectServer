#include "../simconnectthread.ih"


void SimconnectThread::handleHsiData(const PfdHsiStruct &newData)
{
    DataIdentifiers id = DataIdentifiers::ROTATION;
    QByteArray dataToSend;


    if (fabs(d_lastHsiData.rotation - newData.rotation) >= 0.0009)
    {
        d_lastHsiData.rotation = newData.rotation;
        id = DataIdentifiers::ROTATION;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.rotation), sizeof(newData.rotation));
    }
    if (fabs(d_lastHsiData.heading - newData.heading) >= 0.0009)
    {
        d_lastHsiData.heading = newData.heading;
        id = DataIdentifiers::HEADING;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.heading), sizeof(newData.heading));
    }
    if (fabs(d_lastHsiData.turn_rate - newData.turn_rate) >= 0.0009)
    {
        d_lastHsiData.turn_rate = newData.turn_rate;
        id = DataIdentifiers::TURN_RATE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.turn_rate), sizeof(newData.turn_rate));
    }
    if (fabs(d_lastHsiData.current_track - newData.current_track) >= 0.0009)
    {
        d_lastHsiData.current_track = newData.current_track;
        id = DataIdentifiers::CURRENT_TRACK;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.current_track), sizeof(newData.current_track));
    }

    if (fabs(d_lastHsiData.gps_wp_desired_track - newData.gps_wp_desired_track) >= 0.009)
    {
        d_lastHsiData.gps_wp_desired_track = newData.gps_wp_desired_track;
        id = DataIdentifiers::GPS_WP_DTK;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.gps_wp_desired_track), sizeof(newData.gps_wp_desired_track));
    }

    id = DataIdentifiers::COORDINATES;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&newData.currLat), sizeof(newData.currLat));
    dataToSend.append(reinterpret_cast<const char *>(&newData.currLon), sizeof(newData.currLon));

    if (fabs(d_lastHsiData.true_heading - newData.true_heading) >= 0.0009)
    {
        d_lastHsiData.true_heading = newData.true_heading;
        id = DataIdentifiers::TRUE_HEADING;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.true_heading), sizeof(newData.true_heading));
    }


    int32_t cdiSource = 3;
    if (!newData.gpsDrivesNav1 || (newData.autopilot_approach_hold && newData.gps_approach_approach_type == 10))   // 10 = rnav
    {
        cdiSource = newData.autopilot_nav_selected;
    }
    switch (cdiSource)
    {
        case 1:   // nav1
        {
            if (d_lastDisplayDeviation != d_lastHsiData.nav1_has_nav)
            {
                d_lastDisplayDeviation = d_lastHsiData.nav1_has_nav;
                id = DataIdentifiers::DISPLAY_DEVIATION;
                dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiData.nav1_has_nav), sizeof(d_lastHsiData.nav1_has_nav));
            }
            if (newData.nav1_has_loc)
            {
                if (d_lastNavSource != 2)
                {
                    d_lastNavSource = 2;
                    id = DataIdentifiers::NAV_SOURCE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_lastNavSource), sizeof(d_lastNavSource));

                    // make sure all values get updated because of the modeswitch
                    d_lastCourseDeviation = newData.nav1_cdi + 5.0;
                }

                if (fabs(d_lastCourse - newData.nav1_loc) >= 0.0009)
                {
                    d_lastCourse = newData.nav1_loc;
                    id = DataIdentifiers::COURSE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&newData.nav1_loc), sizeof(newData.nav1_loc));
                }
            }
            else
            {
                if (d_lastNavSource != 1)
                {
                    d_lastNavSource = 1;
                    id = DataIdentifiers::NAV_SOURCE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_lastNavSource), sizeof(d_lastNavSource));

                    // make sure all values get updated because of the modeswitch
                    d_lastCourseDeviation = newData.nav1_cdi + 5.0;
                }

                if (fabs(d_lastCourse - newData.nav1_obs) >= 0.0009)
                {
                    d_lastCourse = newData.nav1_obs;
                    id = DataIdentifiers::COURSE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&newData.nav1_obs), sizeof(newData.nav1_obs));
                }
            }

            if (fabs(d_lastCourseDeviation - newData.nav1_cdi) >= 0.3)
            {
                d_lastCourseDeviation = newData.nav1_cdi;
                double deviation = newData.nav1_cdi / 127.0;
                id = DataIdentifiers::COURSE_DEVIATION;
                dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<const char *>(&deviation), sizeof(deviation));
            }

            if (d_lastToFrom != newData.nav1_to_from)
            {
                d_lastToFrom = newData.nav1_to_from;
                id = DataIdentifiers::TO_FROM;
                dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<const char *>(&newData.nav1_to_from), sizeof(newData.nav1_to_from));
            }
            break;
        }
        case 2:   // nav2
        {
            if (d_lastDisplayDeviation != d_lastHsiData.nav2_has_nav)
            {
                d_lastDisplayDeviation = d_lastHsiData.nav2_has_nav;
                id = DataIdentifiers::DISPLAY_DEVIATION;
                dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<const char *>(&d_lastHsiData.nav2_has_nav), sizeof(d_lastHsiData.nav2_has_nav));
            }

            if (newData.nav2_has_loc)
            {
                if (d_lastNavSource != 4)
                {
                    d_lastNavSource = 4;
                    id = DataIdentifiers::NAV_SOURCE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_lastNavSource), sizeof(d_lastNavSource));

                    // make sure all values get updated because of the modeswitch
                    d_lastCourseDeviation = newData.nav2_cdi + 5.0;
                }

                if (fabs(d_lastCourse - newData.nav2_loc) >= 0.0009)
                {
                    d_lastCourse = newData.nav2_loc;
                    id = DataIdentifiers::COURSE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&newData.nav2_loc), sizeof(newData.nav2_loc));
                }
            }
            else
            {
                if (d_lastNavSource != 3)
                {
                    d_lastNavSource = 3;
                    id = DataIdentifiers::NAV_SOURCE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_lastNavSource), sizeof(d_lastNavSource));

                    // make sure all values get updated because of the modeswitch
                    d_lastCourseDeviation = newData.nav2_cdi + 5.0;
                }

                if (fabs(d_lastCourse - newData.nav2_obs) >= 0.0009)
                {
                    d_lastCourse = newData.nav2_obs;
                    id = DataIdentifiers::COURSE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&newData.nav2_obs), sizeof(newData.nav2_obs));
                }
            }

            if (fabs(d_lastCourseDeviation - newData.nav2_cdi) >= 0.009)
            {
                d_lastCourseDeviation = newData.nav2_cdi;
                double deviation = newData.nav2_cdi / 127.0;
                id = DataIdentifiers::COURSE_DEVIATION;
                dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<const char *>(&deviation), sizeof(deviation));
            }

            if (d_lastToFrom != newData.nav2_to_from)
            {
                d_lastToFrom = newData.nav2_to_from;
                id = DataIdentifiers::TO_FROM;
                dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<const char *>(&newData.nav2_to_from), sizeof(newData.nav2_to_from));
            }
            break;
        }
        case 3:   // gps
        {
            if (d_lastNavSource != 0)
            {
                d_lastNavSource = 0;
                id = DataIdentifiers::NAV_SOURCE;
                dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<const char *>(&d_lastNavSource), sizeof(d_lastNavSource));

                // make sure all values get updated because of the modeswitch
                d_lastCourseDeviation = newData.gps_wp_cross_track + 5.0;
            }

            // should be implemented using 'gps_next_wp_id != ""'
            if (d_lastDisplayDeviation != (d_lastStringsData.gps_wp_next_id != ""))
            {
                d_lastDisplayDeviation = (d_lastStringsData.gps_wp_next_id != "");
                id = DataIdentifiers::DISPLAY_DEVIATION;
                dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<const char *>(&d_lastDisplayDeviation), sizeof(d_lastDisplayDeviation));
            }

            if (fabs(d_lastCourse - newData.gps_wp_desired_track) >= 0.0009)
            {
                d_lastCourse = newData.gps_wp_desired_track;
                id = DataIdentifiers::COURSE;
                dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<const char *>(&newData.gps_wp_desired_track), sizeof(newData.gps_wp_desired_track));
            }

            if (fabs(d_lastCourseDeviation - newData.gps_wp_cross_track) >= 0.3)
            {
                d_lastCourseDeviation = newData.gps_wp_cross_track;
                id = DataIdentifiers::COURSE_DEVIATION;
                dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<const char *>(&newData.gps_wp_cross_track), sizeof(newData.gps_wp_cross_track));
            }

            // maybe change to zero if preferred
            if (d_lastToFrom != 1)
            {
                d_lastToFrom = 1;
                id = DataIdentifiers::TO_FROM;
                dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<const char *>(&d_lastToFrom), sizeof(d_lastToFrom));
            }

            break;
        }
    }

    emit sendData(dataToSend);
}
