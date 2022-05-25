#ifndef __HSIHANDLER_HPP__
#define __HSIHANDLER_HPP__

#include "common/dataIdentifiers.hpp"
#include "DataStruct.hpp"

#include <QObject>
#include <string>


typedef void *HANDLE;

class SimInterface;

namespace hsi
{

class HsiHandler : public QObject
{
    Q_OBJECT

    bool d_displayDeviation = false;
    HsiNavSource d_navSource = HsiNavSource::NONE;
    double d_course = -5000.0;
    double d_courseDeviation = -5000.0;
    bool d_nextGpsWpIdValid = false;

    DataStruct d_previous;

    const SimInterface *d_parent;

public:

    explicit HsiHandler(SimInterface *interface, QObject *parent = nullptr);

    void gpsWpNextIdValid(bool valid)
    {
        d_nextGpsWpIdValid = valid;
    }

    void setupData(HANDLE simConnectHandle);

    void processData(unsigned long *raw);

    void reset();

    void sendCurrentData();

private:

    void handleNav1Tacan(QByteArray &dataToSend, const DataStruct &newData);
    void handleNav2Tacan(QByteArray &dataToSend, const DataStruct &newData);

    void handleNav1(QByteArray &dataToSend, const DataStruct &newData);
    void handleNav2(QByteArray &dataToSend, const DataStruct &newData);

    void handleGps(QByteArray &dataToSend, const DataStruct &newData);
};

}  // namespace hsi

#endif  // __HSIHANDLER_HPP__
