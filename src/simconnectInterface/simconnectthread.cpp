#include "simconnectthread.hpp"

SimconnectThread::SimconnectThread(std::atomic_bool *sharedAtomic,
                                   QMutex *sharedMutex,
                                   SharedDataStruct *sharedStruct,
                                   const ActiveAirplaneSettings &airplaneStartSettings,
                                   QObject *parent) :
  QThread(parent),
  sharedDataUpdated(sharedAtomic), sharedDataMutex(sharedMutex), sharedData(sharedStruct)
{
    d_currentAirplaneSettings = airplaneStartSettings;
}
