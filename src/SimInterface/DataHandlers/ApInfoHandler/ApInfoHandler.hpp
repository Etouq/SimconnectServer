#ifndef __APINFOHANDLER_HPP__
#define __APINFOHANDLER_HPP__

#include "DataStruct.hpp"

#include <QByteArray>

typedef void *HANDLE;

namespace apinfo
{

class ApInfoHandler
{
    bool d_apMaster = false;
    bool d_yawDamper = false;

    QByteArray d_verticalActive = "";
    QByteArray d_modeReference = "";
    QByteArray d_armed = "";
    QByteArray d_armedReference = "";
    QByteArray d_lateralActive = "";
    QByteArray d_lateralArmed = "";

    DataStruct d_previous;

public:

    ApInfoHandler() = default;

    void setupData(HANDLE simConnectHandle);

    [[nodiscard]] QByteArray processData(unsigned long *raw);

    QByteArray reset()
    {
        d_apMaster = false;
        d_yawDamper = false;

        d_verticalActive = "";
        d_modeReference = "";
        d_armed = "";
        d_armedReference = "";
        d_lateralActive = "";
        d_lateralArmed = "";

        return sendCurrentData();
    }

    [[nodiscard]] QByteArray sendCurrentData();
};

}  // namespace apinfo

#endif  // __APINFOHANDLER_HPP__
