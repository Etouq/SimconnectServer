#ifndef __APINFOHANDLER_HPP__
#define __APINFOHANDLER_HPP__

#include "DataStruct.hpp"

#include <QObject>

typedef void *HANDLE;

class SimInterface;

namespace apinfo
{

class ApInfoHandler : public QObject
{
    Q_OBJECT

    bool d_apMaster = false;
    bool d_yawDamper = false;

    QByteArray d_verticalActive = "";
    QByteArray d_modeReference = "";
    QByteArray d_armed = "";
    QByteArray d_armedReference = "";
    QByteArray d_lateralActive = "";
    QByteArray d_lateralArmed = "";

    DataStruct d_previous;

    const SimInterface *d_parent;

public:

    explicit ApInfoHandler(SimInterface *interface, QObject *parent = nullptr);

    void setupData(HANDLE simConnectHandle);

    void processData(unsigned long *raw);

    void reset();

    void sendCurrentData();
};

}  // namespace apinfo

#endif  // __APINFOHANDLER_HPP__
