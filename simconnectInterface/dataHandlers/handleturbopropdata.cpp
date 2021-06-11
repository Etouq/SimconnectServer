#include "../simconnectthread.ih"


void SimconnectThread::handleTurbopropSingleEngdata(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData)
{
    TurbopropData *newData = reinterpret_cast<TurbopropData *>(&pObjData->dwData);
    QByteArray dataToSend;
    DataIdentifiers id;

    //n1
    if(fabs(d_lastTurbopropData.engine1N1 - newData->engine1N1) >= d_currentAirplaneSettings.n1Epsilon)
    {
        d_lastTurbopropData.engine1N1 = newData->engine1N1;
        id = DataIdentifiers::ENGINE1_N1;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1N1), sizeof(newData->engine1N1));
    }

    //trq
    if(fabs(d_lastTurbopropData.engine1Trq - newData->engine1Trq) >= d_currentAirplaneSettings.trqEpsilon)
    {
        d_lastTurbopropData.engine1Trq = newData->engine1Trq;
        id = DataIdentifiers::ENGINE1_TRQ;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1Trq), sizeof(newData->engine1Trq));
    }

    //itt
    if(fabs(d_lastTurbopropData.engine1Itt - newData->engine1Itt) >= d_currentAirplaneSettings.ittEpsilon)
    {
        d_lastTurbopropData.engine1Itt = newData->engine1Itt;
        id = DataIdentifiers::ENGINE1_ITT;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1Itt), sizeof(newData->engine1Itt));
    }

    //rpm
    if (fabs(d_lastTurbopropData.engine1Rpm - newData->engine1Rpm) >= 1.0)
    {
        d_lastTurbopropData.engine1Rpm = newData->engine1Rpm;
        id = DataIdentifiers::ENGINE1_RPM;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1Rpm), sizeof(newData->engine1Rpm));
    }

    //fuel qty
    if (d_currentAirplaneSettings.numTanks == 1)
    {
        if(fabs(d_lastTurbopropData.commonData.fuelQtyTotal - newData->commonData.fuelQtyTotal) >= d_currentAirplaneSettings.fuelQtyEpsilon)
        {
            d_lastTurbopropData.commonData.fuelQtyTotal = newData->commonData.fuelQtyTotal;

            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyTotal *= d_lastSlowData.fuelWeight;

            id = DataIdentifiers::ENGINE1_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyTotal), sizeof(newData->commonData.fuelQtyTotal));
        }
    }
    else
    {
        if(fabs(d_lastTurbopropData.commonData.fuelQtyLeft - newData->commonData.fuelQtyLeft) >= d_currentAirplaneSettings.fuelQtyEpsilon)
        {
            d_lastTurbopropData.commonData.fuelQtyLeft = newData->commonData.fuelQtyLeft;

            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyLeft *= d_lastSlowData.fuelWeight;

            id = DataIdentifiers::ENGINE1_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyLeft), sizeof(newData->commonData.fuelQtyLeft));
        }
        if(fabs(d_lastTurbopropData.commonData.fuelQtyRight - newData->commonData.fuelQtyRight) >= d_currentAirplaneSettings.fuelQtyEpsilon)
        {
            d_lastTurbopropData.commonData.fuelQtyRight = newData->commonData.fuelQtyRight;

            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyRight *= d_lastSlowData.fuelWeight;

            id = DataIdentifiers::ENGINE2_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyRight), sizeof(newData->commonData.fuelQtyRight));
        }
    }

    //fuel flow
    if(fabs(d_lastTurbopropData.commonData.engine1FuelFlow - newData->commonData.engine1FuelFlow) >= d_currentAirplaneSettings.fuelFlowEpsilon)
    {
        d_lastTurbopropData.commonData.engine1FuelFlow = newData->commonData.engine1FuelFlow;

        if (!d_currentAirplaneSettings.fuelFlowByVolume)
            newData->commonData.engine1FuelFlow *= 3600.0;

        id = DataIdentifiers::ENGINE1_FUEL_FLOW;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1FuelFlow), sizeof(newData->commonData.engine1FuelFlow));
    }
    if(fabs(d_lastTurbopropData.commonData.engine2FuelFlow - newData->commonData.engine2FuelFlow) >= d_currentAirplaneSettings.fuelFlowEpsilon)
    {
        d_lastTurbopropData.commonData.engine2FuelFlow = newData->commonData.engine2FuelFlow;

        if (!d_currentAirplaneSettings.fuelFlowByVolume)
            newData->commonData.engine2FuelFlow *= 3600.0;

        id = DataIdentifiers::ENGINE2_FUEL_FLOW;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine2FuelFlow), sizeof(newData->commonData.engine2FuelFlow));
    }

    //oil temp
    if(fabs(d_lastTurbopropData.commonData.engine1OilTemp - newData->commonData.engine1OilTemp) >= d_currentAirplaneSettings.oilTempEpsilon)
    {
        d_lastTurbopropData.commonData.engine1OilTemp = newData->commonData.engine1OilTemp;
        id = DataIdentifiers::ENGINE1_OIL_TEMP;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1OilTemp), sizeof(newData->commonData.engine1OilTemp));
    }

    //oil press
    if(fabs(d_lastTurbopropData.commonData.engine1OilPress - newData->commonData.engine1OilPress) >= d_currentAirplaneSettings.oilPressEpsilon)
    {
        d_lastTurbopropData.commonData.engine1OilPress = newData->commonData.engine1OilPress;
        id = DataIdentifiers::ENGINE1_OIL_PRESS;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1OilPress), sizeof(newData->commonData.engine1OilPress));
    }

    //egt
    if (d_currentAirplaneSettings.hasEgt)
        if (fabs(d_lastTurbopropData.engine1Egt - newData->engine1Egt) >= d_currentAirplaneSettings.egtEpsilon)
        {
            d_lastTurbopropData.engine1Egt = newData->engine1Egt;
            id = DataIdentifiers::ENGINE1_EGT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->engine1Egt), sizeof(newData->engine1Egt));
        }

    //flaps\spoilers
    if (d_currentAirplaneSettings.hasFlaps)
    {
        //flaps
        if (fabs(d_lastTurbopropData.commonData.flapsLeftAngle + d_lastTurbopropData.commonData.flapsRightAngle - newData->commonData.flapsLeftAngle - newData->commonData.flapsRightAngle) >= 1.0)
        {
            d_lastTurbopropData.commonData.flapsLeftAngle = newData->commonData.flapsLeftAngle;
            d_lastTurbopropData.commonData.flapsRightAngle = newData->commonData.flapsRightAngle;

            newData->commonData.flapsRightAngle = (newData->commonData.flapsLeftAngle + newData->commonData.flapsRightAngle) / 2.0;
            id = DataIdentifiers::FLAPS_ANGLE;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.flapsRightAngle), sizeof(newData->commonData.flapsRightAngle));
        }

        //spoilers
        if (d_currentAirplaneSettings.hasSpoilers)
            if (fabs(d_lastTurbopropData.commonData.spoilersLeftPct + d_lastTurbopropData.commonData.spoilersRightPct - newData->commonData.spoilersLeftPct - newData->commonData.spoilersRightPct) >= 1.0)
            {
                d_lastTurbopropData.commonData.spoilersLeftPct = newData->commonData.spoilersLeftPct;
                d_lastTurbopropData.commonData.spoilersRightPct = newData->commonData.spoilersRightPct;

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
        if (fabs(d_lastTurbopropData.commonData.rudderTrimPct - newData->commonData.rudderTrimPct) >= 0.002)
        {
            d_lastTurbopropData.commonData.rudderTrimPct = newData->commonData.rudderTrimPct;
            id = DataIdentifiers::RUDD_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.rudderTrimPct), sizeof(newData->commonData.rudderTrimPct));
        }

    //aileron trim
    if (d_currentAirplaneSettings.hasAileronTrim)
        if (fabs(d_lastTurbopropData.commonData.aileronTrimPct - newData->commonData.aileronTrimPct) >= 0.002)
        {
            d_lastTurbopropData.commonData.aileronTrimPct = newData->commonData.aileronTrimPct;
            id = DataIdentifiers::AIL_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.aileronTrimPct), sizeof(newData->commonData.aileronTrimPct));
        }

    if (!dataToSend.isEmpty())
        emit sendData(dataToSend);
}


