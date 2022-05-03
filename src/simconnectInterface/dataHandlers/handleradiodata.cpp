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
        dataToSend.append(reinterpret_cast<const char *>(&newData.com1_freq),
                          sizeof(newData.com1_freq));
    }
    if (fabs(d_lastRadioData.com2_freq - newData.com2_freq) >= 0.001)
    {
        d_lastRadioData.com2_freq = newData.com2_freq;
        id = SimconnectIds::COM2_FREQ;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.com2_freq),
                          sizeof(newData.com2_freq));
    }

    if (fabs(d_lastRadioData.nav1_freq - newData.nav1_freq) >= 0.009)
    {
        d_lastRadioData.nav1_freq = newData.nav1_freq;
        id = SimconnectIds::NAV1_FREQ;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav1_freq),
                          sizeof(newData.nav1_freq));
    }
    if (fabs(d_lastRadioData.nav2_freq - newData.nav2_freq) >= 0.009)
    {
        d_lastRadioData.nav2_freq = newData.nav2_freq;
        id = SimconnectIds::NAV2_FREQ;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav2_freq),
                          sizeof(newData.nav2_freq));
    }

    if (fabs(d_lastRadioData.com1_stby - newData.com1_stby) >= 0.001)
    {
        d_lastRadioData.com1_stby = newData.com1_stby;
        id = SimconnectIds::COM1_STBY;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.com1_stby),
                          sizeof(newData.com1_stby));
    }
    if (fabs(d_lastRadioData.com2_stby - newData.com2_stby) >= 0.001)
    {
        d_lastRadioData.com2_stby = newData.com2_stby;
        id = SimconnectIds::COM2_STBY;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.com2_stby),
                          sizeof(newData.com2_stby));
    }

    if (fabs(d_lastRadioData.nav1_stby - newData.nav1_stby) >= 0.009)
    {
        d_lastRadioData.nav1_stby = newData.nav1_stby;
        id = SimconnectIds::NAV1_STBY;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav1_stby),
                          sizeof(newData.nav1_stby));
    }
    if (fabs(d_lastRadioData.nav2_stby - newData.nav2_stby) >= 0.009)
    {
        d_lastRadioData.nav2_stby = newData.nav2_stby;
        id = SimconnectIds::NAV2_STBY;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.nav2_stby),
                          sizeof(newData.nav2_stby));
    }

    if (d_lastRadioData.xpdr_code != newData.xpdr_code)
    {
        d_lastRadioData.xpdr_code = newData.xpdr_code;
        id = SimconnectIds::XPDR_CODE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.xpdr_code),
                          sizeof(newData.xpdr_code));
    }

    if (d_lastRadioData.xpdr_state != newData.xpdr_state)
    {
        d_lastRadioData.xpdr_state = newData.xpdr_state;
        id = SimconnectIds::XPDR_STATE;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.xpdr_state),
                          sizeof(newData.xpdr_state));
    }


    if (!dataToSend.isEmpty())
        emit sendData(dataToSend);
}
