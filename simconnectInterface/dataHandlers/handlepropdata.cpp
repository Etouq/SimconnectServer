#include "../simconnectthread.ih"

void SimconnectThread::handlePropSingleEngdata(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData)
{
    PropData *newData = reinterpret_cast<PropData *>(&pObjData->dwData);
    QByteArray dataToSend;
    SimconnectIds id;

    // rpm
    if (fabs(d_lastPropData.engine1Rpm - newData->engine1Rpm)
        >= d_currentAirplaneSettings.rpmEpsilon)
    {
        d_lastPropData.engine1Rpm = newData->engine1Rpm;
        id = SimconnectIds::ENGINE1_RPM;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1Rpm),
                          sizeof(newData->engine1Rpm));
    }

    // second
    if (fabs(d_lastPropData.engine1Second - newData->engine1Second)
        >= d_currentAirplaneSettings.secondEpsilon)
    {
        d_lastPropData.engine1Second = newData->engine1Second;
        newData->engine1Second /= d_currentAirplaneSettings.secondDivFactor;
        id = SimconnectIds::ENGINE1_SECOND;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1Second),
                          sizeof(newData->engine1Second));
    }

    // fuel qty
    if (d_currentAirplaneSettings.numTanks == 1)
    {
        if (fabs(d_lastPropData.commonData.fuelQtyTotal - newData->commonData.fuelQtyTotal)
            >= d_currentAirplaneSettings.fuelQtyEpsilon)
        {
            d_lastPropData.commonData.fuelQtyTotal = newData->commonData.fuelQtyTotal;

            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyTotal *= d_lastSlowData.fuelWeight;

            id = SimconnectIds::ENGINE1_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyTotal),
                              sizeof(newData->commonData.fuelQtyTotal));
        }
    }
    else
    {
        if (fabs(d_lastPropData.commonData.fuelQtyLeft - newData->commonData.fuelQtyLeft)
            >= d_currentAirplaneSettings.fuelQtyEpsilon)
        {
            d_lastPropData.commonData.fuelQtyLeft = newData->commonData.fuelQtyLeft;

            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyLeft *= d_lastSlowData.fuelWeight;

            id = SimconnectIds::ENGINE1_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyLeft),
                              sizeof(newData->commonData.fuelQtyLeft));
        }
        if (fabs(d_lastPropData.commonData.fuelQtyRight - newData->commonData.fuelQtyRight)
            >= d_currentAirplaneSettings.fuelQtyEpsilon)
        {
            d_lastPropData.commonData.fuelQtyRight = newData->commonData.fuelQtyRight;

            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyRight *= d_lastSlowData.fuelWeight;

            id = SimconnectIds::ENGINE2_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyRight),
                              sizeof(newData->commonData.fuelQtyRight));
        }
    }

    // fuel flow
    if (fabs(d_lastPropData.commonData.engine1FuelFlow - newData->commonData.engine1FuelFlow)
        >= d_currentAirplaneSettings.fuelFlowEpsilon)
    {
        d_lastPropData.commonData.engine1FuelFlow = newData->commonData.engine1FuelFlow;

        if (!d_currentAirplaneSettings.fuelFlowByVolume)
            newData->commonData.engine1FuelFlow *= 3600.0;
        else
            newData->commonData.engine1FuelFlow /= 0.2641720523;

        id = SimconnectIds::ENGINE1_FUEL_FLOW;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1FuelFlow),
                          sizeof(newData->commonData.engine1FuelFlow));
    }

    // oil temp
    if (fabs(d_lastPropData.commonData.engine1OilTemp - newData->commonData.engine1OilTemp)
        >= d_currentAirplaneSettings.oilTempEpsilon)
    {
        d_lastPropData.commonData.engine1OilTemp = newData->commonData.engine1OilTemp;
        id = SimconnectIds::ENGINE1_OIL_TEMP;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1OilTemp),
                          sizeof(newData->commonData.engine1OilTemp));
    }

    // oil press
    if (fabs(d_lastPropData.commonData.engine1OilPress - newData->commonData.engine1OilPress)
        >= d_currentAirplaneSettings.oilPressEpsilon)
    {
        d_lastPropData.commonData.engine1OilPress = newData->commonData.engine1OilPress;
        id = SimconnectIds::ENGINE1_OIL_PRESS;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1OilPress),
                          sizeof(newData->commonData.engine1OilPress));
    }

    // egt
    if (d_currentAirplaneSettings.hasEgt)
        if (fabs(d_lastPropData.engine1Egt - newData->engine1Egt)
            >= d_currentAirplaneSettings.egtEpsilon)
        {
            d_lastPropData.engine1Egt = newData->engine1Egt;
            id = SimconnectIds::ENGINE1_EGT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->engine1Egt),
                              sizeof(newData->engine1Egt));
        }

    // flaps\spoilers
    if (d_currentAirplaneSettings.hasFlaps)
    {
        // flaps
        if (fabs(d_lastPropData.commonData.flapsLeftAngle
                 + d_lastPropData.commonData.flapsRightAngle - newData->commonData.flapsLeftAngle
                 - newData->commonData.flapsRightAngle)
            >= 1.0)
        {
            d_lastPropData.commonData.flapsLeftAngle = newData->commonData.flapsLeftAngle;
            d_lastPropData.commonData.flapsRightAngle = newData->commonData.flapsRightAngle;

            newData->commonData.flapsRightAngle
              = (newData->commonData.flapsLeftAngle + newData->commonData.flapsRightAngle) / 2.0;
            id = SimconnectIds::FLAPS_ANGLE;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.flapsRightAngle),
                              sizeof(newData->commonData.flapsRightAngle));
        }

        // spoilers
        if (d_currentAirplaneSettings.hasSpoilers)
            if (fabs(d_lastPropData.commonData.spoilersLeftPct
                     + d_lastPropData.commonData.spoilersRightPct
                     - newData->commonData.spoilersLeftPct - newData->commonData.spoilersRightPct)
                >= 1.0)
            {
                d_lastPropData.commonData.spoilersLeftPct = newData->commonData.spoilersLeftPct;
                d_lastPropData.commonData.spoilersRightPct = newData->commonData.spoilersRightPct;

                newData->commonData.spoilersRightPct
                  = (newData->commonData.spoilersLeftPct + newData->commonData.spoilersRightPct)
                    / 2.0;
                id = SimconnectIds::SPOILERS_PCT;
                dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<char *>(&newData->commonData.spoilersRightPct),
                                  sizeof(newData->commonData.spoilersRightPct));
            }
    }

    // elev trim
    if (d_currentAirplaneSettings.hasElevTrim)
        if (fabs(d_lastJetData.commonData.elevTrimPct - newData->commonData.elevTrimPct) >= 0.002)
        {
            d_lastJetData.commonData.elevTrimPct = newData->commonData.elevTrimPct;
            id = SimconnectIds::ELEV_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.elevTrimPct),
                              sizeof(newData->commonData.elevTrimPct));
        }

    // rudder trim
    if (d_currentAirplaneSettings.hasRudderTrim)
        if (fabs(d_lastJetData.commonData.rudderTrimPct - newData->commonData.rudderTrimPct)
            >= 0.002)
        {
            d_lastJetData.commonData.rudderTrimPct = newData->commonData.rudderTrimPct;
            id = SimconnectIds::RUDD_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.rudderTrimPct),
                              sizeof(newData->commonData.rudderTrimPct));
        }

    // aileron trim
    if (d_currentAirplaneSettings.hasAileronTrim)
        if (fabs(d_lastJetData.commonData.aileronTrimPct - newData->commonData.aileronTrimPct)
            >= 0.002)
        {
            d_lastJetData.commonData.aileronTrimPct = newData->commonData.aileronTrimPct;
            id = SimconnectIds::AIL_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.aileronTrimPct),
                              sizeof(newData->commonData.aileronTrimPct));
        }

    if (!dataToSend.isEmpty())
        emit sendData(dataToSend);
}


