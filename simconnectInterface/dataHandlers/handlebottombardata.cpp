#include "../simconnectthread.ih"


void SimconnectThread::handleBottombarData(const PfdBottombarStruct &newData)
{
    DataIdentifiers id = DataIdentifiers::ALTITUDE;
    QByteArray dataToSend;


    if (d_lastBottombarData.zulu_seconds != newData.zulu_seconds)
    {
        d_lastBottombarData.zulu_seconds = newData.zulu_seconds;
        id = DataIdentifiers::ZULU_SECONDS;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.zulu_seconds), sizeof(newData.zulu_seconds));
    }
    if (d_lastBottombarData.local_seconds != newData.local_seconds)
    {
        d_lastBottombarData.local_seconds = newData.local_seconds;
        id = DataIdentifiers::LOCAL_SECONDS;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.local_seconds), sizeof(newData.local_seconds));
    }
    if (d_lastBottombarData.ground_speed != newData.ground_speed)
    {
        d_lastBottombarData.ground_speed = newData.ground_speed;
        id = DataIdentifiers::GROUND_SPEED;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.ground_speed), sizeof(newData.ground_speed));
    }
    if (fabs(d_lastBottombarData.total_air_temp - newData.total_air_temp) >= 0.25)
    {
        d_lastBottombarData.total_air_temp = newData.total_air_temp;
        id = DataIdentifiers::TOTAL_AIR_TEMP;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.total_air_temp), sizeof(newData.total_air_temp));
    }

    if (!dataToSend.isEmpty())
        emit sendData(dataToSend);
}
