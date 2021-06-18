#include "../simconnectthread.ih"


void SimconnectThread::handleWindData(const PfdWindStruct &newData)
{
    DataIdentifiers id = DataIdentifiers::WIND_STRENGTH;
    QByteArray dataToSend;

    if (fabs(d_lastWindData.wind_velocity - newData.wind_velocity) >= 0.1)
    {
        d_lastWindData.wind_velocity = newData.wind_velocity;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.wind_velocity), sizeof(newData.wind_velocity));
    }
    if (fabs(d_lastWindData.wind_true_direction - newData.wind_true_direction) >= 0.1)
    {
        d_lastWindData.wind_true_direction = newData.wind_true_direction;
        id = DataIdentifiers::WIND_TRUE_DIRECTION;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.wind_true_direction), sizeof(newData.wind_true_direction));
    }
    if (fabs(d_lastWindData.wind_direction - newData.wind_direction) >= 0.1)
    {
        d_lastWindData.wind_direction = newData.wind_direction;
        id = DataIdentifiers::WIND_DIRECTION;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.wind_direction), sizeof(newData.wind_direction));
    }


    if (!dataToSend.isEmpty())
        emit sendData(dataToSend);
}
