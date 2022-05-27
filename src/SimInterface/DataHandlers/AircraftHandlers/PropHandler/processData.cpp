#include "PropHandler.hpp"
#include "common/dataIdentifiers.hpp"

#include <cmath>

#include "SimInterface/DataHandlers/AircraftHandlers/PropHandler/DataStruct.hpp"

namespace aircraft::prop
{

QByteArray PropHandler::processData(const unsigned long *raw)
{
    QByteArray dataToSend = processDataBase(raw + d_numEngines * sizeof(EngineStruct));
    if (d_numEngines == 1) [[likely]]
    {
        processEngine(raw, 1, d_engine1, dataToSend);
    }
    else if (d_numEngines == 2)
    {
        processEngine(raw, 1, d_engine1, dataToSend);
        processEngine(raw, 2, d_engine2, dataToSend);
    }
    else [[unlikely]]
    {
        processEngine(raw, 1, d_engine1, dataToSend);
        processEngine(raw, 2, d_engine2, dataToSend);
        processEngine(raw, 3, d_engine3, dataToSend);
        processEngine(raw, 4, d_engine4, dataToSend);
    }

    return dataToSend;
}

}  // namespace aircraft::prop
