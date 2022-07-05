#include "EngineHandler.hpp"
#include "common/appendData.hpp"
#include "common/dataIdentifiers.hpp"

namespace handler::engine
{

QByteArray EngineHandler::sendCurrentData()
{
    QByteArray dataToSend;

    util::appendData(MfdIdentifier::ENGINE_FIRST_GAUGE,
                     d_engineIdx,
                     d_gauge1IsPowerPct ? d_previous.firstGauge : d_previous.firstGauge / d_maxPower,
                     dataToSend);
    util::appendData(MfdIdentifier::ENGINE_SECOND_GAUGE,
                     d_engineIdx,
                     d_gauge2IsPowerPct ? d_previous.secondGauge : d_previous.secondGauge / d_maxPower,
                     dataToSend);
    util::appendData(MfdIdentifier::ENGINE_THIRD_GAUGE,
                     d_engineIdx,
                     d_gauge3IsPowerPct ? d_previous.thirdGauge : d_previous.thirdGauge / d_maxPower,
                     dataToSend);
    util::appendData(MfdIdentifier::ENGINE_FOURTH_GAUGE,
                     d_engineIdx,
                     d_gauge4IsPowerPct ? d_previous.fourthGauge : d_previous.fourthGauge / d_maxPower,
                     dataToSend);


    util::appendData(MfdIdentifier::ENGINE_FUEL_FLOW,
                     d_engineIdx,
                     d_previous.fuelFlow * (d_fuelFlowByWeight ? 3600.0 : 3.785411784),
                     dataToSend);
    util::appendData(MfdIdentifier::ENGINE_OIL_TEMP, d_engineIdx, d_previous.oilTemp, dataToSend);
    util::appendData(MfdIdentifier::ENGINE_SECONDARY_TEMP, d_engineIdx, d_previous.secondaryEngineTemp, dataToSend);
    util::appendData(MfdIdentifier::ENGINE_OIL_PRESS, d_engineIdx, d_previous.oilPress, dataToSend);

    return dataToSend;
}

}  // namespace handler::engine
