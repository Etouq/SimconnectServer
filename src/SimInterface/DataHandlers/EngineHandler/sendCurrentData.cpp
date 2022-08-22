#include "EngineHandler.hpp"
#include "common/dataIdentifiers.hpp"

namespace handler::engine
{

std::string EngineHandler::sendCurrentData()
{
    std::string dataToSend;

    double gaugeValue = d_gauge1IsPct ? d_previous.firstGauge * d_gauge1Factor : d_previous.firstGauge;
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA),
                        static_cast<char>(MfdIdentifier::ENGINE_FIRST_GAUGE),
                        static_cast<char>(d_engineIdx) });
    dataToSend.append(reinterpret_cast<const char *>(&gaugeValue), sizeof(gaugeValue));

    gaugeValue = d_gauge2IsPct ? d_previous.secondGauge * d_gauge2Factor : d_previous.secondGauge;
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA),
                        static_cast<char>(MfdIdentifier::ENGINE_SECOND_GAUGE),
                        static_cast<char>(d_engineIdx) });
    dataToSend.append(reinterpret_cast<const char *>(&gaugeValue), sizeof(gaugeValue));

    gaugeValue = d_gauge3IsPct ? d_previous.thirdGauge * d_gauge3Factor : d_previous.thirdGauge;
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA),
                        static_cast<char>(MfdIdentifier::ENGINE_THIRD_GAUGE),
                        static_cast<char>(d_engineIdx) });
    dataToSend.append(reinterpret_cast<const char *>(&gaugeValue), sizeof(gaugeValue));

    gaugeValue = d_gauge4IsPct ? d_previous.fourthGauge * d_gauge4Factor : d_previous.fourthGauge;
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA),
                        static_cast<char>(MfdIdentifier::ENGINE_FOURTH_GAUGE),
                        static_cast<char>(d_engineIdx) });
    dataToSend.append(reinterpret_cast<const char *>(&gaugeValue), sizeof(gaugeValue));


    gaugeValue = d_previous.fuelFlow * (d_fuelFlowByWeight ? 3600.0 : 3.785411784);
    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA),
                        static_cast<char>(MfdIdentifier::ENGINE_FUEL_FLOW),
                        static_cast<char>(d_engineIdx) });
    dataToSend.append(reinterpret_cast<const char *>(&gaugeValue), sizeof(gaugeValue));


    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA),
                        static_cast<char>(MfdIdentifier::ENGINE_OIL_TEMP),
                        static_cast<char>(d_engineIdx) });
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.oilTemp), sizeof(d_previous.oilTemp));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA),
                        static_cast<char>(MfdIdentifier::ENGINE_SECONDARY_TEMP),
                        static_cast<char>(d_engineIdx) });
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.secondaryEngineTemp),
                      sizeof(d_previous.secondaryEngineTemp));

    dataToSend.append({ static_cast<char>(DataGroupIdentifier::MFD_DATA),
                        static_cast<char>(MfdIdentifier::ENGINE_OIL_PRESS),
                        static_cast<char>(d_engineIdx) });
    dataToSend.append(reinterpret_cast<const char *>(&d_previous.oilPress), sizeof(d_previous.oilPress));

    return dataToSend;
}

}  // namespace handler::engine
