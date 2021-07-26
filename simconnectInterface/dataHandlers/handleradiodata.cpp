#include "../simconnectthread.ih"


void SimconnectThread::handleRadioData(const PfdRadioStruct &newData)
{
    SimconnectIds id = SimconnectIds::COM1_FREQ;
    QByteArray dataToSend;

    if (fabs(d_lastRadioData.com1_freq - newData.com1_freq) >= 0.001)
    {
        d_lastRadioData.com1_freq = newData.com1_freq;
        id = SimconnectIds::COM1_FREQ;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.com1_freq), sizeof(newData.com1_freq));
    }
    if (fabs(d_lastRadioData.com2_freq - newData.com2_freq) >= 0.001)
    {
        d_lastRadioData.com2_freq = newData.com2_freq;
        id = SimconnectIds::COM2_FREQ;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.com2_freq), sizeof(newData.com2_freq));
    }

    if (fabs(d_lastRadioData.nav1_freq - newData.nav1_freq) >= 0.009)
    {
        d_lastRadioData.nav1_freq = newData.nav1_freq;
        id = SimconnectIds::NAV1_FREQ;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav1_freq), sizeof(newData.nav1_freq));
    }
    if (fabs(d_lastRadioData.nav2_freq - newData.nav2_freq) >= 0.009)
    {
        d_lastRadioData.nav2_freq = newData.nav2_freq;
        id = SimconnectIds::NAV2_FREQ;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav2_freq), sizeof(newData.nav2_freq));
    }


    if (!dataToSend.isEmpty())
        emit sendData(dataToSend);
}
