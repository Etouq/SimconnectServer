#include "Logger.hpp"

#ifdef LOG_TO_FILE
#include <QStandardPaths>
#include <QDateTime>
#include <QDir>
#endif

void Logger::init()
{
#ifdef LOG_TO_FILE
    QDir dataDirs(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
    dataDirs.mkpath("AppData/Roaming/Flight Display Companion");

    s_logFile.setFileName(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/AppData/Roaming/Flight Display Companion/server.log");
    bool fileAlreadyExists = s_logFile.exists();
    s_logFile.open(QIODevice::WriteOnly | QIODevice::Append);

    std::string data = "";

    if (fileAlreadyExists)
        data += "\n\n\n\n\n\n\n\n\n\n";

    data += "[" + QDateTime::currentDateTimeUtc().toString("yyyy-MM-ddTHH:mm:ss.zzz").toStdString() + "]: Start of new log\n\n";

    s_logFile.write(data.c_str());

    s_logFile.close();

#endif
}
