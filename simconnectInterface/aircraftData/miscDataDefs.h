#ifndef MISCDATADEFS_H
#define MISCDATADEFS_H

#include "sharedStructs.h"

#include <QByteArray>

struct SlowDatadefRawStruct
{
    double fuelWeight = 1;
    float totalFuelQty = 0;
    float eng1FuelFlow = 0;
    float eng2FuelFlow = 0;
    float eng3FuelFlow = 0;
    float eng4FuelFlow = 0;
    float groundSpeed = 0;
    int32_t hasAp = 1;
    int32_t hasCom1 = 0;
    int32_t hasCom2 = 0;
    int32_t hasNav1 = 1;
    int32_t hasNav2 = 1;
};

struct SlowDatadefStruct
{
    double fuelWeight = 1;
    float totalFuelQty = 0;
    float totalFuelFlow = 0;
    float groundSpeed = 0;
    bool hasAp = true;
    bool hasCom1 = true;
    bool hasCom2 = true;
    bool hasNav1 = true;
    bool hasNav2 = true;

    SlowDatadefStruct() = default;

    SlowDatadefStruct(SlowDatadefRawStruct *rhs)
    {
        fuelWeight = rhs->fuelWeight;
        totalFuelQty = rhs->totalFuelQty;
        totalFuelFlow
          = rhs->eng1FuelFlow + rhs->eng2FuelFlow + rhs->eng3FuelFlow + rhs->eng4FuelFlow;
        groundSpeed = rhs->groundSpeed;
        hasAp = rhs->hasAp != 0;
        hasCom1 = rhs->hasCom1 == 0;
        hasCom2 = rhs->hasCom2 == 0;
        hasNav1 = rhs->hasNav1 != 0;
        hasNav2 = rhs->hasNav2 != 0;
    }
};


extern const std::vector<dataDef> slowDatadefVector;

struct StringsRawDataStruct
{
    char gps_wp_next_id[256];
    char nav1_ident[256];
    char nav2_ident[256];
    char gps_wp_prev_id[256];
};

struct StringsDataStruct
{
    QByteArray gps_wp_next_id = "";
    QByteArray nav1_ident = "";
    QByteArray nav2_ident = "";
    QByteArray gps_wp_prev_id = "";

    StringsDataStruct() = default;

    StringsDataStruct(StringsRawDataStruct *rhs)
    {
        gps_wp_next_id = QByteArray(rhs->gps_wp_next_id);
        nav1_ident = QByteArray(rhs->nav1_ident);
        nav2_ident = QByteArray(rhs->nav2_ident);
        gps_wp_prev_id = QByteArray(rhs->gps_wp_prev_id);
    }
};

extern const std::vector<dataDef>
  stringsDatadefVector;   // maybe add: ATC AIRLINE String (50), ATC ID String (10), ATC FLIGHT
                          // NUMBER String (6)


struct SetXpndrStateStruct
{
    int32_t state = 0;
};

#endif   // MISCDATADEFS_H
