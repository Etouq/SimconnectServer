#include "EngineHandler.hpp"
#include "common/appendData.hpp"
#include "common/dataIdentifiers.hpp"

namespace handler::engine
{

QByteArray EngineHandler::processData(const unsigned long *raw)
{
    DataStruct newData(*reinterpret_cast<const DataStruct *>(raw));
    QByteArray dataToSend;

    switch (d_numGauges)
    {
        case 4:
        {
            if (std::abs(d_previous.fourthGauge - newData.fourthGauge) >= d_fourthGaugeEpsilon)
            {
                d_previous.fourthGauge = newData.fourthGauge;
                if (d_gauge4IsPowerPct)
                    newData.fourthGauge /= d_maxPower;

                util::appendData(MfdIdentifier::ENGINE_FOURTH_GAUGE, d_engineIdx, newData.fourthGauge, dataToSend);
            }

            [[fallthrough]];
        }
        case 3:
        {
            if (std::abs(d_previous.thirdGauge - newData.thirdGauge) >= d_thirdGaugeEpsilon)
            {
                d_previous.thirdGauge = newData.thirdGauge;
                if (d_gauge3IsPowerPct)
                    newData.thirdGauge /= d_maxPower;

                util::appendData(MfdIdentifier::ENGINE_THIRD_GAUGE, d_engineIdx, newData.thirdGauge, dataToSend);
            }

            [[fallthrough]];
        }
        case 2:
        {
            if (std::abs(d_previous.firstGauge - newData.firstGauge) >= d_firstGaugeEpsilon)
            {
                d_previous.firstGauge = newData.firstGauge;
                if (d_gauge1IsPowerPct)
                    newData.firstGauge /= d_maxPower;

                util::appendData(MfdIdentifier::ENGINE_FIRST_GAUGE, d_engineIdx, newData.firstGauge, dataToSend);
            }

            if (std::abs(d_previous.secondGauge - newData.secondGauge) >= d_secondGaugeEpsilon)
            {
                d_previous.secondGauge = newData.secondGauge;
                if (d_gauge2IsPowerPct)
                    newData.secondGauge /= d_maxPower;

                util::appendData(MfdIdentifier::ENGINE_SECOND_GAUGE, d_engineIdx, newData.secondGauge, dataToSend);
            }
        }
    }


    if (std::abs(d_previous.fuelFlow - newData.fuelFlow) >= d_fuelFlowEpsilon)
    {
        d_previous.fuelFlow = newData.fuelFlow;
        newData.fuelFlow *= d_fuelFlowByWeight ? 3600.0 : 3.785411784;
        util::appendData(MfdIdentifier::ENGINE_FUEL_FLOW, d_engineIdx, newData.fuelFlow, dataToSend);
    }

    if (std::abs(d_previous.oilTemp - newData.oilTemp) >= d_oilTempEpsilon)
    {
        d_previous.oilTemp = newData.oilTemp;
        util::appendData(MfdIdentifier::ENGINE_OIL_TEMP, d_engineIdx, newData.oilTemp, dataToSend);
    }

    if (d_hasSecondaryTempGauge && std::abs(d_previous.secondaryEngineTemp - newData.secondaryEngineTemp) >= d_secondaryTempEpsilon)
    {
        d_previous.secondaryEngineTemp = newData.secondaryEngineTemp;
        util::appendData(MfdIdentifier::ENGINE_SECONDARY_TEMP, d_engineIdx, newData.secondaryEngineTemp, dataToSend);
    }

    if (std::abs(d_previous.oilPress - newData.oilPress) >= d_oilPressEpsilon)
    {
        d_previous.oilPress = newData.oilPress;
        util::appendData(MfdIdentifier::ENGINE_OIL_PRESS, d_engineIdx, newData.oilPress, dataToSend);
    }

    return dataToSend;
}

}
