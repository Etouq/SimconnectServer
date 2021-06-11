#include "../simconnectthread.ih"

void SimconnectThread::handleJetSingleEngdata(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData)
{
    JetData *newData = reinterpret_cast<JetData *>(&pObjData->dwData);
    QByteArray dataToSend;
    DataIdentifiers id;

    //n1
    if(fabs(d_lastJetData.engine1N1 - newData->engine1N1) >= d_currentAirplaneSettings.n1Epsilon)
    {
        d_lastJetData.engine1N1 = newData->engine1N1;
        id = DataIdentifiers::ENGINE1_N1;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1N1), sizeof(newData->engine1N1));
    }

    //n2
    if(fabs(d_lastJetData.engine1N2 - newData->engine1N2) >= d_currentAirplaneSettings.n2Epsilon)
    {
        d_lastJetData.engine1N2 = newData->engine1N2;
        id = DataIdentifiers::ENGINE1_N2;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1N2), sizeof(newData->engine1N2));
    }

    //itt
    if(fabs(d_lastJetData.engine1Itt - newData->engine1Itt) >= d_currentAirplaneSettings.ittEpsilon)
    {
        d_lastJetData.engine1Itt = newData->engine1Itt;
        id = DataIdentifiers::ENGINE1_ITT;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1Itt), sizeof(newData->engine1Itt));
    }

    //fuel qty
    if (d_currentAirplaneSettings.numTanks == 1)
    {
        if(fabs(d_lastJetData.commonData.fuelQtyTotal - newData->commonData.fuelQtyTotal) >= d_currentAirplaneSettings.fuelQtyEpsilon)
        {
            d_lastJetData.commonData.fuelQtyTotal = newData->commonData.fuelQtyTotal;

            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyTotal *= d_lastSlowData.fuelWeight;

            id = DataIdentifiers::ENGINE1_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyTotal), sizeof(newData->commonData.fuelQtyTotal));
        }
    }
    else
    {
        if(fabs(d_lastJetData.commonData.fuelQtyLeft - newData->commonData.fuelQtyLeft) >= d_currentAirplaneSettings.fuelQtyEpsilon)
        {
            d_lastJetData.commonData.fuelQtyLeft = newData->commonData.fuelQtyLeft;

            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyLeft *= d_lastSlowData.fuelWeight;

            id = DataIdentifiers::ENGINE1_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyLeft), sizeof(newData->commonData.fuelQtyLeft));
        }
        if(fabs(d_lastJetData.commonData.fuelQtyRight - newData->commonData.fuelQtyRight) >= d_currentAirplaneSettings.fuelQtyEpsilon)
        {
            d_lastJetData.commonData.fuelQtyRight = newData->commonData.fuelQtyRight;

            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyRight *= d_lastSlowData.fuelWeight;

            id = DataIdentifiers::ENGINE2_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyRight), sizeof(newData->commonData.fuelQtyRight));
        }
    }

    //fuel flow
    if(fabs(d_lastJetData.commonData.engine1FuelFlow - newData->commonData.engine1FuelFlow) >= d_currentAirplaneSettings.fuelFlowEpsilon)
    {
        d_lastJetData.commonData.engine1FuelFlow = newData->commonData.engine1FuelFlow;

        if (!d_currentAirplaneSettings.fuelFlowByVolume)
            newData->commonData.engine1FuelFlow *= 3600.0;

        id = DataIdentifiers::ENGINE1_FUEL_FLOW;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1FuelFlow), sizeof(newData->commonData.engine1FuelFlow));
    }

    //oil temp
    if(fabs(d_lastJetData.commonData.engine1OilTemp - newData->commonData.engine1OilTemp) >= d_currentAirplaneSettings.oilTempEpsilon)
    {
        d_lastJetData.commonData.engine1OilTemp = newData->commonData.engine1OilTemp;
        id = DataIdentifiers::ENGINE1_OIL_TEMP;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1OilTemp), sizeof(newData->commonData.engine1OilTemp));
    }

    //oil press
    if(fabs(d_lastJetData.commonData.engine1OilPress - newData->commonData.engine1OilPress) >= d_currentAirplaneSettings.oilPressEpsilon)
    {
        d_lastJetData.commonData.engine1OilPress = newData->commonData.engine1OilPress;
        id = DataIdentifiers::ENGINE1_OIL_PRESS;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1OilPress), sizeof(newData->commonData.engine1OilPress));
    }

    //apu
    if (d_currentAirplaneSettings.hasApu)
        if (lround(d_lastJetData.commonData.apuRpmPct) != lround(newData->commonData.apuRpmPct))
        {
            d_lastJetData.commonData.apuRpmPct = newData->commonData.apuRpmPct;
            int32_t value = lround(newData->commonData.apuRpmPct);
            id = DataIdentifiers::APU_RPM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));
        }

    //flaps\spoilers
    if (d_currentAirplaneSettings.hasFlaps)
    {
        //flaps
        if (fabs(d_lastJetData.commonData.flapsLeftAngle + d_lastJetData.commonData.flapsRightAngle - newData->commonData.flapsLeftAngle - newData->commonData.flapsRightAngle) >= 1.0)
        {
            d_lastJetData.commonData.flapsLeftAngle = newData->commonData.flapsLeftAngle;
            d_lastJetData.commonData.flapsRightAngle = newData->commonData.flapsRightAngle;

            newData->commonData.flapsRightAngle = (newData->commonData.flapsLeftAngle + newData->commonData.flapsRightAngle) / 2.0;
            id = DataIdentifiers::FLAPS_ANGLE;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.flapsRightAngle), sizeof(newData->commonData.flapsRightAngle));
        }

        //spoilers
        if (d_currentAirplaneSettings.hasSpoilers)
            if (fabs(d_lastJetData.commonData.spoilersLeftPct + d_lastJetData.commonData.spoilersRightPct - newData->commonData.spoilersLeftPct - newData->commonData.spoilersRightPct) >= 1.0)
            {
                d_lastJetData.commonData.spoilersLeftPct = newData->commonData.spoilersLeftPct;
                d_lastJetData.commonData.spoilersRightPct = newData->commonData.spoilersRightPct;

                newData->commonData.spoilersRightPct = (newData->commonData.spoilersLeftPct + newData->commonData.spoilersRightPct) / 2.0;
                id = DataIdentifiers::SPOILERS_PCT;
                dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<char *>(&newData->commonData.spoilersRightPct), sizeof(newData->commonData.spoilersRightPct));
            }
    }

    //elev trim
    if (d_currentAirplaneSettings.hasElevTrim)
        if (fabs(d_lastJetData.commonData.elevTrimPct - newData->commonData.elevTrimPct) >= 0.002)
        {
            d_lastJetData.commonData.elevTrimPct = newData->commonData.elevTrimPct;
            id = DataIdentifiers::ELEV_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.elevTrimPct), sizeof(newData->commonData.elevTrimPct));
        }

    //rudder trim
    if (d_currentAirplaneSettings.hasRudderTrim)
        if (fabs(d_lastJetData.commonData.rudderTrimPct - newData->commonData.rudderTrimPct) >= 0.002)
        {
            d_lastJetData.commonData.rudderTrimPct = newData->commonData.rudderTrimPct;
            id = DataIdentifiers::RUDD_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.rudderTrimPct), sizeof(newData->commonData.rudderTrimPct));
        }

    //aileron trim
    if (d_currentAirplaneSettings.hasAileronTrim)
        if (fabs(d_lastJetData.commonData.aileronTrimPct - newData->commonData.aileronTrimPct) >= 0.002)
        {
            d_lastJetData.commonData.aileronTrimPct = newData->commonData.aileronTrimPct;
            id = DataIdentifiers::AIL_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.aileronTrimPct), sizeof(newData->commonData.aileronTrimPct));
        }

    if (!dataToSend.isEmpty())
        emit sendData(dataToSend);
}

