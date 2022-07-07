#include "SimInterface.hpp"

SimInterface::SimInterface(std::atomic_bool *sharedAtomic,
                           QMutex *sharedMutex,
                           SharedThreadData *sharedData,
                           const AircraftConfig &airplaneStartConfig,
                           QObject *parent)
  : QThread(parent),
    d_sharedDataUpdated(sharedAtomic),
    d_sharedDataMutex(sharedMutex),
    d_sharedData(sharedData),
    d_aircraftConfig(airplaneStartConfig)
{}
