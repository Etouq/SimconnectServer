#ifndef __HSI_DATASTRUCT_HPP__
#define __HSI_DATASTRUCT_HPP__

#include <cstdint>
#include "common/simEnums.hpp"

namespace hsi
{

struct RawStruct
{
    double rotation = 0;
    double heading = 0;
    double turnRate = 0;
    double currentTrack = 0;
    double gpsWpDesiredTrack = 0;

    double currLat = 0;
    double currLon = 0;

    double gpsWpCrossTrack = 0;
    double trueHeading = 0;

    double nav1Loc = 0;
    double nav1Cdi = 0;
    double nav1Obs = 0;
    double nav1TacanObs = 0;
    double nav1TacanCdi = 0;

    double nav2Loc = 0;
    double nav2Cdi = 0;
    double nav2Obs = 0;
    double nav2TacanObs = 0;
    double nav2TacanCdi = 0;

    uint32_t autopilotNavSelected = 0;
    simenums::ApproachType gpsApproachApproachType = simenums::ApproachType::NONE;
    uint32_t gpsDrivesNav1 = 0;
    uint32_t autopilotApproachHold = 0;

    uint32_t tacanDrivesNav1 = 0;
    uint32_t nav1HasTacan = 0;
    uint32_t nav2HasTacan = 0;

    uint32_t nav1HasNav = 0;
    uint32_t nav1HasLoc = 0;
    uint32_t nav1ToFrom = 0;
    uint32_t nav1TacanToFrom = 0;

    uint32_t nav2HasNav = 0;
    uint32_t nav2HasLoc = 0;
    uint32_t nav2ToFrom = 0;
    uint32_t nav2TacanToFrom = 0;
};

struct DataStruct  // also handles position
{
    double rotation = 0;
    double heading = 0;
    double turnRate = 0;
    double currentTrack = 0;
    double gpsWpDesiredTrack = 0;

    double currLat = 0;
    double currLon = 0;

    double gpsWpCrossTrack = 0;
    double trueHeading = 0;

    uint32_t autopilotNavSelected = 0;
    simenums::ApproachType gpsApproachApproachType = simenums::ApproachType::NONE;
    bool gpsDrivesNav1 = false;
    bool autopilotApproachHold = false;

    // tacan
    bool tacanDrivesNav1 = false;

    bool nav1HasTacan = false;
    double nav1TacanObs = 0;
    double nav1TacanCdi = 0;

    bool nav2HasTacan = false;
    double nav2TacanObs = 0;
    double nav2TacanCdi = 0;

    bool nav1HasNav = false;
    bool nav1HasLoc = false;
    uint32_t nav1ToFrom = 0;
    uint32_t nav1TacanToFrom = 0;
    double nav1Loc = 0;
    double nav1Obs = 0;
    double nav1Cdi = 0;

    bool nav2HasNav = false;
    bool nav2HasLoc = false;
    uint32_t nav2ToFrom = 0;
    uint32_t nav2TacanToFrom = 0;
    double nav2Loc = 0;
    double nav2Cdi = 0;
    double nav2Obs = 0;

    DataStruct() = default;

    DataStruct(RawStruct *data)
      : rotation(data->rotation),
        heading(data->heading),
        turnRate(data->turnRate),
        currentTrack(data->currentTrack),
        gpsWpDesiredTrack(data->gpsWpDesiredTrack),

        currLat(data->currLat),
        currLon(data->currLon),

        gpsWpCrossTrack(data->gpsWpCrossTrack),
        trueHeading(data->trueHeading),

        autopilotNavSelected(data->autopilotNavSelected),
        gpsApproachApproachType(data->gpsApproachApproachType),
        gpsDrivesNav1(data->gpsDrivesNav1 != 0),
        autopilotApproachHold(data->autopilotApproachHold != 0),

        tacanDrivesNav1(data->tacanDrivesNav1),

        nav1HasTacan(data->nav1HasTacan),
        nav1TacanObs(data->nav1TacanObs),
        nav1TacanCdi(data->nav1TacanCdi),

        nav2HasTacan(data->nav2HasTacan),
        nav2TacanObs(data->nav2TacanObs),
        nav2TacanCdi(data->nav2TacanCdi),

        nav1HasNav(data->nav1HasNav != 0),
        nav1HasLoc(data->nav1HasLoc != 0),
        nav1ToFrom(data->nav1ToFrom),
        nav1TacanToFrom(data->nav1TacanToFrom),
        nav1Loc(data->nav1Loc),
        nav1Cdi(data->nav1Cdi),
        nav1Obs(data->nav1Obs),

        nav2HasNav(data->nav2HasNav != 0),
        nav2HasLoc(data->nav2HasLoc != 0),
        nav2ToFrom(data->nav2ToFrom),
        nav2TacanToFrom(data->nav2TacanToFrom),
        nav2Loc(data->nav2Loc),
        nav2Cdi(data->nav2Cdi),
        nav2Obs(data->nav2Obs)
    {}
};

}  // namespace hsi

#endif  // __HSI_DATASTRUCT_HPP__