void SimconnectThread::handlePropTwinEngdata(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData)
{
    PropData *newData = reinterpret_cast<PropData *>(&pObjData->dwData);
    QByteArray dataToSend;
    SimconnectIds id;

    // rpm
    if (fabs(d_lastPropData.engine1Rpm - newData->engine1Rpm)
        >= d_currentAirplaneSettings.rpmEpsilon)
    {
        d_lastPropData.engine1Rpm = newData->engine1Rpm;
        id = SimconnectIds::ENGINE1_RPM;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1Rpm),
                          sizeof(newData->engine1Rpm));
    }
    if (fabs(d_lastPropData.engine2Rpm - newData->engine2Rpm)
        >= d_currentAirplaneSettings.rpmEpsilon)
    {
        d_lastPropData.engine2Rpm = newData->engine2Rpm;
        id = SimconnectIds::ENGINE2_RPM;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine2Rpm),
                          sizeof(newData->engine2Rpm));
    }

    // second
    if (fabs(d_lastPropData.engine1Second - newData->engine1Second)
        >= d_currentAirplaneSettings.secondEpsilon)
    {
        d_lastPropData.engine1Second = newData->engine1Second;
        newData->engine1Second /= d_currentAirplaneSettings.secondDivFactor;
        id = SimconnectIds::ENGINE1_SECOND;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1Second),
                          sizeof(newData->engine1Second));
    }
    if (fabs(d_lastPropData.engine2Second - newData->engine2Second)
        >= d_currentAirplaneSettings.secondEpsilon)
    {
        d_lastPropData.engine2Second = newData->engine2Second;
        newData->engine2Second /= d_currentAirplaneSettings.secondDivFactor;
        id = SimconnectIds::ENGINE2_SECOND;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine2Second),
                          sizeof(newData->engine2Second));
    }

    // fuel qty
    if (d_currentAirplaneSettings.numTanks == 1)
    {
        if (fabs(d_lastPropData.commonData.fuelQtyTotal - newData->commonData.fuelQtyTotal)
            >= d_currentAirplaneSettings.fuelQtyEpsilon)
        {
            d_lastPropData.commonData.fuelQtyTotal = newData->commonData.fuelQtyTotal;

            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyTotal *= d_lastSlowData.fuelWeight;

            id = SimconnectIds::ENGINE1_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyTotal),
                              sizeof(newData->commonData.fuelQtyTotal));
        }
    }
    else
    {
        if (fabs(d_lastPropData.commonData.fuelQtyLeft - newData->commonData.fuelQtyLeft)
            >= d_currentAirplaneSettings.fuelQtyEpsilon)
        {
            d_lastPropData.commonData.fuelQtyLeft = newData->commonData.fuelQtyLeft;

            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyLeft *= d_lastSlowData.fuelWeight;

            id = SimconnectIds::ENGINE1_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyLeft),
                              sizeof(newData->commonData.fuelQtyLeft));
        }
        if (fabs(d_lastPropData.commonData.fuelQtyRight - newData->commonData.fuelQtyRight)
            >= d_currentAirplaneSettings.fuelQtyEpsilon)
        {
            d_lastPropData.commonData.fuelQtyRight = newData->commonData.fuelQtyRight;

            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyRight *= d_lastSlowData.fuelWeight;

            id = SimconnectIds::ENGINE2_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyRight),
                              sizeof(newData->commonData.fuelQtyRight));
        }
    }

    // fuel flow
    if (fabs(d_lastPropData.commonData.engine1FuelFlow - newData->commonData.engine1FuelFlow)
        >= d_currentAirplaneSettings.fuelFlowEpsilon)
    {
        d_lastPropData.commonData.engine1FuelFlow = newData->commonData.engine1FuelFlow;

        if (!d_currentAirplaneSettings.fuelFlowByVolume)
            newData->commonData.engine1FuelFlow *= 3600.0;
        else
            newData->commonData.engine1FuelFlow /= 0.2641720523;

        id = SimconnectIds::ENGINE1_FUEL_FLOW;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1FuelFlow),
                          sizeof(newData->commonData.engine1FuelFlow));
    }
    if (fabs(d_lastPropData.commonData.engine2FuelFlow - newData->commonData.engine2FuelFlow)
        >= d_currentAirplaneSettings.fuelFlowEpsilon)
    {
        d_lastPropData.commonData.engine2FuelFlow = newData->commonData.engine2FuelFlow;

        if (!d_currentAirplaneSettings.fuelFlowByVolume)
            newData->commonData.engine2FuelFlow *= 3600.0;
        else
            newData->commonData.engine2FuelFlow /= 0.2641720523;

        id = SimconnectIds::ENGINE2_FUEL_FLOW;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine2FuelFlow),
                          sizeof(newData->commonData.engine2FuelFlow));
    }

    // oil temp
    if (fabs(d_lastPropData.commonData.engine1OilTemp - newData->commonData.engine1OilTemp)
        >= d_currentAirplaneSettings.oilTempEpsilon)
    {
        d_lastPropData.commonData.engine1OilTemp = newData->commonData.engine1OilTemp;
        id = SimconnectIds::ENGINE1_OIL_TEMP;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1OilTemp),
                          sizeof(newData->commonData.engine1OilTemp));
    }
    if (fabs(d_lastPropData.commonData.engine2OilTemp - newData->commonData.engine2OilTemp)
        >= d_currentAirplaneSettings.oilTempEpsilon)
    {
        d_lastPropData.commonData.engine2OilTemp = newData->commonData.engine2OilTemp;
        id = SimconnectIds::ENGINE2_OIL_TEMP;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine2OilTemp),
                          sizeof(newData->commonData.engine2OilTemp));
    }

    // oil press
    if (fabs(d_lastPropData.commonData.engine1OilPress - newData->commonData.engine1OilPress)
        >= d_currentAirplaneSettings.oilPressEpsilon)
    {
        d_lastPropData.commonData.engine1OilPress = newData->commonData.engine1OilPress;
        id = SimconnectIds::ENGINE1_OIL_PRESS;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1OilPress),
                          sizeof(newData->commonData.engine1OilPress));
    }
    if (fabs(d_lastPropData.commonData.engine2OilPress - newData->commonData.engine2OilPress)
        >= d_currentAirplaneSettings.oilPressEpsilon)
    {
        d_lastPropData.commonData.engine2OilPress = newData->commonData.engine2OilPress;
        id = SimconnectIds::ENGINE2_OIL_PRESS;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine2OilPress),
                          sizeof(newData->commonData.engine2OilPress));
    }

    // egt
    if (d_currentAirplaneSettings.hasEgt)
    {
        if (fabs(d_lastPropData.engine1Egt - newData->engine1Egt)
            >= d_currentAirplaneSettings.egtEpsilon)
        {
            d_lastPropData.engine1Egt = newData->engine1Egt;
            id = SimconnectIds::ENGINE1_EGT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->engine1Egt),
                              sizeof(newData->engine1Egt));
        }
        if (fabs(d_lastPropData.engine2Egt - newData->engine2Egt)
            >= d_currentAirplaneSettings.egtEpsilon)
        {
            d_lastPropData.engine2Egt = newData->engine2Egt;
            id = SimconnectIds::ENGINE2_EGT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->engine2Egt),
                              sizeof(newData->engine2Egt));
        }
    }


    // flaps\spoilers
    if (d_currentAirplaneSettings.hasFlaps)
    {
        // flaps
        if (fabs(d_lastPropData.commonData.flapsLeftAngle
                 + d_lastPropData.commonData.flapsRightAngle - newData->commonData.flapsLeftAngle
                 - newData->commonData.flapsRightAngle)
            >= 1.0)
        {
            d_lastPropData.commonData.flapsLeftAngle = newData->commonData.flapsLeftAngle;
            d_lastPropData.commonData.flapsRightAngle = newData->commonData.flapsRightAngle;

            newData->commonData.flapsRightAngle
              = (newData->commonData.flapsLeftAngle + newData->commonData.flapsRightAngle) / 2.0;
            id = SimconnectIds::FLAPS_ANGLE;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.flapsRightAngle),
                              sizeof(newData->commonData.flapsRightAngle));
        }

        // spoilers
        if (d_currentAirplaneSettings.hasSpoilers)
            if (fabs(d_lastPropData.commonData.spoilersLeftPct
                     + d_lastPropData.commonData.spoilersRightPct
                     - newData->commonData.spoilersLeftPct - newData->commonData.spoilersRightPct)
                >= 1.0)
            {
                d_lastPropData.commonData.spoilersLeftPct = newData->commonData.spoilersLeftPct;
                d_lastPropData.commonData.spoilersRightPct = newData->commonData.spoilersRightPct;

                newData->commonData.spoilersRightPct
                  = (newData->commonData.spoilersLeftPct + newData->commonData.spoilersRightPct)
                    / 2.0;
                id = SimconnectIds::SPOILERS_PCT;
                dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<char *>(&newData->commonData.spoilersRightPct),
                                  sizeof(newData->commonData.spoilersRightPct));
            }
    }

    // elev trim
    if (d_currentAirplaneSettings.hasElevTrim)
        if (fabs(d_lastJetData.commonData.elevTrimPct - newData->commonData.elevTrimPct) >= 0.002)
        {
            d_lastJetData.commonData.elevTrimPct = newData->commonData.elevTrimPct;
            id = SimconnectIds::ELEV_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.elevTrimPct),
                              sizeof(newData->commonData.elevTrimPct));
        }

    // rudder trim
    if (d_currentAirplaneSettings.hasRudderTrim)
        if (fabs(d_lastJetData.commonData.rudderTrimPct - newData->commonData.rudderTrimPct)
            >= 0.002)
        {
            d_lastJetData.commonData.rudderTrimPct = newData->commonData.rudderTrimPct;
            id = SimconnectIds::RUDD_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.rudderTrimPct),
                              sizeof(newData->commonData.rudderTrimPct));
        }

    // aileron trim
    if (d_currentAirplaneSettings.hasAileronTrim)
        if (fabs(d_lastJetData.commonData.aileronTrimPct - newData->commonData.aileronTrimPct)
            >= 0.002)
        {
            d_lastJetData.commonData.aileronTrimPct = newData->commonData.aileronTrimPct;
            id = SimconnectIds::AIL_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.aileronTrimPct),
                              sizeof(newData->commonData.aileronTrimPct));
        }

    if (!dataToSend.isEmpty())
        emit sendData(dataToSend);
}
