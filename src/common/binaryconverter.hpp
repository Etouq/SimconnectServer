#ifndef BINARYCONVERTER_HPP
#define BINARYCONVERTER_HPP

#include "FlightplanReader/flightplanreader.hpp"
#include "simconnectInterface/simconnectthread.hpp"

#include <cstdint>
#include <QByteArray>
#include <QIODevice>
#include <QList>

namespace BinaryConverter
{
// to binary converters
// fundamental types
inline QByteArray toBinary(int8_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}

inline QByteArray toBinary(uint8_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}

inline QByteArray toBinary(int16_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}

inline QByteArray toBinary(uint16_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}

inline QByteArray toBinary(int32_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}

inline QByteArray toBinary(uint32_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}

inline QByteArray toBinary(int64_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}

inline QByteArray toBinary(uint64_t val)
{
    return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
}

inline QByteArray toBinary(bool bl)
{
    return QByteArray(reinterpret_cast<char *>(&bl), sizeof(bl));
}

inline QByteArray toBinary(float flt)
{
    return QByteArray(reinterpret_cast<char *>(&flt), sizeof(flt));
}

inline QByteArray toBinary(double dbl)
{
    return QByteArray(reinterpret_cast<char *>(&dbl), sizeof(dbl));
}

// basic types
inline QByteArray toBinary(const QString &str)
{
    QByteArray bytes = str.toUtf8();
    uint8_t size = bytes.size();
    bytes.prepend(reinterpret_cast<char *>(&size), sizeof(size));
    return bytes;
}

// struct types
inline QByteArray toBinary(const FlightPlanWaypoint &wp)
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

inline QByteArray toBinary(const ActiveAirplaneSettings &settings)
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

// list types
inline QByteArray toBinary(const QList<FlightPlanWaypoint> &wpList)
{
    uint16_t size = wpList.size();
    QByteArray ret = toBinary(size);
    for (int i = 0; i < size; i++)
        ret += toBinary(wpList[i]);
    return ret;
}

// from binary converters
// fundamental types
inline int8_t readInt8_t(QIODevice &data)
{
    int8_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}

inline uint8_t readUint8_t(QIODevice &data)
{
    uint8_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}

inline int16_t readInt16_t(QIODevice &data)
{
    int16_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}

inline uint16_t readUint16_t(QIODevice &data)
{
    uint16_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}

inline int32_t readInt32_t(QIODevice &data)
{
    int32_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}

inline uint32_t readUint32_t(QIODevice &data)
{
    uint32_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}

inline int64_t readInt64_t(QIODevice &data)
{
    int64_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}

inline uint64_t readUint64_t(QIODevice &data)
{
    uint64_t val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}

inline bool readBool(QIODevice &data)
{
    bool val = false;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}

inline float readFloat(QIODevice &data)
{
    float val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}

inline double readDouble(QIODevice &data)
{
    double val = 0;
    data.read(reinterpret_cast<char *>(&val), sizeof(val));
    return val;
}

// basic types
inline QString readString(QIODevice &data)
{
    uint8_t size = readUint8_t(data);
    return size == 0 ? "" : QString::fromUtf8(data.read(size));
}

// struct types
inline FlightPlanWaypoint readFpWp(QIODevice &data)
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

inline ActiveAirplaneSettings readAirplaneSettings(QIODevice &data)
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

// list types
inline QList<FlightPlanWaypoint> readFpList(QIODevice &data)
{
    uint16_t size = readUint16_t(data);
    QList<FlightPlanWaypoint> ret;
    ret.reserve(size);
    for (int i = 0; i < size; i++)
        ret.append(readFpWp(data));
    return ret;
}

}  // namespace BinaryConverter

#endif  // BINARYCONVERTER_HPP
