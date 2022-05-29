#ifndef __MISC_DATASTRUCT_HPP__
#define __MISC_DATASTRUCT_HPP__

#include <cstdint>
#include <cstring>
#include <QByteArray>

namespace misc
{

struct RawStruct
{
    float totalFuelQty = 0;
    float eng1FuelFlow = 0;
    float eng2FuelFlow = 0;
    float eng3FuelFlow = 0;
    float eng4FuelFlow = 0;
    float groundSpeed = 0;

    char gpsNextWpId[64];
    char nav1Ident[64];
    char nav2Ident[64];
    char gpsPrevWpId[64];

    int32_t hasAp = 1;
    int32_t hasCom1 = 1;
    int32_t hasCom2 = 1;
    int32_t hasNav1 = 1;
    int32_t hasNav2 = 1;
};

struct DataStruct
{
    float totalFuelQty = 0;
    float totalFuelFlow = 0;
    float groundSpeed = 0;
    bool hasAp = true;
    bool hasCom1 = true;
    bool hasCom2 = true;
    bool hasNav1 = true;
    bool hasNav2 = true;

    QByteArray gpsNextWpId;
    QByteArray nav1Ident;
    QByteArray nav2Ident;
    QByteArray gpsPrevWpId;

    DataStruct() = default;

    DataStruct(RawStruct *data)
      : totalFuelQty(data->eng1FuelFlow + data->eng2FuelFlow + data->eng3FuelFlow + data->eng4FuelFlow),

        groundSpeed(data->groundSpeed),
        hasAp(data->hasAp != 0),
        hasCom1(data->hasCom1 != 0),
        hasCom2(data->hasCom2 != 0),
        hasNav1(data->hasNav1 != 0),
        hasNav2(data->hasNav2 != 0),

        gpsNextWpId(data->gpsNextWpId, 64),
        nav1Ident(data->nav1Ident, 64),
        nav2Ident(data->nav2Ident, 64),
        gpsPrevWpId(data->gpsPrevWpId, 64)
    {}
};

}  // namespace misc

#endif  // __MISC_DATASTRUCT_HPP__