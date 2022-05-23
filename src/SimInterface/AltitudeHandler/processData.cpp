#include "../SimInterface.hpp"
#include "AltitudeHandler.hpp"
#include "common/dataIdentifiers.hpp"

#include <cmath>

void AltitudeHandler::processData(unsigned long *raw)
{
    DataStruct newData(reinterpret_cast<RawStruct *>(raw));
    SimconnectIds id = SimconnectIds::ALTITUDE;
    QByteArray dataToSend;

    if (std::abs(d_previous.altitude - newData.altitude) >= 0.09)
    {
        d_previous.altitude = newData.altitude;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.altitude), sizeof(newData.altitude));
    }

    if (std::abs(d_previous.radar_altitude - newData.radar_altitude) >= 0.09)
    {
        d_previous.radar_altitude = newData.radar_altitude;
        id = SimconnectIds::RADAR_ALTITUDE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.radar_altitude), sizeof(newData.radar_altitude));
    }

    if (d_previous.ref_altitude != newData.ref_altitude)
    {
        d_previous.ref_altitude = newData.ref_altitude;
        id = SimconnectIds::REF_ALTITUDE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.ref_altitude), sizeof(newData.ref_altitude));
    }

    if (std::abs(d_previous.pressure - newData.pressure) >= 0.009)
    {
        d_previous.pressure = newData.pressure;
        id = SimconnectIds::PRESSURE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.pressure), sizeof(newData.pressure));
    }


    if (std::abs(d_previous.vspeed - newData.vspeed) >= 0.009)
    {
        d_previous.vspeed = newData.vspeed;
        id = SimconnectIds::VSPEED;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.vspeed), sizeof(newData.vspeed));
    }

    if (d_previous.ref_vspeed != newData.ref_vspeed)
    {
        d_previous.ref_vspeed = newData.ref_vspeed;
        id = SimconnectIds::REF_VSPEED;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.ref_vspeed), sizeof(newData.ref_vspeed));
    }


    int32_t cdiSource = newData.gpsDrivesNav1 ? 3 : newData.autopilot_nav_selected;
    switch (cdiSource)
    {
        case 1:  // nav1
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
                    d_previous.nav1_gsi = newData.nav1_gsi + 5.0;
                }
                if (std::abs(d_previous.nav1_gsi - newData.nav1_gsi) >= 0.1)
                {
                    d_previous.nav1_gsi = newData.nav1_gsi;
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
        case 2:  // nav2
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
                    d_previous.nav2_gsi = newData.nav2_gsi + 5.0;
                }
                if (std::abs(d_previous.nav2_gsi - newData.nav2_gsi) >= 0.1)
                {
                    d_previous.nav2_gsi = newData.nav2_gsi;
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
        case 3:  // gps
        {
            if (newData.gps_approach_active && newData.gps_approach_approach_type == 10)  // 10 = rnav
            {
                if (d_lastVertMode != 3)
                {
                    d_lastVertMode = 3;
                    id = SimconnectIds::VERT_DEV_MODE;
                    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                    dataToSend.append(reinterpret_cast<const char *>(&d_lastVertMode), sizeof(d_lastVertMode));

                    // make sure all other values get evaluated
                    d_previous.gps_vert_error = newData.gps_vert_error + 5.0;
                }
                if (std::abs(d_previous.gps_vert_error - newData.gps_vert_error) >= 0.1)
                {
                    d_previous.gps_vert_error = newData.gps_vert_error;
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
                    d_previous.nav1_gsi = newData.nav1_gsi + 5.0;
                }
                if (std::abs(d_previous.nav1_gsi - newData.nav1_gsi) >= 0.1)
                {
                    d_previous.nav1_gsi = newData.nav1_gsi;
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
                    d_previous.nav2_gsi = newData.nav2_gsi + 5.0;
                }
                if (std::abs(d_previous.nav2_gsi - newData.nav2_gsi) >= 0.1)
                {
                    d_previous.nav2_gsi = newData.nav2_gsi;
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
        default:
        {
            if (d_lastVertMode != 0)
            {
                d_lastVertMode = 0;
                id = SimconnectIds::VERT_DEV_MODE;
                dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<const char *>(&d_lastVertMode), sizeof(d_lastVertMode));

                double deviation = 0.0;
                id = SimconnectIds::VERT_DEV_VALUE;
                dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<const char *>(&deviation), sizeof(deviation));
            }
        }
    }


    if (!dataToSend.isEmpty())
        emit d_parent->sendData(dataToSend);
}
