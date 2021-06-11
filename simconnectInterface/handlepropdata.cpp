#include "simconnectinterface.h"
using namespace std;


void SimconnectInterface::handlePropSingleEngdata(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData)
{
    PropData *newData = reinterpret_cast<PropData *>(&pObjData->dwData);
    QByteArray dataToSend;
    DataIdentifiers id;

    //rpm
    if (fabs(d_lastPropData.engine1Rpm - newData->engine1Rpm) >= 1.0)
    {
        d_lastPropData.engine1Rpm = newData->engine1Rpm;
        id = DataIdentifiers::ENGINE1_RPM;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1Rpm), sizeof(newData->engine1Rpm));
    }

    //second
    if (fabs(d_lastPropData.engine1Second - newData->engine1Second) >= 0.05)
    {
        d_lastPropData.engine1Second = newData->engine1Second;
        newData->engine1Second /= d_currentAirplaneSettings.secondDivFactor;
        id = DataIdentifiers::ENGINE1_SECOND;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1Second), sizeof(newData->engine1Second));
    }

    //fuel qty
    if (d_currentAirplaneSettings.numTanks == 1)
    {
        if(fabs(d_lastPropData.commonData.fuelQtyTotal - newData->commonData.fuelQtyTotal) >= 0.02)
        {
            d_lastPropData.commonData.fuelQtyTotal = newData->commonData.fuelQtyTotal;
            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyTotal *= d_lastSlowData.fuelWeight;
            id = DataIdentifiers::ENGINE1_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyTotal), sizeof(newData->commonData.fuelQtyTotal));
        }
    }
    else
    {
        if(fabs(d_lastPropData.commonData.fuelQtyLeft - newData->commonData.fuelQtyLeft) >= 0.02)
        {
            d_lastPropData.commonData.fuelQtyLeft = newData->commonData.fuelQtyLeft;
            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyLeft *= d_lastSlowData.fuelWeight;
            id = DataIdentifiers::ENGINE1_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyLeft), sizeof(newData->commonData.fuelQtyLeft));
        }
        if(fabs(d_lastPropData.commonData.fuelQtyRight - newData->commonData.fuelQtyRight) >= 0.02)
        {
            d_lastPropData.commonData.fuelQtyRight = newData->commonData.fuelQtyRight;
            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyRight *= d_lastSlowData.fuelWeight;
            id = DataIdentifiers::ENGINE2_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyRight), sizeof(newData->commonData.fuelQtyRight));
        }
    }

    //fuel flow
    if (d_currentAirplaneSettings.fuelFlowByVolume)
    {
        if(fabs(d_lastPropData.commonData.engine1FuelFlowVolume - newData->commonData.engine1FuelFlowVolume) >= 0.1)
        {
            d_lastPropData.commonData.engine1FuelFlowVolume = newData->commonData.engine1FuelFlowVolume;
            id = DataIdentifiers::ENGINE1_FUEL_FLOW;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1FuelFlowVolume), sizeof(newData->commonData.engine1FuelFlowVolume));
        }
    }
    else
    {
        if(fabs(d_lastPropData.commonData.engine1FuelFlowWeight - newData->commonData.engine1FuelFlowWeight) >= 0.00003)
        {
            d_lastPropData.commonData.engine1FuelFlowWeight = newData->commonData.engine1FuelFlowWeight;
            newData->commonData.engine1FuelFlowWeight *= 3600.0;
            id = DataIdentifiers::ENGINE1_FUEL_FLOW;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1FuelFlowWeight), sizeof(newData->commonData.engine1FuelFlowWeight));
        }
    }

    //oil temp
    if(fabs(d_lastPropData.commonData.engine1OilTemp - newData->commonData.engine1OilTemp) >= 0.1)
    {
        d_lastPropData.commonData.engine1OilTemp = newData->commonData.engine1OilTemp;
        id = DataIdentifiers::ENGINE1_OIL_TEMP;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1OilTemp), sizeof(newData->commonData.engine1OilTemp));
    }

    //oil press
    if(fabs(d_lastPropData.commonData.engine1OilPress - newData->commonData.engine1OilPress) >= 0.8)
    {
        d_lastPropData.commonData.engine1OilPress = newData->commonData.engine1OilPress;
        id = DataIdentifiers::ENGINE1_OIL_PRESS;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1OilPress), sizeof(newData->commonData.engine1OilPress));
    }

    //egt
    if (d_currentAirplaneSettings.hasEgt)
        if (fabs(d_lastPropData.commonData.engine1Egt - newData->commonData.engine1Egt) >= 0.1)
        {
            d_lastPropData.commonData.engine1Egt = newData->commonData.engine1Egt;
            id = DataIdentifiers::ENGINE1_EGT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1Egt), sizeof(newData->commonData.engine1Egt));
        }

    //flaps\spoilers
    if (d_currentAirplaneSettings.hasFlaps)
    {
        //flaps
        if (fabs(d_lastPropData.commonData.flapsLeftAngle + d_lastPropData.commonData.flapsRightAngle - newData->commonData.flapsLeftAngle - newData->commonData.flapsRightAngle) >= 1.0)
        {
            d_lastPropData.commonData.flapsLeftAngle = newData->commonData.flapsLeftAngle;
            d_lastPropData.commonData.flapsRightAngle = newData->commonData.flapsRightAngle;

            newData->commonData.flapsRightAngle = (newData->commonData.flapsLeftAngle + newData->commonData.flapsRightAngle) / 2.0;
            id = DataIdentifiers::FLAPS_ANGLE;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.flapsRightAngle), sizeof(newData->commonData.flapsRightAngle));
        }

        //spoilers
        if (d_currentAirplaneSettings.hasSpoilers)
            if (fabs(d_lastPropData.commonData.spoilersLeftPct + d_lastPropData.commonData.spoilersRightPct - newData->commonData.spoilersLeftPct - newData->commonData.spoilersRightPct) >= 1.0)
            {
                d_lastPropData.commonData.spoilersLeftPct = newData->commonData.spoilersLeftPct;
                d_lastPropData.commonData.spoilersRightPct = newData->commonData.spoilersRightPct;

                newData->commonData.spoilersRightPct = (newData->commonData.spoilersLeftPct + newData->commonData.spoilersRightPct) / 2.0;
                id = DataIdentifiers::SPOILERS_PCT;
                dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<char *>(&newData->commonData.spoilersRightPct), sizeof(newData->commonData.spoilersRightPct));
            }
    }

    //elev trim
    if (fabs(d_lastPropData.commonData.elevTrimPct - newData->commonData.elevTrimPct) >= 0.002)
    {
        d_lastPropData.commonData.elevTrimPct = newData->commonData.elevTrimPct;
        id = DataIdentifiers::ELEV_TRIM_PCT;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.elevTrimPct), sizeof(newData->commonData.elevTrimPct));
    }

    //rudder trim
    if (d_currentAirplaneSettings.hasRudderTrim)
        if (fabs(d_lastPropData.commonData.rudderTrimPct - newData->commonData.rudderTrimPct) >= 0.002)
        {
            d_lastPropData.commonData.rudderTrimPct = newData->commonData.rudderTrimPct;
            id = DataIdentifiers::RUDD_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.rudderTrimPct), sizeof(newData->commonData.rudderTrimPct));
        }

    //aileron trim
    if (d_currentAirplaneSettings.hasAileronTrim)
        if (fabs(d_lastPropData.commonData.aileronTrimPct - newData->commonData.aileronTrimPct) >= 0.002)
        {
            d_lastPropData.commonData.aileronTrimPct = newData->commonData.aileronTrimPct;
            id = DataIdentifiers::AIL_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.aileronTrimPct), sizeof(newData->commonData.aileronTrimPct));
        }

    if (!dataToSend.isEmpty())
        emit sendData(dataToSend);
}


