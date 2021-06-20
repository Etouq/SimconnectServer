#include "../simconnectthread.ih"



void SimconnectThread::handleSlowData(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData)
{
    SlowDatadefStruct newData(reinterpret_cast<SlowDatadefRawStruct *>(&pObjData->dwData));

    d_lastSlowData.fuelWeight = newData.fuelWeight;

    DataIdentifiers id = DataIdentifiers::FUEL_TEXT_DATA;
    QByteArray dataToSend(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&newData.totalFuelQty), sizeof(newData.totalFuelQty));
    dataToSend.append(reinterpret_cast<char *>(&newData.totalFuelFlow), sizeof(newData.totalFuelFlow));
    dataToSend.append(reinterpret_cast<char *>(&newData.groundSpeed), sizeof(newData.groundSpeed));

    if (d_lastSlowData.hasAp != newData.hasAp)
    {
        d_lastSlowData.hasAp = newData.hasAp;
        id = DataIdentifiers::AP_AVAILABLE;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.hasAp), sizeof(newData.hasAp));
        if (newData.hasAp)
            d_updateApInfo = true;
    }

    if (d_lastSlowData.hasCom1 != newData.hasCom1)
    {
        d_lastSlowData.hasCom1 = newData.hasCom1;
        id = DataIdentifiers::HAS_COM1;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.hasCom1), sizeof(newData.hasCom1));
    }

    if (d_lastSlowData.hasCom2 != newData.hasCom2)
    {
        d_lastSlowData.hasCom2 = newData.hasCom2;
        id = DataIdentifiers::HAS_COM2;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.hasCom2), sizeof(newData.hasCom2));
    }

    if (d_lastSlowData.hasNav1 != newData.hasNav1)
    {
        d_lastSlowData.hasNav1 = newData.hasNav1;
        id = DataIdentifiers::HAS_NAV1;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.hasNav1), sizeof(newData.hasNav1));
    }

    if (d_lastSlowData.hasNav2 != newData.hasNav2)
    {
        d_lastSlowData.hasNav2 = newData.hasNav2;
        id = DataIdentifiers::HAS_NAV2;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData.hasNav2), sizeof(newData.hasNav2));
    }


    emit sendData(dataToSend);

}



void SimconnectThread::sendBlankSlowData()
{
    SlowDatadefStruct blankData;

    DataIdentifiers id = DataIdentifiers::FUEL_TEXT_DATA;
    QByteArray dataToSend(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.totalFuelQty), sizeof(blankData.totalFuelQty));
    dataToSend.append(reinterpret_cast<char *>(&blankData.totalFuelFlow), sizeof(blankData.totalFuelFlow));
    dataToSend.append(reinterpret_cast<char *>(&blankData.groundSpeed), sizeof(blankData.groundSpeed));


    id = DataIdentifiers::AP_AVAILABLE;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.hasAp), sizeof(blankData.hasAp));

    id = DataIdentifiers::HAS_COM1;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.hasCom1), sizeof(blankData.hasCom1));

    id = DataIdentifiers::HAS_COM2;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.hasCom2), sizeof(blankData.hasCom2));

    id = DataIdentifiers::HAS_NAV1;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.hasNav1), sizeof(blankData.hasNav1));

    id = DataIdentifiers::HAS_NAV2;
    dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
    dataToSend.append(reinterpret_cast<char *>(&blankData.hasNav2), sizeof(blankData.hasNav2));

    emit sendData(dataToSend);
}













