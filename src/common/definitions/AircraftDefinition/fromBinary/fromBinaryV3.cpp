#include "../AircraftDefinition.hpp"
#include "common/converters/listConverters.hpp"

namespace definitions
{

AircraftDefinition AircraftDefinition::fromBinaryV3(QIODevice &data, FileVersion version)
{
    AircraftDefinition ret;

    Converters::convert(data, ret.type);

    Converters::convertString(data, ret.name);

    ret.firstGauge = GaugeDefinition::fromBinary(data, version);
    ret.secondGauge = GaugeDefinition::fromBinary(data, version);
    ret.thirdGauge = GaugeDefinition::fromBinary(data, version);
    ret.fourthGauge = GaugeDefinition::fromBinary(data, version);

    ret.fuelQtyGauge = GaugeDefinition::fromBinary(data, version);
    ret.fuelFlowGauge = GaugeDefinition::fromBinary(data, version);
    ret.oilTempGauge = GaugeDefinition::fromBinary(data, version);
    ret.secondaryTempGauge = GaugeDefinition::fromBinary(data, version);
    ret.oilPressGauge = GaugeDefinition::fromBinary(data, version);

    Converters::convert(data, ret.gauge1Type);
    Converters::convert(data, ret.gauge2Type);
    Converters::convert(data, ret.gauge3Type);
    Converters::convert(data, ret.gauge4Type);

    Converters::convert(data, ret.engineTempType);

    Converters::convert(data, ret.maxPower);

    Converters::convert(data, ret.hasApu);

    Converters::convert(data, ret.hasFlaps);
    Converters::convert(data, ret.hasSpoilers);

    Converters::convert(data, ret.hasElevatorTrim);
    Converters::convert(data, ret.hasRudderTrim);
    Converters::convert(data, ret.hasAileronTrim);

    Converters::convert(data, ret.fuelQtyByWeight);
    Converters::convert(data, ret.fuelFlowByWeight);

    Converters::convert(data, ret.hasSecondaryTempGauge);
    Converters::convert(data, ret.secondaryTempType);

    Converters::convert(data, ret.numEngines);
    Converters::convert(data, ret.singleTank);

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

    Converters::convertList(data, ret.refSpeedDefaults);

    return ret;
}

}  // namespace definitions
