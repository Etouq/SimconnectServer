#ifndef BINARYUTIL_H
#define BINARYUTIL_H

#include <QByteArray>
#include <QIODevice>
#include <cstdint>
#include "flightplanreader.h"
#include "simconnectInterface/simconnectthread.h"

class BinaryUtil
{
public:
    BinaryUtil() = default;

    //fundamental types
    static QByteArray toBinary(int8_t val)
    {
        return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
    }
    static QByteArray toBinary(uint8_t val)
    {
        return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
    }
    static QByteArray toBinary(int16_t val)
    {
        return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
    }
    static QByteArray toBinary(uint16_t val)
    {
        return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
    }
    static QByteArray toBinary(int32_t val)
    {
        return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
    }
    static QByteArray toBinary(uint32_t val)
    {
        return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
    }
    static QByteArray toBinary(int64_t val)
    {
        return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
    }
    static QByteArray toBinary(uint64_t val)
    {
        return QByteArray(reinterpret_cast<char *>(&val), sizeof(val));
    }

    static QByteArray toBinary(bool bl)
    {
        return QByteArray(reinterpret_cast<char *>(&bl), sizeof(bl));
    }

    static QByteArray toBinary(float flt)
    {
        return QByteArray(reinterpret_cast<char *>(&flt), sizeof(flt));
    }
    static QByteArray toBinary(double dbl)
    {
        return QByteArray(reinterpret_cast<char *>(&dbl), sizeof(dbl));
    }


    //basic types
    static QByteArray toBinary(const QString &str)
    {
        QByteArray bytes = str.toUtf8();
        uint8_t size = bytes.size();
        bytes.prepend(reinterpret_cast<char *>(&size), sizeof(size));
        return bytes;
    }

    //struct types
    static QByteArray toBinary(const FlightPlanWaypoint &wp)
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

    static QByteArray toBinary(const ActiveAirplaneSettings &settings)
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
    static QByteArray toBinary(const QList<FlightPlanWaypoint> &wpList)
    {
        uint16_t size = wpList.size();
        QByteArray ret = toBinary(size);
        for (int i = 0; i < size; i++)
            ret += toBinary(wpList[i]);
        return ret;
    }


    //read functions
    //fundamental types
    static int8_t readInt8_t(QIODevice &data)
    {
        int8_t val = 0;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }
    static uint8_t readUint8_t(QIODevice &data)
    {
        uint8_t val = 0;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }
    static int16_t readInt16_t(QIODevice &data)
    {
        int16_t val = 0;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }
    static uint16_t readUint16_t(QIODevice &data)
    {
        uint16_t val = 0;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }
    static int32_t readInt32_t(QIODevice &data)
    {
        int32_t val = 0;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }
    static uint32_t readUint32_t(QIODevice &data)
    {
        uint32_t val = 0;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }
    static int64_t readInt64_t(QIODevice &data)
    {
        int64_t val = 0;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }
    static uint64_t readUint64_t(QIODevice &data)
    {
        uint64_t val = 0;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }

    static bool readBool(QIODevice &data)
    {
        bool val = false;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }

    static float readFloat(QIODevice &data)
    {
        float val = 0;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }
    static double readDouble(QIODevice &data)
    {
        double val = 0;
        data.read(reinterpret_cast<char *>(&val), sizeof(val));
        return val;
    }


    //basic types
    static QString readString(QIODevice &data)
    {
        uint8_t size = readUint8_t(data);
        return size == 0 ? "" : QString::fromUtf8(data.read(size));
    }

    //struct types
    static FlightPlanWaypoint readFpWp(QIODevice &data)
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

    static ActiveAirplaneSettings readAirplaneSettings(QIODevice &data)
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
    static QList<FlightPlanWaypoint> readFpList(QIODevice &data)
    {
        uint16_t size = readUint16_t(data);
        QList<FlightPlanWaypoint> ret;
        ret.reserve(size);
        for (int i = 0; i < size; i++)
            ret.append(readFpWp(data));
        return ret;
    }


};

#endif // BINARYUTIL_H
