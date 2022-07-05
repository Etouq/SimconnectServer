#include "../AircraftDefinition.hpp"
#include "common/converters/basicConverters.hpp"

namespace definitions
{

AircraftDefinition AircraftDefinition::fromBinaryV2(QIODevice &data, FileVersion version)
{
    AircraftDefinition ret = fromBinaryV1(data, version);

    ret.refSpeedDefaults = { { Converters::convert<uint16_t>(data), "r" },
                             { Converters::convert<uint16_t>(data), "x" },
                             { Converters::convert<uint16_t>(data), "y" },
                             { Converters::convert<uint16_t>(data), "ap" } };

    return ret;
}

}  // namespace definitions
