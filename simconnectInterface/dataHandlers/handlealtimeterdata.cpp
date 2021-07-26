#include "../simconnectthread.ih"


void SimconnectThread::handleAltimeterData(const PfdAltimeterStruct &newData)
{
    SimconnectIds id = SimconnectIds::ALTITUDE;
    QByteArray dataToSend;

    if (fabs(d_lastAltimeterData.altitude - newData.altitude) >= 0.09)
    {
        d_lastAltimeterData.altitude = newData.altitude;
        id = SimconnectIds::ALTITUDE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.altitude), sizeof(newData.altitude));
    }

    if (fabs(d_lastAltimeterData.radar_altitude - newData.radar_altitude) >= 0.09)
    {
        d_lastAltimeterData.radar_altitude = newData.radar_altitude;
        id = SimconnectIds::RADAR_ALTITUDE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.radar_altitude), sizeof(newData.radar_altitude));
    }

    if (d_lastAltimeterData.ref_altitude != newData.ref_altitude)
    {
        d_lastAltimeterData.ref_altitude = newData.ref_altitude;
        id = SimconnectIds::REF_ALTITUDE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.ref_altitude), sizeof(newData.ref_altitude));
    }

    if (fabs(d_lastAltimeterData.pressure - newData.pressure) >= 0.009)
    {
        d_lastAltimeterData.pressure = newData.pressure;
        id = SimconnectIds::PRESSURE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.pressure), sizeof(newData.pressure));
    }


    if (fabs(d_lastAltimeterData.vspeed - newData.vspeed) >= 0.009)
    {
        d_lastAltimeterData.vspeed = newData.vspeed;
        id = SimconnectIds::VSPEED;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.vspeed), sizeof(newData.vspeed));
    }

    if (d_lastAltimeterData.ref_vspeed != newData.ref_vspeed)
    {
        d_lastAltimeterData.ref_vspeed = newData.ref_vspeed;
        id = SimconnectIds::REF_VSPEED;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.ref_vspeed), sizeof(newData.ref_vspeed));
    }


    int32_t cdiSource = newData.gpsDrivesNav1 ? 3 : newData.autopilot_nav_selected;
    switch (cdiSource)
    {
        case 1:   // nav1
        {
            if (newData.nav1_has_glideslope)
            {
                if (d_lastVertMode != 2)
                {
                    d_lastVertMode = 2;
                    id = SimconnectIds::VERT_DEV_MODE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_lastVertMode), sizeof(d_lastVertMode));

                    // make sure all other values get evaluated
                    d_lastAltimeterData.nav1_gsi = newData.nav1_gsi + 5.0;
                }
                if (fabs(d_lastAltimeterData.nav1_gsi - newData.nav1_gsi) >= 0.1)
                {
                    d_lastAltimeterData.nav1_gsi = newData.nav1_gsi;
                    double deviation = newData.nav1_gsi / 127.0;
                    id = SimconnectIds::VERT_DEV_VALUE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&deviation), sizeof(deviation));
                }
            }
            else
            {
                if (d_lastVertMode != 0)
                {
                    d_lastVertMode = 0;
                    id = SimconnectIds::VERT_DEV_MODE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_lastVertMode), sizeof(d_lastVertMode));
                }
            }
            break;
        }
        case 2:   // nav2
        {
            if (newData.nav2_has_glideslope)
            {
                if (d_lastVertMode != 2)
                {
                    d_lastVertMode = 2;
                    id = SimconnectIds::VERT_DEV_MODE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_lastVertMode), sizeof(d_lastVertMode));

                    // make sure all other values get evaluated
                    d_lastAltimeterData.nav2_gsi = newData.nav2_gsi + 5.0;
                }
                if (fabs(d_lastAltimeterData.nav2_gsi - newData.nav2_gsi) >= 0.1)
                {
                    d_lastAltimeterData.nav2_gsi = newData.nav2_gsi;
                    double deviation = newData.nav2_gsi / 127.0;
                    id = SimconnectIds::VERT_DEV_VALUE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&deviation), sizeof(deviation));
                }
            }
            else
            {
                if (d_lastVertMode != 0)
                {
                    d_lastVertMode = 0;
                    id = SimconnectIds::VERT_DEV_MODE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_lastVertMode), sizeof(d_lastVertMode));
                }
            }
            break;
        }
        case 3:   // gps
        {
            if (newData.gps_approach_active && newData.gps_approach_approach_type == 10)   // 10 = rnav
            {
                if (d_lastVertMode != 3)
                {
                    d_lastVertMode = 3;
                    id = SimconnectIds::VERT_DEV_MODE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_lastVertMode), sizeof(d_lastVertMode));

                    // make sure all other values get evaluated
                    d_lastAltimeterData.gps_vert_error = newData.gps_vert_error + 5.0;
                }
                if (fabs(d_lastAltimeterData.gps_vert_error - newData.gps_vert_error) >= 0.1)
                {
                    d_lastAltimeterData.gps_vert_error = newData.gps_vert_error;
                    double deviation = newData.gps_vert_error / 150.0;
                    id = SimconnectIds::VERT_DEV_VALUE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&deviation), sizeof(deviation));
                }
            }
            else if (newData.nav1_has_glideslope)
            {
                if (d_lastVertMode != 4)
                {
                    d_lastVertMode = 4;
                    id = SimconnectIds::VERT_DEV_MODE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_lastVertMode), sizeof(d_lastVertMode));

                    // make sure all other values get evaluated
                    d_lastAltimeterData.nav1_gsi = newData.nav1_gsi + 5.0;
                }
                if (fabs(d_lastAltimeterData.nav1_gsi - newData.nav1_gsi) >= 0.1)
                {
                    d_lastAltimeterData.nav1_gsi = newData.nav1_gsi;
                    double deviation = newData.nav1_gsi / 127.0;
                    id = SimconnectIds::VERT_DEV_VALUE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&deviation), sizeof(deviation));
                }
            }
            else if (newData.nav2_has_glideslope)
            {
                if (d_lastVertMode != 4)
                {
                    d_lastVertMode = 4;
                    id = SimconnectIds::VERT_DEV_MODE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_lastVertMode), sizeof(d_lastVertMode));

                    // make sure all other values get evaluated
                    d_lastAltimeterData.nav2_gsi = newData.nav2_gsi + 5.0;
                }
                if (fabs(d_lastAltimeterData.nav2_gsi - newData.nav2_gsi) >= 0.1)
                {
                    d_lastAltimeterData.nav2_gsi = newData.nav2_gsi;
                    double deviation = newData.nav2_gsi / 127.0;
                    id = SimconnectIds::VERT_DEV_VALUE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&deviation), sizeof(deviation));
                }
            }
            else
            {
                if (d_lastVertMode != 0)
                {
                    d_lastVertMode = 0;
                    id = SimconnectIds::VERT_DEV_MODE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_lastVertMode), sizeof(d_lastVertMode));
                }
            }

            break;
        }
    }


    if (!dataToSend.isEmpty())
        emit sendData(dataToSend);
}
