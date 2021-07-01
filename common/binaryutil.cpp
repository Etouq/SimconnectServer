#include "binaryutil.h"

//to binary converters
//fundamental types
QByteArray BinaryUtil::toBinary(int8_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}
QByteArray BinaryUtil::toBinary(uint8_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}
QByteArray BinaryUtil::toBinary(int16_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}
QByteArray BinaryUtil::toBinary(uint16_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}
QByteArray BinaryUtil::toBinary(int32_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}
QByteArray BinaryUtil::toBinary(uint32_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}
QByteArray BinaryUtil::toBinary(int64_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}
QByteArray BinaryUtil::toBinary(uint64_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}

QByteArray BinaryUtil::toBinary(bool bl)
{
    return QByteArray(reinterpret_cast<char *>(&bl), sizeof(bl));
}

QByteArray BinaryUtil::toBinary(float flt)
{
    return QByteArray(reinterpret_cast<char *>(&flt), sizeof(flt));
}
QByteArray BinaryUtil::toBinary(double dbl)
{
    return QByteArray(reinterpret_cast<char *>(&dbl), sizeof(dbl));
}


//basic types
QByteArray BinaryUtil::toBinary(const QString &str)
{
    QByteArray bytes = str.toUtf8();
    uint8_t size = bytes.size();
    bytes.prepend(reinterpret_cast<char *>(&size), sizeof(size));
    return bytes;
}


//struct types
QByteArray BinaryUtil::toBinary(const FlightPlanWaypoint &wp)
{
    QByteArray ret = toBinary(wp.position.latitude());
    ret += toBinary(wp.position.longitude());
    ret += toBinary(wp.alt1);
    ret += toBinary(wp.alt2);
    ret += toBinary(wp.ident);
    ret += toBinary(wp.wpType);
    ret += toBinary(wp.altType);
    return ret;
}

QByteArray BinaryUtil::toBinary(const ActiveAirplaneSettings &settings)
{
    QByteArray ret = toBinary(settings.secondDivFactor);
    ret += toBinary(settings.egtReplacesItt);
    ret += toBinary(settings.torqueAsPct);
    ret += toBinary(settings.usePropRpm);
    ret += toBinary(settings.secondIsLoad);
    ret += toBinary(settings.hasApu);
    ret += toBinary(settings.hasFlaps);
    ret += toBinary(settings.hasSpoilers);
    ret += toBinary(settings.hasElevTrim);
    ret += toBinary(settings.hasRudderTrim);
    ret += toBinary(settings.hasAileronTrim);
    ret += toBinary(settings.hasEgt);
    ret += toBinary(settings.fuelQtyByVolume);
    ret += toBinary(settings.fuelFlowByVolume);
    ret += toBinary(settings.numEngines);
    ret += toBinary(settings.numTanks);
    ret += toBinary(settings.type);
    ret += toBinary(settings.n1Epsilon);
    ret += toBinary(settings.n2Epsilon);
    ret += toBinary(settings.ittEpsilon);
    ret += toBinary(settings.rpmEpsilon);
    ret += toBinary(settings.secondEpsilon);
    ret += toBinary(settings.trqEpsilon);
    ret += toBinary(settings.fuelQtyEpsilon);
    ret += toBinary(settings.fuelFlowEpsilon);
    ret += toBinary(settings.oilTempEpsilon);
    ret += toBinary(settings.oilPressEpsilon);
    ret += toBinary(settings.egtEpsilon);
    return ret;
}


//list types
QByteArray BinaryUtil::toBinary(const QList<FlightPlanWaypoint> &wpList)
{
    uint16_t size = wpList.size();
    QByteArray ret = toBinary(size);
    for (int i = 0; i < size; i++)
        ret += toBinary(wpList[i]);
    return ret;
}



//from binary converters

int8_t BinaryUtil::readInt8_t(QIODevice &data)
{
    int8_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
uint8_t BinaryUtil::readUint8_t(QIODevice &data)
{
    uint8_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
int16_t BinaryUtil::readInt16_t(QIODevice &data)
{
    int16_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
uint16_t BinaryUtil::readUint16_t(QIODevice &data)
{
    uint16_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
int32_t BinaryUtil::readInt32_t(QIODevice &data)
{
    int32_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
uint32_t BinaryUtil::readUint32_t(QIODevice &data)
{
    uint32_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
int64_t BinaryUtil::readInt64_t(QIODevice &data)
{
    int64_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
uint64_t BinaryUtil::readUint64_t(QIODevice &data)
{
    uint64_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}

bool BinaryUtil::readBool(QIODevice &data)
{
    bool val = false;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}

float BinaryUtil::readFloat(QIODevice &data)
{
    float val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}
double BinaryUtil::readDouble(QIODevice &data)
{
    double val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}


//basic types
QString BinaryUtil::readString(QIODevice &data)
{
    uint8_t size = readUint8_t(data);
    return size == 0 ? "" : QString::fromUtf8(data.read(size));
}


//struct types
FlightPlanWaypoint BinaryUtil::readFpWp(QIODevice &data)
{
    FlightPlanWaypoint ret;
    ret.position = QGeoCoordinate(readDouble(data), readDouble(data));
    ret.alt1 = readInt32_t(data);
    ret.alt2 = readInt32_t(data);
    ret.ident = readString(data);
    ret.wpType = readInt8_t(data);
    ret.altType = readInt8_t(data);
    return ret;
}

ActiveAirplaneSettings BinaryUtil::readAirplaneSettings(QIODevice &data)
{
    ActiveAirplaneSettings ret;
    ret.secondDivFactor = readDouble(data);
    ret.egtReplacesItt = readBool(data);
    ret.torqueAsPct = readBool(data);
    ret.usePropRpm = readBool(data);
    ret.secondIsLoad = readBool(data);
    ret.hasApu = readBool(data);
    ret.hasFlaps = readBool(data);
    ret.hasSpoilers = readBool(data);
    ret.hasElevTrim = readBool(data);
    ret.hasRudderTrim = readBool(data);
    ret.hasAileronTrim = readBool(data);
    ret.hasEgt = readBool(data);
    ret.fuelQtyByVolume = readBool(data);
    ret.fuelFlowByVolume = readBool(data);
    ret.numEngines = readInt8_t(data);
    ret.numTanks = readInt8_t(data);
    ret.type = readInt8_t(data);
    ret.n1Epsilon = readDouble(data);
    ret.n2Epsilon = readDouble(data);
    ret.ittEpsilon = readDouble(data);
    ret.rpmEpsilon = readDouble(data);
    ret.secondEpsilon = readDouble(data);
    ret.trqEpsilon = readDouble(data);
    ret.fuelQtyEpsilon = readDouble(data);
    ret.fuelFlowEpsilon = readDouble(data);
    ret.oilTempEpsilon = readDouble(data);
    ret.oilPressEpsilon = readDouble(data);
    ret.egtEpsilon = readDouble(data);
    return ret;
}


//list types
QList<FlightPlanWaypoint> BinaryUtil::readFpList(QIODevice &data)
{
    uint16_t size = readUint16_t(data);
    QList<FlightPlanWaypoint> ret;
    ret.reserve(size);
    for (int i = 0; i < size; i++)
        ret.append(readFpWp(data));
    return ret;
}
