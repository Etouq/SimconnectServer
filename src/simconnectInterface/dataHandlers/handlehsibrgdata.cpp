#include "../simconnectthread.ih"


void SimconnectThread::handleHsiBrgData(const PfdHsiBrgStruct &newData)
{
    SimconnectIds id = SimconnectIds::NAV1_DME;
    QByteArray dataToSend;


    // nav1
    if (fabs(d_lastHsiBrgData.nav1_dme - newData.nav1_dme) >= 0.09)
    {
        d_lastHsiBrgData.nav1_dme = newData.nav1_dme;
        id = SimconnectIds::NAV1_DME;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav1_dme),
                          sizeof(newData.nav1_dme));
    }
    if (fabs(d_lastHsiBrgData.nav1_radial - newData.nav1_radial) >= 0.0009)
    {
        d_lastHsiBrgData.nav1_radial = newData.nav1_radial;
        id = SimconnectIds::NAV1_BEARING;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav1_radial),
                          sizeof(newData.nav1_radial));
    }
    if (d_lastHsiBrgData.nav1_has_nav != newData.nav1_has_nav)
    {
        d_lastHsiBrgData.nav1_has_nav = newData.nav1_has_nav;
        id = SimconnectIds::NAV1_HAS_NAV;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav1_has_nav),
                          sizeof(newData.nav1_has_nav));
    }
    if (d_lastHsiBrgData.nav1_has_signal != newData.nav1_has_signal)
    {
        d_lastHsiBrgData.nav1_has_signal = newData.nav1_has_signal;
        id = SimconnectIds::NAV1_HAS_SIGNAL;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav1_has_signal),
                          sizeof(newData.nav1_has_signal));
    }
    if (d_lastHsiBrgData.nav1_has_dme != newData.nav1_has_dme)
    {
        d_lastHsiBrgData.nav1_has_dme = newData.nav1_has_dme;
        id = SimconnectIds::NAV1_HAS_DME;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav1_has_dme),
                          sizeof(newData.nav1_has_dme));
    }

    // nav2
    if (fabs(d_lastHsiBrgData.nav2_dme - newData.nav2_dme) >= 0.09)
    {
        d_lastHsiBrgData.nav2_dme = newData.nav2_dme;
        id = SimconnectIds::NAV2_DME;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav2_dme),
                          sizeof(newData.nav2_dme));
    }
    if (fabs(d_lastHsiBrgData.nav2_radial - newData.nav2_radial) >= 0.0009)
    {
        d_lastHsiBrgData.nav2_radial = newData.nav2_radial;
        id = SimconnectIds::NAV2_BEARING;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav2_radial),
                          sizeof(newData.nav2_radial));
    }
    if (d_lastHsiBrgData.nav2_has_nav != newData.nav2_has_nav)
    {
        d_lastHsiBrgData.nav2_has_nav = newData.nav2_has_nav;
        id = SimconnectIds::NAV2_HAS_NAV;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav2_has_nav),
                          sizeof(newData.nav2_has_nav));
    }
    if (d_lastHsiBrgData.nav2_has_signal != newData.nav2_has_signal)
    {
        d_lastHsiBrgData.nav2_has_signal = newData.nav2_has_signal;
        id = SimconnectIds::NAV2_HAS_SIGNAL;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav2_has_signal),
                          sizeof(newData.nav2_has_signal));
    }
    if (d_lastHsiBrgData.nav2_has_dme != newData.nav2_has_dme)
    {
        d_lastHsiBrgData.nav2_has_dme = newData.nav2_has_dme;
        id = SimconnectIds::NAV2_HAS_DME;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav2_has_dme),
                          sizeof(newData.nav2_has_dme));
    }

    // gps
    if (fabs(d_lastHsiBrgData.gps_next_wp_dist - newData.gps_next_wp_dist) >= 0.09)
    {
        d_lastHsiBrgData.gps_next_wp_dist = newData.gps_next_wp_dist;
        id = SimconnectIds::GPS_DISTANCE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.gps_next_wp_dist),
                          sizeof(newData.gps_next_wp_dist));
    }
    if (fabs(d_lastHsiBrgData.gps_next_wp_bearing - newData.gps_next_wp_bearing) >= 0.0009)
    {
        d_lastHsiBrgData.gps_next_wp_bearing = newData.gps_next_wp_bearing;
        id = SimconnectIds::GPS_BEARING;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.gps_next_wp_bearing),
                          sizeof(newData.gps_next_wp_bearing));
    }

    // adf
    if (d_lastHsiBrgData.adf_has_signal != newData.adf_has_signal)
    {
        d_lastHsiBrgData.adf_has_signal = newData.adf_has_signal;
        id = SimconnectIds::ADF_HAS_SIGNAL;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.adf_has_signal),
                          sizeof(newData.adf_has_signal));
    }
    if (fabs(d_lastHsiBrgData.adf_active_freq - newData.adf_active_freq) >= 0.09)
    {
        d_lastHsiBrgData.adf_active_freq = newData.adf_active_freq;
        id = SimconnectIds::ADF_FREQ;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.adf_active_freq),
                          sizeof(newData.adf_active_freq));
    }
    if (fabs(d_lastHsiBrgData.adf_radial - newData.adf_radial) >= 0.0009)
    {
        d_lastHsiBrgData.adf_radial = newData.adf_radial;
        id = SimconnectIds::ADF_RADIAL;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.adf_radial),
                          sizeof(newData.adf_radial));
    }


    if (!dataToSend.isEmpty())
        emit sendData(dataToSend);
}
