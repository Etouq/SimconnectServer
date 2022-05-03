#ifndef SHAREDSTRUCTS_H
#define SHAREDSTRUCTS_H

#include <windows.h>
#include "C:/MSFS SDK/SimConnect SDK/include/SimConnect.h"

#include <stdint.h>
#include <vector>

struct dataDef
{
    const char *DatumName;
    const char *UnitsName;
    SIMCONNECT_DATATYPE DatumType;
    float fEpsilon;
};

#endif   // SHAREDSTRUCTS_H
