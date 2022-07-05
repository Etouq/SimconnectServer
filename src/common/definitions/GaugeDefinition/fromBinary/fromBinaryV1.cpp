#include "../GaugeDefinition.hpp"
#include "common/converters/listConverters.hpp"

namespace definitions
{

GaugeDefinition GaugeDefinition::fromBinaryV1(QIODevice &data)
{
    GaugeDefinition ret;

    Converters::convertString(data, ret.title);
    Converters::convertString(data, ret.unitString);

    Converters::convert(data, ret.minValue);
    Converters::convert(data, ret.maxValue);

    Converters::convertList(data, ret.colorZones);
    Converters::convertList(data, ret.grads);
    Converters::convertList(data, ret.textGrads);

    Converters::convert(data, ret.textIncrement);
    Converters::convert(data, ret.textNumDigits);

    Converters::convert(data, ret.forceTextColor);
    Converters::convert(data, ret.textForcedColor);

    Converters::convert(data, ret.hasMinRedBlink);
    Converters::convert(data, ret.minRedBlinkThreshold);
    Converters::convert(data, ret.hasMaxRedBlink);
    Converters::convert(data, ret.maxRedBlinkThreshold);

    Converters::convert(data, ret.noText);

    Converters::convert(data, ret.unit);

    return ret;
}

}  // namespace definitions
