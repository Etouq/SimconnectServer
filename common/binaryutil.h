#ifndef BINARYUTIL_H
#define BINARYUTIL_H

#include <QByteArray>
#include <QIODevice>
#include <cstdint>
#include "FlightplanReader/flightplanreader.h"
#include "simconnectInterface/simconnectthread.h"

namespace BinaryUtil
{
//to binary converters
//fundamental types
QByteArray toBinary(int8_t val);
QByteArray toBinary(uint8_t val);
QByteArray toBinary(int16_t val);
QByteArray toBinary(uint16_t val);
QByteArray toBinary(int32_t val);
QByteArray toBinary(uint32_t val);
QByteArray toBinary(int64_t val);
QByteArray toBinary(uint64_t val);

QByteArray toBinary(bool bl);

QByteArray toBinary(float flt);
QByteArray toBinary(double dbl);


//basic types
QByteArray toBinary(const QString &str);


//struct types
QByteArray toBinary(const FlightPlanWaypoint &wp);

QByteArray toBinary(const ActiveAirplaneSettings &settings);


//list types
QByteArray toBinary(const QList<FlightPlanWaypoint> &wpList);



//from binary converters
//fundamental types
int8_t readInt8_t(QIODevice &data);
uint8_t readUint8_t(QIODevice &data);
int16_t readInt16_t(QIODevice &data);
uint16_t readUint16_t(QIODevice &data);
int32_t readInt32_t(QIODevice &data);
uint32_t readUint32_t(QIODevice &data);
int64_t readInt64_t(QIODevice &data);
uint64_t readUint64_t(QIODevice &data);

bool readBool(QIODevice &data);

float readFloat(QIODevice &data);
double readDouble(QIODevice &data);


//basic types
QString readString(QIODevice &data);


//struct types
FlightPlanWaypoint readFpWp(QIODevice &data);

ActiveAirplaneSettings readAirplaneSettings(QIODevice &data);


//list types
QList<FlightPlanWaypoint> readFpList(QIODevice &data);

}

#endif // BINARYUTIL_H
