#include "../AircraftDefinition.hpp"
#include <QIODevice>

namespace definitions
{

AircraftDefinition AircraftDefinition::fromBinaryV2(QIODevice &data, FileVersion version)
{
    AircraftDefinition ret = fromBinaryV1(data, version);

    uint16_t vrSetting = 0;
    data.read(reinterpret_cast<char *>(&vrSetting), sizeof(vrSetting));
    uint16_t vxSetting = 0;
    data.read(reinterpret_cast<char *>(&vxSetting), sizeof(vxSetting));
    uint16_t vySetting = 0;
    data.read(reinterpret_cast<char *>(&vySetting), sizeof(vySetting));
    uint16_t vapSetting = 0;
    data.read(reinterpret_cast<char *>(&vapSetting), sizeof(vapSetting));

    ret.refSpeedDefaults = { { vrSetting, "r" },
                             { vxSetting, "x" },
                             { vySetting, "y" },
                             { vapSetting, "ap" } };

    return ret;
}

}  // namespace definitions
