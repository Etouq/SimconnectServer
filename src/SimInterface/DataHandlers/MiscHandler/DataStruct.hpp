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

    uint32_t hasAp = 1;
    uint32_t com1Avail = 1;
    uint32_t com2Avail = 1;
    uint32_t com3Avail = 1;
    uint32_t nav1Avail = 1;
    uint32_t nav2Avail = 1;
    uint32_t xpdrAvail = 1;
};

struct DataStruct
{
    float totalFuelQty = 0;
    float totalFuelFlow = 0;
    float groundSpeed = 0;
    bool hasAp = true;
    bool com1Avail = true;
    bool com2Avail = true;
    bool com3Avail = true;
    bool nav1Avail = true;
    bool nav2Avail = true;
    bool xpdrAvail = true;

    QByteArray gpsNextWpId;
    QByteArray nav1Ident;
    QByteArray nav2Ident;
    QByteArray gpsPrevWpId;

    DataStruct() = default;

    DataStruct(RawStruct *data)
      : totalFuelQty(data->eng1FuelFlow + data->eng2FuelFlow + data->eng3FuelFlow + data->eng4FuelFlow),

        groundSpeed(data->groundSpeed),
        hasAp(data->hasAp != 0),
        com1Avail(data->com1Avail != 0),
        com2Avail(data->com2Avail != 0),
        com3Avail(data->com3Avail != 0),
        nav1Avail(data->nav1Avail != 0),
        nav2Avail(data->nav2Avail != 0),
        xpdrAvail(data->xpdrAvail != 0),

        gpsNextWpId(data->gpsNextWpId, 64),
        nav1Ident(data->nav1Ident, 64),
        nav2Ident(data->nav2Ident, 64),
        gpsPrevWpId(data->gpsPrevWpId, 64)
    {}
};

}  // namespace misc

#endif  // __MISC_DATASTRUCT_HPP__