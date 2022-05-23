#ifndef __AIRSPEEDHANDLER_HPP__
#define __AIRSPEEDHANDLER_HPP__

#include <QObject>

typedef void *HANDLE;

class SimInterface;

class AirspeedHandler : public QObject
{
    Q_OBJECT

    struct DataStruct
    {
        double airspeed = 0;
        double max_speed = 0;

        int32_t true_airspeed = 0;
        int32_t ref_speed = 0;
    };

    DataStruct d_previous;

    const SimInterface *d_parent;

public:

    explicit AirspeedHandler(SimInterface *interface, QObject *parent = nullptr);

    void setupData(HANDLE simConnectHandle);

    void processData(unsigned long *raw);

    void sendBlankData() const;
};

#endif  // __AIRSPEEDHANDLER_HPP__
