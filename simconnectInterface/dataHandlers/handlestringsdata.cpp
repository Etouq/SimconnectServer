#include "../simconnectthread.ih"

void SimconnectThread::handleStringsData(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData)
{
    StringsDataStruct newData(reinterpret_cast<StringsRawDataStruct *>(&pObjData->dwData));

    SimconnectIds id = SimconnectIds::CURRENT_LEG_TO;

    QByteArray dataToSend = "";
    uint8_t size = 0;

    if (d_lastStringsData.gps_wp_next_id != newData.gps_wp_next_id)
    {
        d_lastStringsData.gps_wp_next_id = newData.gps_wp_next_id;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        size = newData.gps_wp_next_id.size();
        dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
        dataToSend.append(newData.gps_wp_next_id.constData(), size);
    }

    if (d_lastStringsData.nav1_ident != newData.nav1_ident)
    {
        d_lastStringsData.nav1_ident = newData.nav1_ident;
        id = SimconnectIds::NAV1_IDENT;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        size = newData.nav1_ident.size();
        dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
        dataToSend.append(newData.nav1_ident.constData(), size);
    }

    if (d_lastStringsData.nav2_ident != newData.nav2_ident)
    {
        d_lastStringsData.nav2_ident = newData.nav2_ident;
        id = SimconnectIds::NAV2_IDENT;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        size = newData.nav2_ident.size();
        dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
        dataToSend.append(newData.nav2_ident.constData(), size);
    }

    if (d_lastStringsData.gps_wp_prev_id != newData.gps_wp_prev_id)
    {
        d_lastStringsData.gps_wp_prev_id = newData.gps_wp_prev_id;
        id = SimconnectIds::CURRENT_LEG_FROM;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        size = newData.gps_wp_prev_id.size();
        dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
        dataToSend.append(newData.gps_wp_prev_id.constData(), size);
    }

    emit sendData(dataToSend);
}

void SimconnectThread::sendBlankStringsData()
{
    StringsDataStruct blankData;

    SimconnectIds id = SimconnectIds::CURRENT_LEG_TO;
    QByteArray dataToSend(reinterpret_cast<char *>(&id), sizeof(id));
    uint8_t size = 0;
    size = blankData.gps_wp_next_id.size();
    dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
    dataToSend.append(blankData.gps_wp_next_id.constData(), size);


    id = SimconnectIds::NAV1_IDENT;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    size = blankData.nav1_ident.size();
    dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
    dataToSend.append(blankData.nav1_ident.constData(), size);

    id = SimconnectIds::NAV2_IDENT;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    size = blankData.nav2_ident.size();
    dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
    dataToSend.append(blankData.nav2_ident.constData(), size);

    id = SimconnectIds::CURRENT_LEG_FROM;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    size = blankData.gps_wp_prev_id.size();
    dataToSend.append(reinterpret_cast<char *>(&size), sizeof(size));
    dataToSend.append(blankData.gps_wp_prev_id.constData(), size);

    emit sendData(dataToSend);
}
