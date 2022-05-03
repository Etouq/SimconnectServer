#include "simconnectthread.ih"

void SimconnectThread::sendBlankEngineData()
{
    double value = 0.0;
    SimconnectIds id = SimconnectIds::ENGINE1_N1;
    QByteArray dataToSend(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));

    id = SimconnectIds::ENGINE2_N1;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));

    id = SimconnectIds::ENGINE3_N1;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));

    id = SimconnectIds::ENGINE4_N1;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));


    id = SimconnectIds::ENGINE1_N2;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));

    id = SimconnectIds::ENGINE2_N2;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));

    id = SimconnectIds::ENGINE3_N2;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));

    id = SimconnectIds::ENGINE4_N2;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));


    id = SimconnectIds::ENGINE1_ITT;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));

    id = SimconnectIds::ENGINE2_ITT;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));

    id = SimconnectIds::ENGINE3_ITT;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));

    id = SimconnectIds::ENGINE4_ITT;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));


    id = SimconnectIds::ENGINE1_RPM;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));

    id = SimconnectIds::ENGINE2_RPM;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));


    id = SimconnectIds::ENGINE1_SECOND;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));

    id = SimconnectIds::ENGINE2_SECOND;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));


    id = SimconnectIds::ENGINE1_TRQ;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));

    id = SimconnectIds::ENGINE2_TRQ;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));


    id = SimconnectIds::ENGINE1_FUEL_QTY;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));

    id = SimconnectIds::ENGINE2_FUEL_QTY;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));


    id = SimconnectIds::ENGINE1_FUEL_FLOW;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));

    id = SimconnectIds::ENGINE2_FUEL_FLOW;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));


    id = SimconnectIds::ENGINE1_OIL_PRESS;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));

    id = SimconnectIds::ENGINE2_OIL_PRESS;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));


    id = SimconnectIds::ENGINE1_OIL_TEMP;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));

    id = SimconnectIds::ENGINE2_OIL_TEMP;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));


    id = SimconnectIds::ENGINE1_EGT;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));

    id = SimconnectIds::ENGINE2_EGT;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));


    id = SimconnectIds::SPOILERS_PCT;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));

    id = SimconnectIds::FLAPS_ANGLE;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));

    id = SimconnectIds::ELEV_TRIM_PCT;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));

    id = SimconnectIds::RUDD_TRIM_PCT;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));

    id = SimconnectIds::AIL_TRIM_PCT;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));

    int32_t intVal = 0;
    id = SimconnectIds::APU_RPM_PCT;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&intVal), sizeof(intVal));

    emit sendData(dataToSend);
}
