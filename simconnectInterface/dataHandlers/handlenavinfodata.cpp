#include "../simconnectthread.ih"


void SimconnectThread::handleNavInfoData(const PfdNavInfoStruct &newData)
{

    SimconnectIds id = SimconnectIds::GPS_IS_ACTIVE_FLIGHTPLAN;
    QByteArray dataToSend;


    if (d_lastNavInfoData.gps_is_active_flightplan != newData.gps_is_active_flightplan)
    {
        d_lastNavInfoData.gps_is_active_flightplan = newData.gps_is_active_flightplan;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.gps_is_active_flightplan), sizeof(newData.gps_is_active_flightplan));
    }
    if (d_lastNavInfoData.gps_is_directto != newData.gps_is_directto)
    {
        d_lastNavInfoData.gps_is_directto = newData.gps_is_directto;
        id = SimconnectIds::LEG_IS_DIRECT_TO;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.gps_is_directto), sizeof(newData.gps_is_directto));
    }


    if (d_lastNavInfoData.gps_wp_ete != newData.gps_wp_ete)
    {
        d_lastNavInfoData.gps_wp_ete = newData.gps_wp_ete;
        id = SimconnectIds::GPS_WP_ETE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.gps_wp_ete), sizeof(newData.gps_wp_ete));
    }

    if (d_lastNavInfoData.gps_ete != newData.gps_ete)
    {
        d_lastNavInfoData.gps_ete = newData.gps_ete;
        id = SimconnectIds::GPS_ETE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.gps_ete), sizeof(newData.gps_ete));
    }


    if (!dataToSend.isEmpty())
        emit sendData(dataToSend);
}
