#ifndef __APINFOHANDLER_HPP__
#define __APINFOHANDLER_HPP__


#include <string>

typedef void *HANDLE;

namespace apinfo
{

class ApInfoHandler
{
    bool d_apMaster = false;
    bool d_yawDamper = false;
    bool d_flc = false;

    std::string d_verticalActive = "";
    std::string d_modeReference = "";
    std::string d_armed = "";
    std::string d_armedReference = "";
    std::string d_lateralActive = "";
    std::string d_lateralArmed = "";

public:

    ApInfoHandler() = default;

    void setupData(HANDLE simConnectHandle);

    [[nodiscard]] std::string processData(unsigned long *raw);

    std::string reset()
    {
        d_apMaster = false;
        d_yawDamper = false;
        d_flc = false;

        d_verticalActive = "";
        d_modeReference = "";
        d_armed = "";
        d_armedReference = "";
        d_lateralActive = "";
        d_lateralArmed = "";

        return sendCurrentData();
    }

    [[nodiscard]] std::string sendCurrentData();
};

}  // namespace apinfo

#endif  // __APINFOHANDLER_HPP__
