#include "AircraftDefinition.hpp"

#include <string>

namespace definitions
{

QByteArray AircraftDefinition::toBinary() const
{
    std::string ret({ static_cast<char>(type) });

    ret.append({ static_cast<char>(name.toStdString().size()) });
    ret += name.toStdString();

    ret += firstGauge.toBinary();
    ret += secondGauge.toBinary();
    ret += thirdGauge.toBinary();
    ret += fourthGauge.toBinary();

    ret += fuelQtyGauge.toBinary();
    ret += fuelFlowGauge.toBinary();
    ret += oilTempGauge.toBinary();
    ret += secondaryTempGauge.toBinary();
    ret += oilPressGauge.toBinary();

    ret.append({ static_cast<char>(gauge1Type),
                 static_cast<char>(gauge2Type),
                 static_cast<char>(gauge3Type),
                 static_cast<char>(gauge4Type),
                 static_cast<char>(engineTempType) });

    ret.append(reinterpret_cast<const char *>(&maxPower), sizeof(maxPower));
    ret.append(reinterpret_cast<const char *>(&maxTorque), sizeof(maxTorque));

    ret.append({ static_cast<char>(hasApu),

                 static_cast<char>(hasFlaps),
                 static_cast<char>(hasSpoilers),

                 static_cast<char>(hasElevatorTrim),
                 static_cast<char>(hasRudderTrim),
                 static_cast<char>(hasAileronTrim),

                 static_cast<char>(hasSecondaryTempGauge),
                 static_cast<char>(secondaryTempType),

                 static_cast<char>(numEngines),
                 static_cast<char>(singleTank) });


    ret.append(reinterpret_cast<const char *>(&lowLimit), sizeof(lowLimit));
    ret.append(reinterpret_cast<const char *>(&flapsBegin), sizeof(flapsBegin));
    ret.append(reinterpret_cast<const char *>(&flapsEnd), sizeof(flapsEnd));
    ret.append(reinterpret_cast<const char *>(&greenBegin), sizeof(greenBegin));
    ret.append(reinterpret_cast<const char *>(&greenEnd), sizeof(greenEnd));
    ret.append(reinterpret_cast<const char *>(&yellowBegin), sizeof(yellowBegin));
    ret.append(reinterpret_cast<const char *>(&yellowEnd), sizeof(yellowEnd));
    ret.append(reinterpret_cast<const char *>(&redBegin), sizeof(redBegin));
    ret.append(reinterpret_cast<const char *>(&redEnd), sizeof(redEnd));
    ret.append(reinterpret_cast<const char *>(&highLimit), sizeof(highLimit));
    ret.append(reinterpret_cast<const char *>(&noColors), sizeof(noColors));
    ret.append(reinterpret_cast<const char *>(&dynamicBarberpole), sizeof(dynamicBarberpole));

    uint8_t listSize = refSpeedDefaults.size();
    ret.append(reinterpret_cast<const char *>(&listSize), sizeof(listSize));
    for (const ReferenceSpeed &speedBug : refSpeedDefaults)
    {
        ret.append(reinterpret_cast<const char *>(&speedBug.speed), sizeof(speedBug.speed));
        ret.append({ static_cast<char>(speedBug.designator.toStdString().size()) });
        ret += speedBug.designator.toStdString();
    }

    return QByteArray::fromStdString(ret);
}


}  // namespace definitions
