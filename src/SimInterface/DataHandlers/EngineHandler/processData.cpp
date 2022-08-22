#include "EngineHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace handler::engine
{

std::string EngineHandler::processData(const unsigned long *raw)
{
    DataStruct newData(*reinterpret_cast<const DataStruct *>(raw));
    std::string dataToSend;

    switch (d_numGauges)
    {
        case 4:
        {
            if (std::abs(d_previous.fourthGauge - newData.fourthGauge) >= d_fourthGaugeEpsilon)
            {
                d_previous.fourthGauge = newData.fourthGauge;
                if (d_gauge4IsPct)
                    newData.fourthGauge *= d_gauge4Factor;

                dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA),
                                    static_cast<char>(MfdIdentifier::ENGINE_FOURTH_GAUGE),
                                    static_cast<char>(d_engineIdx) });
                dataToSend.append(reinterpret_cast<const char *>(&newData.fourthGauge), sizeof(newData.fourthGauge));
            }

            [[fallthrough]];
        }
        case 3:
        {
            if (std::abs(d_previous.thirdGauge - newData.thirdGauge) >= d_thirdGaugeEpsilon)
            {
                d_previous.thirdGauge = newData.thirdGauge;
                if (d_gauge3IsPct)
                    newData.thirdGauge *= d_gauge3Factor;

                dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA),
                                    static_cast<char>(MfdIdentifier::ENGINE_THIRD_GAUGE),
                                    static_cast<char>(d_engineIdx) });
                dataToSend.append(reinterpret_cast<const char *>(&newData.thirdGauge), sizeof(newData.thirdGauge));
            }

            [[fallthrough]];
        }
        case 2:
        {
            if (std::abs(d_previous.firstGauge - newData.firstGauge) >= d_firstGaugeEpsilon)
            {
                d_previous.firstGauge = newData.firstGauge;
                if (d_gauge1IsPct)
                    newData.firstGauge *= d_gauge1Factor;

                dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA),
                                    static_cast<char>(MfdIdentifier::ENGINE_FIRST_GAUGE),
                                    static_cast<char>(d_engineIdx) });
                dataToSend.append(reinterpret_cast<const char *>(&newData.firstGauge), sizeof(newData.firstGauge));
            }

            if (std::abs(d_previous.secondGauge - newData.secondGauge) >= d_secondGaugeEpsilon)
            {
                d_previous.secondGauge = newData.secondGauge;
                if (d_gauge2IsPct)
                    newData.secondGauge *= d_gauge2Factor;

                dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA),
                                    static_cast<char>(MfdIdentifier::ENGINE_SECOND_GAUGE),
                                    static_cast<char>(d_engineIdx) });
                dataToSend.append(reinterpret_cast<const char *>(&newData.secondGauge), sizeof(newData.secondGauge));
            }
        }
    }


    if (std::abs(d_previous.fuelFlow - newData.fuelFlow) >= d_fuelFlowEpsilon)
    {
        d_previous.fuelFlow = newData.fuelFlow;
        newData.fuelFlow *= d_fuelFlowByWeight ? 3600.0 : 3.785411784;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA),
                            static_cast<char>(MfdIdentifier::ENGINE_FUEL_FLOW),
                            static_cast<char>(d_engineIdx) });
        dataToSend.append(reinterpret_cast<const char *>(&newData.fuelFlow), sizeof(newData.fuelFlow));
    }

    if (std::abs(d_previous.oilTemp - newData.oilTemp) >= d_oilTempEpsilon)
    {
        d_previous.oilTemp = newData.oilTemp;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA),
                            static_cast<char>(MfdIdentifier::ENGINE_OIL_TEMP),
                            static_cast<char>(d_engineIdx) });
        dataToSend.append(reinterpret_cast<const char *>(&newData.oilTemp), sizeof(newData.oilTemp));
    }

    if (d_hasSecondaryTempGauge
        && std::abs(d_previous.secondaryEngineTemp - newData.secondaryEngineTemp) >= d_secondaryTempEpsilon)
    {
        d_previous.secondaryEngineTemp = newData.secondaryEngineTemp;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA),
                            static_cast<char>(MfdIdentifier::ENGINE_SECONDARY_TEMP),
                            static_cast<char>(d_engineIdx) });
        dataToSend.append(reinterpret_cast<const char *>(&newData.secondaryEngineTemp),
                          sizeof(newData.secondaryEngineTemp));
    }

    if (std::abs(d_previous.oilPress - newData.oilPress) >= d_oilPressEpsilon)
    {
        d_previous.oilPress = newData.oilPress;
        dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA),
                            static_cast<char>(MfdIdentifier::ENGINE_OIL_PRESS),
                            static_cast<char>(d_engineIdx) });
        dataToSend.append(reinterpret_cast<const char *>(&newData.oilPress), sizeof(newData.oilPress));
    }

    return dataToSend;
}

}  // namespace handler::engine
