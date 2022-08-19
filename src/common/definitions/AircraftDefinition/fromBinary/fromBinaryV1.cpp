#include "../AircraftDefinition.hpp"
#include <QIODevice>

namespace definitions
{

AircraftDefinition AircraftDefinition::fromBinaryV1(QIODevice &data, FileVersion version)
{
    AircraftDefinition ret;
    data.read(reinterpret_cast<char *>(&ret.type), sizeof(ret.type));

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

            data.read(reinterpret_cast<char *>(&ret.hasApu), sizeof(ret.hasApu));

            bool egtInsteadOfItt = false;
            data.read(reinterpret_cast<char *>(&egtInsteadOfItt), sizeof(egtInsteadOfItt));

            ret.engineTempType = egtInsteadOfItt ? TemperatureGaugeType::EGT : TemperatureGaugeType::ITT;

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

            data.read(reinterpret_cast<char *>(&ret.hasSecondaryTempGauge), sizeof(ret.hasSecondaryTempGauge));

            bool boolData = false;
            data.read(reinterpret_cast<char *>(&boolData), sizeof(boolData));

            ret.gauge1Type = boolData ? SwitchingGaugeType::PROP_RPM : SwitchingGaugeType::RPM;

            data.read(reinterpret_cast<char *>(&boolData), sizeof(boolData));

            ret.gauge2Type = boolData ? SwitchingGaugeType::POWER_PCT : SwitchingGaugeType::MANIFOLD_PRESSURE;
            data.read(reinterpret_cast<char *>(&ret.maxPower), sizeof(ret.maxPower));

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
            data.read(reinterpret_cast<char *>(&ret.hasSecondaryTempGauge), sizeof(ret.hasSecondaryTempGauge));

            bool boolData = false;
            data.read(reinterpret_cast<char *>(&boolData), sizeof(boolData));
            ret.gauge4Type = boolData ? SwitchingGaugeType::PROP_RPM : SwitchingGaugeType::RPM;

            data.read(reinterpret_cast<char *>(&boolData), sizeof(boolData));
            ret.gauge2Type = boolData ? SwitchingGaugeType::TORQUE_PCT : SwitchingGaugeType::TORQUE;

            ret.hasApu = false;

            break;
        }
        default:
            return ret;
    }

    uint8_t stringSize = 0;
    data.read(reinterpret_cast<char *>(&stringSize), sizeof(stringSize));

    ret.name = QString::fromUtf8(data.read(stringSize));

    ret.fuelQtyGauge = GaugeDefinition::fromBinary(data, version);
    ret.fuelFlowGauge = GaugeDefinition::fromBinary(data, version);
    ret.oilTempGauge = GaugeDefinition::fromBinary(data, version);
    ret.oilPressGauge = GaugeDefinition::fromBinary(data, version);

    data.read(reinterpret_cast<char *>(&ret.hasFlaps), sizeof(ret.hasFlaps));
    data.read(reinterpret_cast<char *>(&ret.hasSpoilers), sizeof(ret.hasSpoilers));

    data.read(reinterpret_cast<char *>(&ret.hasElevatorTrim), sizeof(ret.hasElevatorTrim));
    data.read(reinterpret_cast<char *>(&ret.hasRudderTrim), sizeof(ret.hasRudderTrim));
    data.read(reinterpret_cast<char *>(&ret.hasAileronTrim), sizeof(ret.hasAileronTrim));

    data.skip(2 * sizeof(bool));

    data.read(reinterpret_cast<char *>(&ret.numEngines), sizeof(ret.numEngines));
    data.read(reinterpret_cast<char *>(&stringSize), sizeof(stringSize));
    ret.singleTank = stringSize == 1;

    data.read(reinterpret_cast<char *>(&ret.lowLimit), sizeof(ret.lowLimit));
    data.read(reinterpret_cast<char *>(&ret.flapsBegin), sizeof(ret.flapsBegin));
    data.read(reinterpret_cast<char *>(&ret.flapsEnd), sizeof(ret.flapsEnd));
    data.read(reinterpret_cast<char *>(&ret.greenBegin), sizeof(ret.greenBegin));
    data.read(reinterpret_cast<char *>(&ret.greenEnd), sizeof(ret.greenEnd));
    data.read(reinterpret_cast<char *>(&ret.yellowBegin), sizeof(ret.yellowBegin));
    data.read(reinterpret_cast<char *>(&ret.yellowEnd), sizeof(ret.yellowEnd));
    data.read(reinterpret_cast<char *>(&ret.redBegin), sizeof(ret.redBegin));
    data.read(reinterpret_cast<char *>(&ret.redEnd), sizeof(ret.redEnd));
    data.read(reinterpret_cast<char *>(&ret.highLimit), sizeof(ret.highLimit));

    data.read(reinterpret_cast<char *>(&ret.noColors), sizeof(ret.noColors));
    data.read(reinterpret_cast<char *>(&ret.dynamicBarberpole), sizeof(ret.dynamicBarberpole));

    return ret;
}

}  // namespace definitions