void SimconnectInterface::handlePropTwinEngdata(SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData)
{
    PropData *newData = reinterpret_cast<PropData *>(&pObjData->dwData);
    QByteArray dataToSend;
    DataIdentifiers id;

    //rpm
    if (fabs(d_lastPropData.engine1Rpm - newData->engine1Rpm) >= 1.0)
    {
        d_lastPropData.engine1Rpm = newData->engine1Rpm;
        id = DataIdentifiers::ENGINE1_RPM;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1Rpm), sizeof(newData->engine1Rpm));
    }
    if (fabs(d_lastPropData.engine2Rpm - newData->engine2Rpm) >= 1.0)
    {
        d_lastPropData.engine2Rpm = newData->engine2Rpm;
        id = DataIdentifiers::ENGINE2_RPM;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine2Rpm), sizeof(newData->engine2Rpm));
    }

    //second
    if (fabs(d_lastPropData.engine1Second - newData->engine1Second) >= 0.05)
    {
        d_lastPropData.engine1Second = newData->engine1Second;
        newData->engine1Second /= d_currentAirplaneSettings.secondDivFactor;
        id = DataIdentifiers::ENGINE1_SECOND;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine1Second), sizeof(newData->engine1Second));
    }
    if (fabs(d_lastPropData.engine2Second - newData->engine2Second) >= 0.05)
    {
        d_lastPropData.engine2Second = newData->engine2Second;
        newData->engine2Second /= d_currentAirplaneSettings.secondDivFactor;
        id = DataIdentifiers::ENGINE2_SECOND;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->engine2Second), sizeof(newData->engine2Second));
    }

    //fuel qty
    if (d_currentAirplaneSettings.numTanks == 1)
    {
        if(fabs(d_lastPropData.commonData.fuelQtyTotal - newData->commonData.fuelQtyTotal) >= 0.02)
        {
            d_lastPropData.commonData.fuelQtyTotal = newData->commonData.fuelQtyTotal;
            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyTotal *= d_lastSlowData.fuelWeight;
            id = DataIdentifiers::ENGINE1_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyTotal), sizeof(newData->commonData.fuelQtyTotal));
        }
    }
    else
    {
        if(fabs(d_lastPropData.commonData.fuelQtyLeft - newData->commonData.fuelQtyLeft) >= 0.02)
        {
            d_lastPropData.commonData.fuelQtyLeft = newData->commonData.fuelQtyLeft;
            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyLeft *= d_lastSlowData.fuelWeight;
            id = DataIdentifiers::ENGINE1_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyLeft), sizeof(newData->commonData.fuelQtyLeft));
        }
        if(fabs(d_lastPropData.commonData.fuelQtyRight - newData->commonData.fuelQtyRight) >= 0.02)
        {
            d_lastPropData.commonData.fuelQtyRight = newData->commonData.fuelQtyRight;
            if (!d_currentAirplaneSettings.fuelQtyByVolume)
                newData->commonData.fuelQtyRight *= d_lastSlowData.fuelWeight;
            id = DataIdentifiers::ENGINE2_FUEL_QTY;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.fuelQtyRight), sizeof(newData->commonData.fuelQtyRight));
        }
    }

    //fuel flow
    if (d_currentAirplaneSettings.fuelFlowByVolume)
    {
        if(fabs(d_lastPropData.commonData.engine1FuelFlowVolume - newData->commonData.engine1FuelFlowVolume) >= 0.1)
        {
            d_lastPropData.commonData.engine1FuelFlowVolume = newData->commonData.engine1FuelFlowVolume;
            id = DataIdentifiers::ENGINE1_FUEL_FLOW;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1FuelFlowVolume), sizeof(newData->commonData.engine1FuelFlowVolume));
        }
        if(fabs(d_lastPropData.commonData.engine2FuelFlowVolume - newData->commonData.engine2FuelFlowVolume) >= 0.1)
        {
            d_lastPropData.commonData.engine2FuelFlowVolume = newData->commonData.engine2FuelFlowVolume;
            id = DataIdentifiers::ENGINE2_FUEL_FLOW;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine2FuelFlowVolume), sizeof(newData->commonData.engine2FuelFlowVolume));
        }
    }
    else
    {
        if(fabs(d_lastPropData.commonData.engine1FuelFlowWeight - newData->commonData.engine1FuelFlowWeight) >= 0.00003)
        {
            d_lastPropData.commonData.engine1FuelFlowWeight = newData->commonData.engine1FuelFlowWeight;
            newData->commonData.engine1FuelFlowWeight *= 3600.0;
            id = DataIdentifiers::ENGINE1_FUEL_FLOW;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1FuelFlowWeight), sizeof(newData->commonData.engine1FuelFlowWeight));
        }
        if(fabs(d_lastPropData.commonData.engine2FuelFlowWeight - newData->commonData.engine2FuelFlowWeight) >= 0.00003)
        {
            d_lastPropData.commonData.engine2FuelFlowWeight = newData->commonData.engine2FuelFlowWeight;
            newData->commonData.engine2FuelFlowWeight *= 3600.0;
            id = DataIdentifiers::ENGINE2_FUEL_FLOW;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine2FuelFlowWeight), sizeof(newData->commonData.engine2FuelFlowWeight));
        }
    }

    //oil temp
    if(fabs(d_lastPropData.commonData.engine1OilTemp - newData->commonData.engine1OilTemp) >= 0.1)
    {
        d_lastPropData.commonData.engine1OilTemp = newData->commonData.engine1OilTemp;
        id = DataIdentifiers::ENGINE1_OIL_TEMP;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1OilTemp), sizeof(newData->commonData.engine1OilTemp));
    }
    if(fabs(d_lastPropData.commonData.engine2OilTemp - newData->commonData.engine2OilTemp) >= 0.1)
    {
        d_lastPropData.commonData.engine2OilTemp = newData->commonData.engine2OilTemp;
        id = DataIdentifiers::ENGINE2_OIL_TEMP;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine2OilTemp), sizeof(newData->commonData.engine2OilTemp));
    }

    //oil press
    if(fabs(d_lastPropData.commonData.engine1OilPress - newData->commonData.engine1OilPress) >= 0.8)
    {
        d_lastPropData.commonData.engine1OilPress = newData->commonData.engine1OilPress;
        id = DataIdentifiers::ENGINE1_OIL_PRESS;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1OilPress), sizeof(newData->commonData.engine1OilPress));
    }
    if(fabs(d_lastPropData.commonData.engine2OilPress - newData->commonData.engine2OilPress) >= 0.8)
    {
        d_lastPropData.commonData.engine2OilPress = newData->commonData.engine2OilPress;
        id = DataIdentifiers::ENGINE2_OIL_PRESS;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine2OilPress), sizeof(newData->commonData.engine2OilPress));
    }

    //egt
    if (d_currentAirplaneSettings.hasEgt)
    {
        if (fabs(d_lastPropData.commonData.engine1Egt - newData->commonData.engine1Egt) >= 0.1)
        {
            d_lastPropData.commonData.engine1Egt = newData->commonData.engine1Egt;
            id = DataIdentifiers::ENGINE1_EGT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine1Egt), sizeof(newData->commonData.engine1Egt));
        }
        if (fabs(d_lastPropData.commonData.engine2Egt - newData->commonData.engine2Egt) >= 0.1)
        {
            d_lastPropData.commonData.engine2Egt = newData->commonData.engine2Egt;
            id = DataIdentifiers::ENGINE2_EGT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.engine2Egt), sizeof(newData->commonData.engine2Egt));
        }
    }


    //flaps\spoilers
    if (d_currentAirplaneSettings.hasFlaps)
    {
        //flaps
        if (fabs(d_lastPropData.commonData.flapsLeftAngle + d_lastPropData.commonData.flapsRightAngle - newData->commonData.flapsLeftAngle - newData->commonData.flapsRightAngle) >= 1.0)
        {
            d_lastPropData.commonData.flapsLeftAngle = newData->commonData.flapsLeftAngle;
            d_lastPropData.commonData.flapsRightAngle = newData->commonData.flapsRightAngle;

            newData->commonData.flapsRightAngle = (newData->commonData.flapsLeftAngle + newData->commonData.flapsRightAngle) / 2.0;
            id = DataIdentifiers::FLAPS_ANGLE;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.flapsRightAngle), sizeof(newData->commonData.flapsRightAngle));
        }

        //spoilers
        if (d_currentAirplaneSettings.hasSpoilers)
            if (fabs(d_lastPropData.commonData.spoilersLeftPct + d_lastPropData.commonData.spoilersRightPct - newData->commonData.spoilersLeftPct - newData->commonData.spoilersRightPct) >= 1.0)
            {
                d_lastPropData.commonData.spoilersLeftPct = newData->commonData.spoilersLeftPct;
                d_lastPropData.commonData.spoilersRightPct = newData->commonData.spoilersRightPct;

                newData->commonData.spoilersRightPct = (newData->commonData.spoilersLeftPct + newData->commonData.spoilersRightPct) / 2.0;
                id = DataIdentifiers::SPOILERS_PCT;
                dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
                dataToSend.append(reinterpret_cast<char *>(&newData->commonData.spoilersRightPct), sizeof(newData->commonData.spoilersRightPct));
            }
    }

    //elev trim
    if (fabs(d_lastPropData.commonData.elevTrimPct - newData->commonData.elevTrimPct) >= 0.002)
    {
        d_lastPropData.commonData.elevTrimPct = newData->commonData.elevTrimPct;
        id = DataIdentifiers::ELEV_TRIM_PCT;
        dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
        dataToSend.append(reinterpret_cast<char *>(&newData->commonData.elevTrimPct), sizeof(newData->commonData.elevTrimPct));
    }

    //rudder trim
    if (d_currentAirplaneSettings.hasRudderTrim)
        if (fabs(d_lastPropData.commonData.rudderTrimPct - newData->commonData.rudderTrimPct) >= 0.002)
        {
            d_lastPropData.commonData.rudderTrimPct = newData->commonData.rudderTrimPct;
            id = DataIdentifiers::RUDD_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.rudderTrimPct), sizeof(newData->commonData.rudderTrimPct));
        }

    //aileron trim
    if (d_currentAirplaneSettings.hasAileronTrim)
        if (fabs(d_lastPropData.commonData.aileronTrimPct - newData->commonData.aileronTrimPct) >= 0.002)
        {
            d_lastPropData.commonData.aileronTrimPct = newData->commonData.aileronTrimPct;
            id = DataIdentifiers::AIL_TRIM_PCT;
            dataToSend.append(reinterpret_cast<char *>(&id), sizeof(id));
            dataToSend.append(reinterpret_cast<char *>(&newData->commonData.aileronTrimPct), sizeof(newData->commonData.aileronTrimPct));
        }

    if (!dataToSend.isEmpty())
        emit sendData(dataToSend);

}






































