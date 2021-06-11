#include "mainwindow.h"
#include "binaryutil.h"

ActiveAirplaneSettings MainWindow::readAircraftSettings()
{
    ActiveAirplaneSettings ret;
    ret.secondDivFactor = BinaryUtil::readDouble(*tcpSocket);
    ret.egtReplacesItt = BinaryUtil::readBool(*tcpSocket);
    ret.torqueAsPct = BinaryUtil::readBool(*tcpSocket);
    ret.usePropRpm = BinaryUtil::readBool(*tcpSocket);
    ret.secondIsLoad = BinaryUtil::readBool(*tcpSocket);
    ret.hasApu = BinaryUtil::readBool(*tcpSocket);
    ret.hasFlaps = BinaryUtil::readBool(*tcpSocket);
    ret.hasSpoilers = BinaryUtil::readBool(*tcpSocket);
    ret.hasElevTrim = BinaryUtil::readBool(*tcpSocket);
    ret.hasRudderTrim = BinaryUtil::readBool(*tcpSocket);
    ret.hasAileronTrim = BinaryUtil::readBool(*tcpSocket);
    ret.hasEgt = BinaryUtil::readBool(*tcpSocket);
    ret.fuelQtyByVolume = BinaryUtil::readBool(*tcpSocket);
    ret.fuelFlowByVolume = BinaryUtil::readBool(*tcpSocket);
    ret.numEngines = BinaryUtil::readInt8_t(*tcpSocket);
    ret.numTanks = BinaryUtil::readInt8_t(*tcpSocket);
    ret.type = BinaryUtil::readInt8_t(*tcpSocket);
    return ret;
}