void SimconnectThread::handleTurbopropTwinEngdata(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData)
{
    TurbopropData *newData = reinterpret_cast<TurbopropData *>(&pObjData->dwData);
    QByteArray dataToSend;
    DataIdentifiers id;

    //n1
    if(fabs(d_lastTurbopropData.engine1N1 - newData->engine1N1) >= d_currentAirplaneSettings.n1Epsilon)
    {
        d_lastTurbopropData.engine1N1 = newData->engine1N1;
        id = DataIdentifiers::ENGINE1_N1;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1N1), sizeof(newData->engine1N1));
    }
    if(fabs(d_lastTurbopropData.engine2N1 - newData->engine2N1) >= d_currentAirplaneSettings.n1Epsilon)
    {
        d_lastTurbopropData.engine2N1 = newData->engine2N1;
        id = DataIdentifiers::ENGINE2_N1;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine2N1), sizeof(newData->engine2N1));
    }

    //trq
    if(fabs(d_lastTurbopropData.engine1Trq - newData->engine1Trq) >= d_currentAirplaneSettings.trqEpsilon)
    {
        d_lastTurbopropData.engine1Trq = newData->engine1Trq;
        id = DataIdentifiers::ENGINE1_TRQ;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1Trq), sizeof(newData->engine1Trq));
    }
    if(fabs(d_lastTurbopropData.engine2Trq - newData->engine2Trq) >= d_currentAirplaneSettings.trqEpsilon)
    {
        d_lastTurbopropData.engine2Trq = newData->engine2Trq;
        id = DataIdentifiers::ENGINE2_TRQ;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine2Trq), sizeof(newData->engine2Trq));
    }

    //itt
    if(fabs(d_lastTurbopropData.engine1Itt - newData->engine1Itt) >= d_currentAirplaneSettings.ittEpsilon)
    {
        d_lastTurbopropData.engine1Itt = newData->engine1Itt;
        id = DataIdentifiers::ENGINE1_ITT;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1Itt), sizeof(newData->engine1Itt));
    }
    if(fabs(d_lastTurbopropData.engine2Itt - newData->engine2Itt) >= d_currentAirplaneSettings.ittEpsilon)
    {
        d_lastTurbopropData.engine2Itt = newData->engine2Itt;
        id = DataIdentifiers::ENGINE2_ITT;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine2Itt), sizeof(newData->engine2Itt));
    }

    //rpm
    if (fabs(d_lastTurbopropData.engine1Rpm - newData->engine1Rpm) >= 1.0)
    {
        d_lastTurbopropData.engine1Rpm = newData->engine1Rpm;
        id = DataIdentifiers::ENGINE1_RPM;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1Rpm), sizeof(newData->engine1Rpm));
    }
    if (fabs(d_lastTurbopropData.engine2Rpm - newData->engine2Rpm) >= 1.0)
    {
        d_lastTurbopropData.engine2Rpm = newData->engine2Rpm;
        id = DataIdentifiers::ENGINE2_RPM;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine2Rpm), sizeof(newData->engine2Rpm));
    }

    //fuel qty
    if (d_currentAirplaneSettings.numTanks == 1)
    {
        if(fabs(d_lastTurbopropData.commonData.fuelQtyTotal - newData->commonData.fuelQtyTotal) >= d_currentAirplaneSettings.fuelQtyEpsilon)
        {
            d_lastTurbopropData.commonData.fuelQtyTotal = newData->commonData.fuelQtyTotal;

            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyTotal *= d_lastSlowData.fuelWeight;

            id = DataIdentifiers::ENGINE1_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyTotal), sizeof(newData->commonData.fuelQtyTotal));
        }
    }
    else
    {
        if(fabs(d_lastTurbopropData.commonData.fuelQtyLeft - newData->commonData.fuelQtyLeft) >= d_currentAirplaneSettings.fuelQtyEpsilon)
        {
            d_lastTurbopropData.commonData.fuelQtyLeft = newData->commonData.fuelQtyLeft;

            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyLeft *= d_lastSlowData.fuelWeight;

            id = DataIdentifiers::ENGINE1_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyLeft), sizeof(newData->commonData.fuelQtyLeft));
        }
        if(fabs(d_lastTurbopropData.commonData.fuelQtyRight - newData->commonData.fuelQtyRight) >= d_currentAirplaneSettings.fuelQtyEpsilon)
        {
            d_lastTurbopropData.commonData.fuelQtyRight = newData->commonData.fuelQtyRight;

            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyRight *= d_lastSlowData.fuelWeight;

            id = DataIdentifiers::ENGINE2_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyRight), sizeof(newData->commonData.fuelQtyRight));
        }
    }

    //fuel flow
    if(fabs(d_lastTurbopropData.commonData.engine1FuelFlow - newData->commonData.engine1FuelFlow) >= d_currentAirplaneSettings.fuelFlowEpsilon)
    {
        d_lastTurbopropData.commonData.engine1FuelFlow = newData->commonData.engine1FuelFlow;

        if (!d_currentAirplaneSettings.fuelFlowByVolume)
            newData->commonData.engine1FuelFlow *= 3600.0;

        id = DataIdentifiers::ENGINE1_FUEL_FLOW;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1FuelFlow), sizeof(newData->commonData.engine1FuelFlow));
    }
    if(fabs(d_lastTurbopropData.commonData.engine2FuelFlow - newData->commonData.engine2FuelFlow) >= d_currentAirplaneSettings.fuelFlowEpsilon)
    {
        d_lastTurbopropData.commonData.engine2FuelFlow = newData->commonData.engine2FuelFlow;

        if (!d_currentAirplaneSettings.fuelFlowByVolume)
            newData->commonData.engine2FuelFlow *= 3600.0;

        id = DataIdentifiers::ENGINE2_FUEL_FLOW;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine2FuelFlow), sizeof(newData->commonData.engine2FuelFlow));
    }

    //oil temp
    if(fabs(d_lastTurbopropData.commonData.engine1OilTemp - newData->commonData.engine1OilTemp) >= d_currentAirplaneSettings.oilTempEpsilon)
    {
        d_lastTurbopropData.commonData.engine1OilTemp = newData->commonData.engine1OilTemp;
        id = DataIdentifiers::ENGINE1_OIL_TEMP;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1OilTemp), sizeof(newData->commonData.engine1OilTemp));
    }
    if(fabs(d_lastTurbopropData.commonData.engine2OilTemp - newData->commonData.engine2OilTemp) >= d_currentAirplaneSettings.oilTempEpsilon)
    {
        d_lastTurbopropData.commonData.engine2OilTemp = newData->commonData.engine2OilTemp;
        id = DataIdentifiers::ENGINE2_OIL_TEMP;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine2OilTemp), sizeof(newData->commonData.engine2OilTemp));
    }

    //oil press
    if(fabs(d_lastTurbopropData.commonData.engine1OilPress - newData->commonData.engine1OilPress) >= d_currentAirplaneSettings.oilPressEpsilon)
    {
        d_lastTurbopropData.commonData.engine1OilPress = newData->commonData.engine1OilPress;
        id = DataIdentifiers::ENGINE1_OIL_PRESS;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1OilPress), sizeof(newData->commonData.engine1OilPress));
    }
    if(fabs(d_lastTurbopropData.commonData.engine2OilPress - newData->commonData.engine2OilPress) >= d_currentAirplaneSettings.oilPressEpsilon)
    {
        d_lastTurbopropData.commonData.engine2OilPress = newData->commonData.engine2OilPress;
        id = DataIdentifiers::ENGINE2_OIL_PRESS;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine2OilPress), sizeof(newData->commonData.engine2OilPress));
    }

    //egt
    if (d_currentAirplaneSettings.hasEgt)
    {
        if (fabs(d_lastTurbopropData.engine1Egt - newData->engine1Egt) >= d_currentAirplaneSettings.egtEpsilon)
        {
            d_lastTurbopropData.engine1Egt = newData->engine1Egt;
            id = DataIdentifiers::ENGINE1_EGT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->engine1Egt), sizeof(newData->engine1Egt));
        }
        if (fabs(d_lastTurbopropData.engine2Egt - newData->engine2Egt) >= d_currentAirplaneSettings.egtEpsilon)
        {
            d_lastTurbopropData.engine2Egt = newData->engine2Egt;
            id = DataIdentifiers::ENGINE2_EGT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->engine2Egt), sizeof(newData->engine2Egt));
        }
    }


    //flaps\spoilers
    if (d_currentAirplaneSettings.hasFlaps)
    {
        //flaps
        if (fabs(d_lastTurbopropData.commonData.flapsLeftAngle + d_lastTurbopropData.commonData.flapsRightAngle - newData->commonData.flapsLeftAngle - newData->commonData.flapsRightAngle) >= 1.0)
        {
            d_lastTurbopropData.commonData.flapsLeftAngle = newData->commonData.flapsLeftAngle;
            d_lastTurbopropData.commonData.flapsRightAngle = newData->commonData.flapsRightAngle;

            newData->commonData.flapsRightAngle = (newData->commonData.flapsLeftAngle + newData->commonData.flapsRightAngle) / 2.0;
            id = DataIdentifiers::FLAPS_ANGLE;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.flapsRightAngle), sizeof(newData->commonData.flapsRightAngle));
        }

        //spoilers
        if (d_currentAirplaneSettings.hasSpoilers)
            if (fabs(d_lastTurbopropData.commonData.spoilersLeftPct + d_lastTurbopropData.commonData.spoilersRightPct - newData->commonData.spoilersLeftPct - newData->commonData.spoilersRightPct) >= 1.0)
            {
                d_lastTurbopropData.commonData.spoilersLeftPct = newData->commonData.spoilersLeftPct;
                d_lastTurbopropData.commonData.spoilersRightPct = newData->commonData.spoilersRightPct;

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
        if (fabs(d_lastTurbopropData.commonData.rudderTrimPct - newData->commonData.rudderTrimPct) >= 0.002)
        {
            d_lastTurbopropData.commonData.rudderTrimPct = newData->commonData.rudderTrimPct;
            id = DataIdentifiers::RUDD_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.rudderTrimPct), sizeof(newData->commonData.rudderTrimPct));
        }

    //aileron trim
    if (d_currentAirplaneSettings.hasAileronTrim)
        if (fabs(d_lastTurbopropData.commonData.aileronTrimPct - newData->commonData.aileronTrimPct) >= 0.002)
        {
            d_lastTurbopropData.commonData.aileronTrimPct = newData->commonData.aileronTrimPct;
            id = DataIdentifiers::AIL_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.aileronTrimPct), sizeof(newData->commonData.aileronTrimPct));
        }

    if (!dataToSend.isEmpty())
        emit sendData(dataToSend);

}













