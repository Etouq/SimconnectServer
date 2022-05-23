#ifndef ALTITUDEHANDLER_HPP
#define ALTITUDEHANDLER_HPP

#include <QObject>

typedef void *HANDLE;

class SimInterface;

class AltitudeHandler : public QObject
{
    Q_OBJECT

    struct RawStruct
    {
        double altitude = 0;
        double radar_altitude = 0;

        double pressure = 29.92;

        double vspeed = 0;

        double nav1_gsi = 0;
        double nav2_gsi = 0;
        double gps_vert_error = 0;

        int32_t ref_altitude = 0;

        int32_t ref_vspeed = 0;

        int32_t gpsDrivesNav1 = 0;
        int32_t autopilot_nav_selected = 0;
        int32_t gps_approach_approach_type = 0;

        int32_t nav1_has_glideslope = 0;
        int32_t nav2_has_glideslope = 0;
        int32_t gps_approach_active = 0;
    };

    struct DataStruct
    {
        double altitude = 0;
        double radar_altitude = 0;
        int32_t ref_altitude = 0;

        double pressure = 29.92;

        double vspeed = 0;
        int32_t ref_vspeed = 0;

        bool gpsDrivesNav1 = false;
        int32_t autopilot_nav_selected = 0;
        int32_t gps_approach_approach_type = 0;

        bool nav1_has_glideslope = false;
        bool nav2_has_glideslope = false;
        bool gps_approach_active = false;

        double nav1_gsi = 0;
        double nav2_gsi = 0;
        double gps_vert_error = 0;

        DataStruct() = default;
        DataStruct(RawStruct *data);
    };

    int32_t d_lastVertMode = -1;   // 0: none, 1: vdi, 2: gs, 3: gp, 4: gspreview

    DataStruct d_previous;

    const SimInterface *d_parent;

public:

    explicit AltitudeHandler(SimInterface *interface, QObject *parent = nullptr);

    void setupData(HANDLE simConnectHandle);

    void processData(unsigned long *raw);

    void reset();
};

#endif  // ALTITUDEHANDLER_HPP