void SimconnectThread::handleJetTwinEngdata(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData)
{
    JetData *newData = reinterpret_cast<JetData *>(&pObjData->dwData);
    QByteArray dataToSend;
    DataIdentifiers id;

    //n1
    if(fabs(d_lastJetData.engine1N1 - newData->engine1N1) >= d_currentAirplaneSettings.n1Epsilon)
    {
        d_lastJetData.engine1N1 = newData->engine1N1;
        id = DataIdentifiers::ENGINE1_N1;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1N1), sizeof(newData->engine1N1));
    }
    if(fabs(d_lastJetData.engine2N1 - newData->engine2N1) >= d_currentAirplaneSettings.n1Epsilon)
    {
        d_lastJetData.engine2N1 = newData->engine2N1;
        id = DataIdentifiers::ENGINE2_N1;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine2N1), sizeof(newData->engine2N1));
    }

    //n2
    if(fabs(d_lastJetData.engine1N2 - newData->engine1N2) >= d_currentAirplaneSettings.n2Epsilon)
    {
        d_lastJetData.engine1N2 = newData->engine1N2;
        id = DataIdentifiers::ENGINE1_N2;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1N2), sizeof(newData->engine1N2));
    }
    if(fabs(d_lastJetData.engine2N2 - newData->engine2N2) >= d_currentAirplaneSettings.n2Epsilon)
    {
        d_lastJetData.engine2N2 = newData->engine2N2;
        id = DataIdentifiers::ENGINE2_N2;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine2N2), sizeof(newData->engine2N2));
    }

    //itt
    if(fabs(d_lastJetData.engine1Itt - newData->engine1Itt) >= d_currentAirplaneSettings.ittEpsilon)
    {
        d_lastJetData.engine1Itt = newData->engine1Itt;
        id = DataIdentifiers::ENGINE1_ITT;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1Itt), sizeof(newData->engine1Itt));
    }
    if(fabs(d_lastJetData.engine2Itt - newData->engine2Itt) >= d_currentAirplaneSettings.ittEpsilon)
    {
        d_lastJetData.engine2Itt = newData->engine2Itt;
        id = DataIdentifiers::ENGINE2_ITT;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine2Itt), sizeof(newData->engine2Itt));
    }

    //fuel qty
    if (d_currentAirplaneSettings.numTanks == 1)
    {
        if(fabs(d_lastJetData.commonData.fuelQtyTotal - newData->commonData.fuelQtyTotal) >= d_currentAirplaneSettings.fuelQtyEpsilon)
        {
            d_lastJetData.commonData.fuelQtyTotal = newData->commonData.fuelQtyTotal;

            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyTotal *= d_lastSlowData.fuelWeight;

            id = DataIdentifiers::ENGINE1_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyTotal), sizeof(newData->commonData.fuelQtyTotal));
        }
    }
    else
    {
        if(fabs(d_lastJetData.commonData.fuelQtyLeft - newData->commonData.fuelQtyLeft) >= d_currentAirplaneSettings.fuelQtyEpsilon)
        {
            d_lastJetData.commonData.fuelQtyLeft = newData->commonData.fuelQtyLeft;

            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyLeft *= d_lastSlowData.fuelWeight;

            id = DataIdentifiers::ENGINE1_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyLeft), sizeof(newData->commonData.fuelQtyLeft));
        }
        if(fabs(d_lastJetData.commonData.fuelQtyRight - newData->commonData.fuelQtyRight) >= d_currentAirplaneSettings.fuelQtyEpsilon)
        {
            d_lastJetData.commonData.fuelQtyRight = newData->commonData.fuelQtyRight;

            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyRight *= d_lastSlowData.fuelWeight;

            id = DataIdentifiers::ENGINE2_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyRight), sizeof(newData->commonData.fuelQtyRight));
        }
    }

    //fuel flow
    if(fabs(d_lastJetData.commonData.engine1FuelFlow - newData->commonData.engine1FuelFlow) >= d_currentAirplaneSettings.fuelFlowEpsilon)
    {
        d_lastJetData.commonData.engine1FuelFlow = newData->commonData.engine1FuelFlow;

        if (!d_currentAirplaneSettings.fuelFlowByVolume)
            newData->commonData.engine1FuelFlow *= 3600.0;

        id = DataIdentifiers::ENGINE1_FUEL_FLOW;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1FuelFlow), sizeof(newData->commonData.engine1FuelFlow));
    }
    if(fabs(d_lastJetData.commonData.engine2FuelFlow - newData->commonData.engine2FuelFlow) >= d_currentAirplaneSettings.fuelFlowEpsilon)
    {
        d_lastJetData.commonData.engine2FuelFlow = newData->commonData.engine2FuelFlow;

        if (!d_currentAirplaneSettings.fuelFlowByVolume)
            newData->commonData.engine2FuelFlow *= 3600.0;

        id = DataIdentifiers::ENGINE2_FUEL_FLOW;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine2FuelFlow), sizeof(newData->commonData.engine2FuelFlow));
    }

    //oil temp
    if(fabs(d_lastJetData.commonData.engine1OilTemp - newData->commonData.engine1OilTemp) >= d_currentAirplaneSettings.oilTempEpsilon)
    {
        d_lastJetData.commonData.engine1OilTemp = newData->commonData.engine1OilTemp;
        id = DataIdentifiers::ENGINE1_OIL_TEMP;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1OilTemp), sizeof(newData->commonData.engine1OilTemp));
    }
    if(fabs(d_lastJetData.commonData.engine2OilTemp - newData->commonData.engine2OilTemp) >= d_currentAirplaneSettings.oilTempEpsilon)
    {
        d_lastJetData.commonData.engine2OilTemp = newData->commonData.engine2OilTemp;
        id = DataIdentifiers::ENGINE2_OIL_TEMP;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine2OilTemp), sizeof(newData->commonData.engine2OilTemp));
    }

    //oil press
    if(fabs(d_lastJetData.commonData.engine1OilPress - newData->commonData.engine1OilPress) >= d_currentAirplaneSettings.oilPressEpsilon)
    {
        d_lastJetData.commonData.engine1OilPress = newData->commonData.engine1OilPress;
        id = DataIdentifiers::ENGINE1_OIL_PRESS;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1OilPress), sizeof(newData->commonData.engine1OilPress));
    }
    if(fabs(d_lastJetData.commonData.engine2OilPress - newData->commonData.engine2OilPress) >= d_currentAirplaneSettings.oilPressEpsilon)
    {
        d_lastJetData.commonData.engine2OilPress = newData->commonData.engine2OilPress;
        id = DataIdentifiers::ENGINE2_OIL_PRESS;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine2OilPress), sizeof(newData->commonData.engine2OilPress));
    }

    //apu
    if (d_currentAirplaneSettings.hasApu)
        if (lround(d_lastJetData.commonData.apuRpmPct) != lround(newData->commonData.apuRpmPct))
        {
            d_lastJetData.commonData.apuRpmPct = newData->commonData.apuRpmPct;
            int32_t value = lround(newData->commonData.apuRpmPct);
            id = DataIdentifiers::APU_RPM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));
        }

    //flaps\spoilers
    if (d_currentAirplaneSettings.hasFlaps)
    {
        //flaps
        if (fabs(d_lastJetData.commonData.flapsLeftAngle + d_lastJetData.commonData.flapsRightAngle - newData->commonData.flapsLeftAngle - newData->commonData.flapsRightAngle) >= 1.0)
        {
            d_lastJetData.commonData.flapsLeftAngle = newData->commonData.flapsLeftAngle;
            d_lastJetData.commonData.flapsRightAngle = newData->commonData.flapsRightAngle;

            newData->commonData.flapsRightAngle = (newData->commonData.flapsLeftAngle + newData->commonData.flapsRightAngle) / 2.0;
            id = DataIdentifiers::FLAPS_ANGLE;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.flapsRightAngle), sizeof(newData->commonData.flapsRightAngle));
        }

        //spoilers
        if (d_currentAirplaneSettings.hasSpoilers)
            if (fabs(d_lastJetData.commonData.spoilersLeftPct + d_lastJetData.commonData.spoilersRightPct - newData->commonData.spoilersLeftPct - newData->commonData.spoilersRightPct) >= 1.0)
            {
                d_lastJetData.commonData.spoilersLeftPct = newData->commonData.spoilersLeftPct;
                d_lastJetData.commonData.spoilersRightPct = newData->commonData.spoilersRightPct;

                newData->commonData.spoilersRightPct = (newData->commonData.spoilersLeftPct + newData->commonData.spoilersRightPct) / 2.0;
                id = DataIdentifiers::SPOILERS_PCT;
                dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<char *>(&newData->commonData.spoilersRightPct), sizeof(newData->commonData.spoilersRightPct));
            }
    }

    //elev trim
    if (d_currentAirplaneSettings.hasElevTrim)
        if (fabs(d_lastJetData.commonData.elevTrimPct - newData->commonData.elevTrimPct) >= 0.002)
        {
            d_lastJetData.commonData.elevTrimPct = newData->commonData.elevTrimPct;
            id = DataIdentifiers::ELEV_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.elevTrimPct), sizeof(newData->commonData.elevTrimPct));
        }

    //rudder trim
    if (d_currentAirplaneSettings.hasRudderTrim)
        if (fabs(d_lastJetData.commonData.rudderTrimPct - newData->commonData.rudderTrimPct) >= 0.002)
        {
            d_lastJetData.commonData.rudderTrimPct = newData->commonData.rudderTrimPct;
            id = DataIdentifiers::RUDD_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.rudderTrimPct), sizeof(newData->commonData.rudderTrimPct));
        }

    //aileron trim
    if (d_currentAirplaneSettings.hasAileronTrim)
        if (fabs(d_lastJetData.commonData.aileronTrimPct - newData->commonData.aileronTrimPct) >= 0.002)
        {
            d_lastJetData.commonData.aileronTrimPct = newData->commonData.aileronTrimPct;
            id = DataIdentifiers::AIL_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.aileronTrimPct), sizeof(newData->commonData.aileronTrimPct));
        }

    if (!dataToSend.isEmpty())
        emit sendData(dataToSend);
}

