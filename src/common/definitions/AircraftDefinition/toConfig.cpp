#include "AircraftDefinition.hpp"
#include "common/definitions/AircraftConfig.hpp"

namespace definitions
{

AircraftConfig AircraftDefinition::toConfig() const
{
    AircraftConfig ret;

    ret.type = type;

    ret.numEngines = numEngines;
    ret.singleTank = singleTank;

    ret.firstGaugeEpsilon = gauge1Type == SwitchingGaugeType::NONE ? 10000 : firstGauge.getEpsilon(numEngines != 4);
    ret.secondGaugeEpsilon = gauge2Type == SwitchingGaugeType::NONE ? 10000 : secondGauge.getEpsilon(numEngines != 4);
    ret.thirdGaugeEpsilon = gauge3Type == SwitchingGaugeType::NONE ? 10000 : thirdGauge.getEpsilon(numEngines + (gauge4Type == SwitchingGaugeType::NONE ? 3 : 4) <= 5);
    ret.fourthGaugeEpsilon = gauge4Type == SwitchingGaugeType::NONE ? 10000 : fourthGauge.getEpsilon(false);

    ret.fuelQtyEpsilon = fuelQtyGauge.getEpsilon(false);
    ret.fuelFlowEpsilon = fuelFlowGauge.getEpsilon(false);
    ret.oilTempEpsilon = oilTempGauge.getEpsilon(false);
    ret.secondaryTempEpsilon = hasSecondaryTempGauge ? secondaryTempGauge.getEpsilon(false) : 10000;
    ret.oilPressEpsilon = oilPressGauge.getEpsilon(false);

    ret.gauge1Type = gauge1Type;
    ret.gauge2Type = gauge2Type;
    ret.gauge3Type = gauge3Type;
    ret.gauge4Type = gauge4Type;

    ret.engineTempType = engineTempType;

    ret.maxPower = (gauge1Type == SwitchingGaugeType::POWER && firstGauge.unit == Units::PERCENT) || (gauge2Type == SwitchingGaugeType::POWER && secondGauge.unit == Units::PERCENT) || (gauge3Type == SwitchingGaugeType::POWER && thirdGauge.unit == Units::PERCENT) || (gauge4Type == SwitchingGaugeType::POWER && fourthGauge.unit == Units::PERCENT) ? maxPower : 1.0;

    ret.hasApu = hasApu;

    ret.hasFlaps = hasFlaps;
    ret.hasSpoilers = hasSpoilers;

    ret.hasElevatorTrim = hasElevatorTrim;
    ret.hasRudderTrim = hasRudderTrim;
    ret.hasAileronTrim = hasAileronTrim;

    ret.fuelQtyByWeight = fuelQtyByWeight();
    ret.fuelFlowByWeight = fuelFlowByWeight();

    ret.hasSecondaryTempGauge = hasSecondaryTempGauge;
    ret.secondaryTempType = secondaryTempType;

    if (ret.fuelQtyByWeight)
        ret.fuelQtyEpsilon /= 4.0;

    if (ret.fuelFlowByWeight)
        ret.fuelFlowEpsilon /= 3600.0;
    else
        ret.fuelFlowEpsilon *= 0.2641720523; // placeholder until liters per hour is fixed (currently gives liters p/s)

    return ret;
}

}  // namespace definitions
