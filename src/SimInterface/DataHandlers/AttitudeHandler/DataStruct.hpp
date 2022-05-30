#ifndef __ATTITUDE_DATASTRUCT_HPP__
#define __ATTITUDE_DATASTRUCT_HPP__

#include <cstdint>

namespace attitude
{

struct RawStruct
{
    double angleOfAttack = 0;

    double bank = 0;
    double pitch = 0;
    double slipskid = 0;

    double fdBank = 0;
    double fdPitch = 0;

    uint32_t fdState = 0;
};

struct DataStruct  // also handles aoa
{
    double angleOfAttack = 0;

    double bank = 0;
    double pitch = 0;
    double slipskid = 0;

    bool fdState = false;
    double fdBank = 0;
    double fdPitch = 0;

    DataStruct() = default;

    DataStruct(RawStruct *data)
      : angleOfAttack(data->angleOfAttack),

        bank(data->bank),
        pitch(data->pitch),
        slipskid(data->slipskid),

        fdState(data->fdState != 0),
        fdBank(data->fdBank),
        fdPitch(data->fdPitch)
    {}
};

}  // namespace attitude

#endif  // __ATTITUDE_DATASTRUCT_HPP__