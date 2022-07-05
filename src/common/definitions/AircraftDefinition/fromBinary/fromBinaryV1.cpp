#include "../AircraftDefinition.hpp"
#include "common/converters/basicConverters.hpp"

namespace definitions
{

AircraftDefinition AircraftDefinition::fromBinaryV1(QIODevice &data, FileVersion version)
{
    AircraftDefinition ret;
    Converters::convert(data, ret.type);

    switch (ret.type)
    {
        case AircraftType::JET:
        {
            ret.gauge1Type = SwitchingGaugeType::N1;
            ret.gauge2Type = SwitchingGaugeType::N2;
            ret.gauge3Type = SwitchingGaugeType::ENGINE_TEMP;
            ret.gauge4Type = SwitchingGaugeType::NONE;

            ret.firstGauge = GaugeDefinition::fromBinary(data, version);
            ret.secondGauge = GaugeDefinition::fromBinary(data, version);
            ret.thirdGauge = GaugeDefinition::fromBinary(data, version);

            Converters::convert(data, ret.hasApu);
            ret.engineTempType = Converters::convert<bool>(data) ? TemperatureGaugeType::EGT : TemperatureGaugeType::ITT;

            ret.hasSecondaryTempGauge = false;
            break;
        }
        case AircraftType::PROP:
        {
            ret.gauge3Type = SwitchingGaugeType::NONE;
            ret.gauge4Type = SwitchingGaugeType::NONE;

            ret.firstGauge = GaugeDefinition::fromBinary(data, version);
            ret.secondGauge = GaugeDefinition::fromBinary(data, version);

            ret.secondaryTempGauge = GaugeDefinition::fromBinary(data, version);
            ret.secondaryTempType = TemperatureGaugeType::EGT;
            Converters::convert(data, ret.hasSecondaryTempGauge);

            ret.gauge1Type = Converters::convert<bool>(data) ? SwitchingGaugeType::PROP_RPM : SwitchingGaugeType::RPM;
            bool secondIsLoad = Converters::convert<bool>(data);

            if (secondIsLoad)
            {
                ret.gauge2Type = SwitchingGaugeType::POWER_PCT;
                Converters::convert(data, ret.maxPower);
            }
            else
            {
                ret.gauge2Type = SwitchingGaugeType::MANIFOLD_PRESSURE;
                ret.maxPower = 1;
            }

            ret.hasApu = false;
            break;
        }
        case AircraftType::TURBOPROP:
        {
            ret.gauge1Type = SwitchingGaugeType::N1;
            ret.gauge3Type = SwitchingGaugeType::ENGINE_TEMP;

            ret.engineTempType = TemperatureGaugeType::ITT;

            ret.firstGauge = GaugeDefinition::fromBinary(data, version);
            ret.secondGauge = GaugeDefinition::fromBinary(data, version);
            ret.thirdGauge = GaugeDefinition::fromBinary(data, version);
            ret.fourthGauge = GaugeDefinition::fromBinary(data, version);

            ret.secondaryTempGauge = GaugeDefinition::fromBinary(data, version);
            ret.secondaryTempType = TemperatureGaugeType::EGT;
            Converters::convert(data, ret.hasSecondaryTempGauge);

            ret.gauge4Type = Converters::convert<bool>(data) ? SwitchingGaugeType::PROP_RPM : SwitchingGaugeType::RPM;
            ret.gauge2Type = Converters::convert<bool>(data) ? SwitchingGaugeType::TORQUE_PCT : SwitchingGaugeType::TORQUE;

            ret.hasApu = false;
            break;
        }
        default:
            break;
    }

    Converters::convertString(data, ret.name);

    ret.fuelQtyGauge = GaugeDefinition::fromBinary(data, version);
    ret.fuelFlowGauge = GaugeDefinition::fromBinary(data, version);
    ret.oilTempGauge = GaugeDefinition::fromBinary(data, version);
    ret.oilPressGauge = GaugeDefinition::fromBinary(data, version);

    Converters::convert(data, ret.hasFlaps);
    Converters::convert(data, ret.hasSpoilers);

    Converters::convert(data, ret.hasElevatorTrim);
    Converters::convert(data, ret.hasRudderTrim);
    Converters::convert(data, ret.hasAileronTrim);

    ret.fuelQtyByWeight = !Converters::convert<bool>(data);
    ret.fuelFlowByWeight = !Converters::convert<bool>(data);

    ret.numEngines = Converters::convert<int8_t>(data);
    ret.singleTank = Converters::convert<int8_t>(data) == 1;

    Converters::convert(data, ret.lowLimit);
    Converters::convert(data, ret.flapsBegin);
    Converters::convert(data, ret.flapsEnd);
    Converters::convert(data, ret.greenBegin);
    Converters::convert(data, ret.greenEnd);
    Converters::convert(data, ret.yellowBegin);
    Converters::convert(data, ret.yellowEnd);
    Converters::convert(data, ret.redBegin);
    Converters::convert(data, ret.redEnd);
    Converters::convert(data, ret.highLimit);

    Converters::convert(data, ret.noColors);
    Converters::convert(data, ret.dynamicBarberpole);

    return ret;
}

}  // namespace definitions
