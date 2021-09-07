#include "../simconnectthread.ih"


void SimconnectThread::handleAttitudeData(const PfdAttitudeStruct &newData)
{
    SimconnectIds id = SimconnectIds::BANK;
    QByteArray dataToSend(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&newData.bank), sizeof(newData.bank));

    id = SimconnectIds::PITCH;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&newData.pitch), sizeof(newData.pitch));

    id = SimconnectIds::SLIPSKID;
    dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<const char *>(&newData.slipskid), sizeof(newData.slipskid));

    if (fabs(d_lastAttitudeData.angle_of_attack - newData.angle_of_attack) >= 0.25)
    {
        d_lastAttitudeData.angle_of_attack = newData.angle_of_attack;
        id = SimconnectIds::ANGLE_OF_ATTACK;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&d_lastAttitudeData.angle_of_attack),
                          sizeof(d_lastAttitudeData.angle_of_attack));
    }

    if (d_lastAttitudeData.fd_state != newData.fd_state)
    {
        d_lastAttitudeData.fd_state = newData.fd_state;
        id = SimconnectIds::AP_FD_STATUS;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.fd_state),
                          sizeof(newData.fd_state));
    }

    if (newData.fd_state)
    {
        id = SimconnectIds::FD_BANK;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.fd_bank),
                          sizeof(newData.fd_bank));

        id = SimconnectIds::FD_PITCH;
        dataToSend.append(reinterpret_cast<const char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<const char *>(&newData.fd_pitch),
                          sizeof(newData.fd_pitch));
    }

    emit sendData(dataToSend);
}
