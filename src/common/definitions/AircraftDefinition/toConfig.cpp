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

    switch (numGauges())
    {
        case 2:
        {
            switch (numEngines)
            {
                case 1:
                {
                    ret.firstGaugeEpsilon = firstGauge.getEpsilon(true, gauge1Type, type, maxPower, maxTorque);
                    ret.secondGaugeEpsilon = secondGauge.getEpsilon(true, gauge2Type, type, maxPower, maxTorque);
                    ret.thirdGaugeEpsilon = 10000;
                    ret.fourthGaugeEpsilon = 10000;
                    break;
                }
                case 2:
                {
                    ret.firstGaugeEpsilon = firstGauge.getEpsilon(true, gauge1Type, type, maxPower, maxTorque);
                    ret.secondGaugeEpsilon = secondGauge.getEpsilon(true, gauge2Type, type, maxPower, maxTorque);
                    ret.thirdGaugeEpsilon = 10000;
                    ret.fourthGaugeEpsilon = 10000;
                    break;
                }
                case 4:
                {
                    ret.firstGaugeEpsilon = firstGauge.getEpsilon(false, gauge1Type, type, maxPower, maxTorque);
                    ret.secondGaugeEpsilon = secondGauge.getEpsilon(false, gauge2Type, type, maxPower, maxTorque);
                    ret.thirdGaugeEpsilon = 10000;
                    ret.fourthGaugeEpsilon = 10000;
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case 3:
        {
            switch (numEngines)
            {
                case 1:
                {
                    ret.firstGaugeEpsilon = firstGauge.getEpsilon(true, gauge1Type, type, maxPower, maxTorque);
                    ret.secondGaugeEpsilon = secondGauge.getEpsilon(true, gauge2Type, type, maxPower, maxTorque);
                    ret.thirdGaugeEpsilon = thirdGauge.getEpsilon(true, gauge3Type, type, maxPower, maxTorque);
                    ret.fourthGaugeEpsilon = 10000;
                    break;
                }
                case 2:
                {
                    ret.firstGaugeEpsilon = firstGauge.getEpsilon(true, gauge1Type, type, maxPower, maxTorque);
                    ret.secondGaugeEpsilon = secondGauge.getEpsilon(true, gauge2Type, type, maxPower, maxTorque);
                    ret.thirdGaugeEpsilon = thirdGauge.getEpsilon(true, gauge3Type, type, maxPower, maxTorque);
                    ret.fourthGaugeEpsilon = 10000;
                    break;
                }
                case 4:
                {
                    ret.firstGaugeEpsilon = firstGauge.getEpsilon(false, gauge1Type, type, maxPower, maxTorque);
                    ret.secondGaugeEpsilon = secondGauge.getEpsilon(false, gauge2Type, type, maxPower, maxTorque);
                    ret.thirdGaugeEpsilon = thirdGauge.getEpsilon(false, gauge3Type, type, maxPower, maxTorque);
                    ret.fourthGaugeEpsilon = 10000;
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case 4:
        {
            switch (numEngines)
            {
                case 1:
                {
                    ret.firstGaugeEpsilon = firstGauge.getEpsilon(true, gauge1Type, type, maxPower, maxTorque);
                    ret.secondGaugeEpsilon = secondGauge.getEpsilon(true, gauge2Type, type, maxPower, maxTorque);
                    ret.thirdGaugeEpsilon = thirdGauge.getEpsilon(true, gauge3Type, type, maxPower, maxTorque);
                    ret.fourthGaugeEpsilon = fourthGauge.getEpsilon(true, gauge4Type, type, maxPower, maxTorque);
                    break;
                }
                case 2:
                {
                    ret.firstGaugeEpsilon = firstGauge.getEpsilon(true, gauge1Type, type, maxPower, maxTorque);
                    ret.secondGaugeEpsilon = secondGauge.getEpsilon(true, gauge2Type, type, maxPower, maxTorque);
                    ret.thirdGaugeEpsilon = thirdGauge.getEpsilon(false, gauge3Type, type, maxPower, maxTorque);
                    ret.fourthGaugeEpsilon = fourthGauge.getEpsilon(false, gauge4Type, type, maxPower, maxTorque);
                    break;
                }
                case 4:
                {
                    ret.firstGaugeEpsilon = firstGauge.getEpsilon(false, gauge1Type, type, maxPower, maxTorque);
                    ret.secondGaugeEpsilon = secondGauge.getEpsilon(false, gauge2Type, type, maxPower, maxTorque);
                    ret.thirdGaugeEpsilon = thirdGauge.getEpsilon(false, gauge3Type, type, maxPower, maxTorque);
                    ret.fourthGaugeEpsilon = fourthGauge.getEpsilon(false, gauge4Type, type, maxPower, maxTorque);
                    break;
                }
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }

    ret.fuelQtyEpsilon = fuelQtyGauge.getEpsilon(false);
    ret.fuelFlowEpsilon = fuelFlowGauge.getEpsilon(false);
    ret.oilTempEpsilon = oilTempGauge.getEpsilon(false);
    ret.secondaryTempEpsilon = hasSecondaryTempGauge ? secondaryTempGauge.getEpsilon(false) : 10000;
    ret.oilPressEpsilon = oilPressGauge.getEpsilon(false);

    ret.gauge1Type = gauge1Type;
    ret.gauge2Type = gauge2Type;
    ret.gauge3Type = gauge3Type;
    ret.gauge4Type = gauge4Type;

    ret.gauge1Unit = firstGauge.unit;
    ret.gauge2Unit = secondGauge.unit;
    ret.gauge3Unit = thirdGauge.unit;
    ret.gauge4Unit = fourthGauge.unit;

    ret.engineTempType = engineTempType;

    ret.maxPower = (gauge1Type == SwitchingGaugeType::POWER && firstGauge.unit == Units::PERCENT)
        || (gauge2Type == SwitchingGaugeType::POWER && secondGauge.unit == Units::PERCENT)
        || (gauge3Type == SwitchingGaugeType::POWER && thirdGauge.unit == Units::PERCENT)
        || (gauge4Type == SwitchingGaugeType::POWER && fourthGauge.unit == Units::PERCENT)
      ? maxPower * 550.0 // convert to ft*lbf/s since simconnect doesn't have hp as unit of power
      : 1.0;

    ret.maxTorque =
      type == AircraftType::PROP && (gauge1Type == SwitchingGaugeType::TORQUE && firstGauge.unit == Units::PERCENT)
        || (gauge2Type == SwitchingGaugeType::TORQUE && secondGauge.unit == Units::PERCENT)
        || (gauge3Type == SwitchingGaugeType::TORQUE && thirdGauge.unit == Units::PERCENT)
        || (gauge4Type == SwitchingGaugeType::TORQUE && fourthGauge.unit == Units::PERCENT)
      ? maxTorque
      : 1.0;

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
        ret.fuelFlowEpsilon *= 0.2641720523;  // placeholder until liters per hour is fixed (currently gives liters p/s)

    return ret;
}

}  // namespace definitions