void SimconnectThread::handleJetQuadEngdata(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData)
{
    JetData *newData = reinterpret_cast<JetData *>(&pObjData->dwData);
    QByteArray dataToSend;
    DataIdentifiers id;

    //n1
    if(fabs(d_lastJetData.engine1N1 - newData->engine1N1) >= d_currentAirplaneSettings.n1Epsilon)
    {
        d_lastJetData.engine1N1 = newData->engine1N1;
        id = DataIdentifiers::ENGINE1_N1;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1N1), sizeof(newData->engine1N1));
    }
    if(fabs(d_lastJetData.engine2N1 - newData->engine2N1) >= d_currentAirplaneSettings.n1Epsilon)
    {
        d_lastJetData.engine2N1 = newData->engine2N1;
        id = DataIdentifiers::ENGINE2_N1;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine2N1), sizeof(newData->engine2N1));
    }
    if(fabs(d_lastJetData.engine3N1 - newData->engine3N1) >= d_currentAirplaneSettings.n1Epsilon)
    {
        d_lastJetData.engine3N1 = newData->engine3N1;
        id = DataIdentifiers::ENGINE3_N1;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine3N1), sizeof(newData->engine3N1));
    }
    if(fabs(d_lastJetData.engine4N1 - newData->engine4N1) >= d_currentAirplaneSettings.n1Epsilon)
    {
        d_lastJetData.engine4N1 = newData->engine4N1;
        id = DataIdentifiers::ENGINE4_N1;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine4N1), sizeof(newData->engine4N1));
    }

    //n2
    if(fabs(d_lastJetData.engine1N2 - newData->engine1N2) >= d_currentAirplaneSettings.n2Epsilon)
    {
        d_lastJetData.engine1N2 = newData->engine1N2;
        id = DataIdentifiers::ENGINE1_N2;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1N2), sizeof(newData->engine1N2));
    }
    if(fabs(d_lastJetData.engine2N2 - newData->engine2N2) >= d_currentAirplaneSettings.n2Epsilon)
    {
        d_lastJetData.engine2N2 = newData->engine2N2;
        id = DataIdentifiers::ENGINE2_N2;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine2N2), sizeof(newData->engine2N2));
    }
    if(fabs(d_lastJetData.engine3N2 - newData->engine3N2) >= d_currentAirplaneSettings.n2Epsilon)
    {
        d_lastJetData.engine3N2 = newData->engine3N2;
        id = DataIdentifiers::ENGINE3_N2;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine3N2), sizeof(newData->engine3N2));
    }
    if(fabs(d_lastJetData.engine4N2 - newData->engine4N2) >= d_currentAirplaneSettings.n2Epsilon)
    {
        d_lastJetData.engine4N2 = newData->engine4N2;
        id = DataIdentifiers::ENGINE4_N2;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine4N2), sizeof(newData->engine4N2));
    }

    //itt
    if(fabs(d_lastJetData.engine1Itt - newData->engine1Itt) >= d_currentAirplaneSettings.ittEpsilon)
    {
        d_lastJetData.engine1Itt = newData->engine1Itt;
        id = DataIdentifiers::ENGINE1_ITT;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1Itt), sizeof(newData->engine1Itt));
    }
    if(fabs(d_lastJetData.engine2Itt - newData->engine2Itt) >= d_currentAirplaneSettings.ittEpsilon)
    {
        d_lastJetData.engine2Itt = newData->engine2Itt;
        id = DataIdentifiers::ENGINE2_ITT;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine2Itt), sizeof(newData->engine2Itt));
    }
    if(fabs(d_lastJetData.engine3Itt - newData->engine3Itt) >= d_currentAirplaneSettings.ittEpsilon)
    {
        d_lastJetData.engine3Itt = newData->engine3Itt;
        id = DataIdentifiers::ENGINE3_ITT;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine3Itt), sizeof(newData->engine3Itt));
    }
    if(fabs(d_lastJetData.engine4Itt - newData->engine4Itt) >= d_currentAirplaneSettings.ittEpsilon)
    {
        d_lastJetData.engine4Itt = newData->engine4Itt;
        id = DataIdentifiers::ENGINE4_ITT;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine4Itt), sizeof(newData->engine4Itt));
    }

    //fuel qty
    if (d_currentAirplaneSettings.numTanks == 1)
    {
        if(fabs(d_lastJetData.commonData.fuelQtyTotal - newData->commonData.fuelQtyTotal) >= d_currentAirplaneSettings.fuelQtyEpsilon)
        {
            d_lastJetData.commonData.fuelQtyTotal = newData->commonData.fuelQtyTotal;

            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyTotal *= d_lastSlowData.fuelWeight;

            id = DataIdentifiers::ENGINE1_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyTotal), sizeof(newData->commonData.fuelQtyTotal));
        }
    }
    else
    {
        if(fabs(d_lastJetData.commonData.fuelQtyLeft - newData->commonData.fuelQtyLeft) >= d_currentAirplaneSettings.fuelQtyEpsilon)
        {
            d_lastJetData.commonData.fuelQtyLeft = newData->commonData.fuelQtyLeft;

            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyLeft *= d_lastSlowData.fuelWeight;

            id = DataIdentifiers::ENGINE1_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyLeft), sizeof(newData->commonData.fuelQtyLeft));
        }
        if(fabs(d_lastJetData.commonData.fuelQtyRight - newData->commonData.fuelQtyRight) >= d_currentAirplaneSettings.fuelQtyEpsilon)
        {
            d_lastJetData.commonData.fuelQtyRight = newData->commonData.fuelQtyRight;

            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyRight *= d_lastSlowData.fuelWeight;

            id = DataIdentifiers::ENGINE2_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyRight), sizeof(newData->commonData.fuelQtyRight));
        }
    }

    //fuel flow
    if(fabs(d_lastJetData.commonData.engine1FuelFlow + d_lastJetData.commonData.engine2FuelFlow - newData->commonData.engine1FuelFlow - newData->commonData.engine2FuelFlow) >= 2 * d_currentAirplaneSettings.fuelFlowEpsilon)
    {
        d_lastJetData.commonData.engine1FuelFlow = newData->commonData.engine1FuelFlow;
        d_lastJetData.commonData.engine2FuelFlow = newData->commonData.engine2FuelFlow;

        newData->commonData.engine1FuelFlow = (newData->commonData.engine1FuelFlow + newData->commonData.engine2FuelFlow) / 2.0;

        if (!d_currentAirplaneSettings.fuelFlowByVolume)
            newData->commonData.engine1FuelFlow *= 3600.0;

        id = DataIdentifiers::ENGINE1_FUEL_FLOW;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1FuelFlow), sizeof(newData->commonData.engine1FuelFlow));
    }
    if(fabs(d_lastJetData.commonData.engine3FuelFlow + d_lastJetData.commonData.engine4FuelFlow - newData->commonData.engine3FuelFlow - newData->commonData.engine4FuelFlow) >= 2 * d_currentAirplaneSettings.fuelFlowEpsilon)
    {
        d_lastJetData.commonData.engine3FuelFlow = newData->commonData.engine3FuelFlow;
        d_lastJetData.commonData.engine4FuelFlow = newData->commonData.engine4FuelFlow;

        newData->commonData.engine3FuelFlow = (newData->commonData.engine3FuelFlow + newData->commonData.engine4FuelFlow) / 2.0;

        if (!d_currentAirplaneSettings.fuelFlowByVolume)
            newData->commonData.engine3FuelFlow *= 3600.0;

        id = DataIdentifiers::ENGINE2_FUEL_FLOW;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine3FuelFlow), sizeof(newData->commonData.engine3FuelFlow));
    }

    //oil temp
    if(fabs(d_lastJetData.commonData.engine1OilTemp + d_lastJetData.commonData.engine2OilTemp - newData->commonData.engine1OilTemp - newData->commonData.engine2OilTemp) >= 2 * d_currentAirplaneSettings.oilTempEpsilon)
    {
        d_lastJetData.commonData.engine1OilTemp = newData->commonData.engine1OilTemp;
        d_lastJetData.commonData.engine2OilTemp = newData->commonData.engine2OilTemp;
        newData->commonData.engine1OilTemp = (newData->commonData.engine1OilTemp + newData->commonData.engine2OilTemp) / 2.0;
        id = DataIdentifiers::ENGINE1_OIL_TEMP;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1OilTemp), sizeof(newData->commonData.engine1OilTemp));
    }
    if(fabs(d_lastJetData.commonData.engine3OilTemp + d_lastJetData.commonData.engine4OilTemp - newData->commonData.engine3OilTemp - newData->commonData.engine4OilTemp) >= 2 * d_currentAirplaneSettings.oilTempEpsilon)
    {
        d_lastJetData.commonData.engine3OilTemp = newData->commonData.engine3OilTemp;
        d_lastJetData.commonData.engine4OilTemp = newData->commonData.engine4OilTemp;
        newData->commonData.engine3OilTemp = (newData->commonData.engine3OilTemp + newData->commonData.engine4OilTemp) / 2.0;
        id = DataIdentifiers::ENGINE2_OIL_TEMP;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine3OilTemp), sizeof(newData->commonData.engine3OilTemp));
    }

    //oil press
    if(fabs(d_lastJetData.commonData.engine1OilPress + d_lastJetData.commonData.engine2OilPress - newData->commonData.engine1OilPress - newData->commonData.engine2OilPress) >= 2 * d_currentAirplaneSettings.oilPressEpsilon)
    {
        d_lastJetData.commonData.engine1OilPress = newData->commonData.engine1OilPress;
        d_lastJetData.commonData.engine2OilPress = newData->commonData.engine2OilPress;
        newData->commonData.engine1OilPress = (newData->commonData.engine1OilPress + newData->commonData.engine2OilPress) / 2.0;
        id = DataIdentifiers::ENGINE1_OIL_PRESS;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1OilPress), sizeof(newData->commonData.engine1OilPress));
    }
    if(fabs(d_lastJetData.commonData.engine3OilPress + d_lastJetData.commonData.engine4OilPress - newData->commonData.engine3OilPress - newData->commonData.engine4OilPress) >= 2 * d_currentAirplaneSettings.oilPressEpsilon)
    {
        d_lastJetData.commonData.engine3OilPress = newData->commonData.engine3OilPress;
        d_lastJetData.commonData.engine4OilPress = newData->commonData.engine4OilPress;
        newData->commonData.engine3OilPress = (newData->commonData.engine3OilPress + newData->commonData.engine4OilPress) / 2.0;
        id = DataIdentifiers::ENGINE2_OIL_PRESS;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine3OilPress), sizeof(newData->commonData.engine3OilPress));
    }

    //apu
    if (d_currentAirplaneSettings.hasApu)
        if (lround(d_lastJetData.commonData.apuRpmPct) != lround(newData->commonData.apuRpmPct))
        {
            d_lastJetData.commonData.apuRpmPct = newData->commonData.apuRpmPct;
            int32_t value = lround(newData->commonData.apuRpmPct);
            id = DataIdentifiers::APU_RPM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&value), sizeof(value));
        }

    //flaps\spoilers
    if (d_currentAirplaneSettings.hasFlaps)
    {
        //flaps
        if (fabs(d_lastJetData.commonData.flapsLeftAngle + d_lastJetData.commonData.flapsRightAngle - newData->commonData.flapsLeftAngle - newData->commonData.flapsRightAngle) >= 1.0)
        {
            d_lastJetData.commonData.flapsLeftAngle = newData->commonData.flapsLeftAngle;
            d_lastJetData.commonData.flapsRightAngle = newData->commonData.flapsRightAngle;

            newData->commonData.flapsRightAngle = (newData->commonData.flapsLeftAngle + newData->commonData.flapsRightAngle) / 2.0;
            id = DataIdentifiers::FLAPS_ANGLE;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.flapsRightAngle), sizeof(newData->commonData.flapsRightAngle));
        }

        //spoilers
        if (d_currentAirplaneSettings.hasSpoilers)
            if (fabs(d_lastJetData.commonData.spoilersLeftPct + d_lastJetData.commonData.spoilersRightPct - newData->commonData.spoilersLeftPct - newData->commonData.spoilersRightPct) >= 1.0)
            {
                d_lastJetData.commonData.spoilersLeftPct = newData->commonData.spoilersLeftPct;
                d_lastJetData.commonData.spoilersRightPct = newData->commonData.spoilersRightPct;

                newData->commonData.spoilersRightPct = (newData->commonData.spoilersLeftPct + newData->commonData.spoilersRightPct) / 2.0;
                id = DataIdentifiers::SPOILERS_PCT;
                dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<char *>(&newData->commonData.spoilersRightPct), sizeof(newData->commonData.spoilersRightPct));
            }
    }

    //elev trim
    if (d_currentAirplaneSettings.hasElevTrim)
        if (fabs(d_lastJetData.commonData.elevTrimPct - newData->commonData.elevTrimPct) >= 0.002)
        {
            d_lastJetData.commonData.elevTrimPct = newData->commonData.elevTrimPct;
            id = DataIdentifiers::ELEV_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.elevTrimPct), sizeof(newData->commonData.elevTrimPct));
        }

    //rudder trim
    if (d_currentAirplaneSettings.hasRudderTrim)
        if (fabs(d_lastJetData.commonData.rudderTrimPct - newData->commonData.rudderTrimPct) >= 0.002)
        {
            d_lastJetData.commonData.rudderTrimPct = newData->commonData.rudderTrimPct;
            id = DataIdentifiers::RUDD_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.rudderTrimPct), sizeof(newData->commonData.rudderTrimPct));
        }

    //aileron trim
    if (d_currentAirplaneSettings.hasAileronTrim)
        if (fabs(d_lastJetData.commonData.aileronTrimPct - newData->commonData.aileronTrimPct) >= 0.002)
        {
            d_lastJetData.commonData.aileronTrimPct = newData->commonData.aileronTrimPct;
            id = DataIdentifiers::AIL_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.aileronTrimPct), sizeof(newData->commonData.aileronTrimPct));
        }

    if (!dataToSend.isEmpty())
        emit sendData(dataToSend);
}
