#include "Logger.hpp"

#include <QDateTime>
#include <sstream>
#include <iostream>

void Logger::logOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    s_mutex.lock();

    std::ostringstream buf;

    switch (type)
    {
        case QtDebugMsg:
            buf << "D [";
            break;
        case QtWarningMsg:
            buf << "W [";
            break;
        case QtInfoMsg:
            buf << "I [";
            break;
        case QtCriticalMsg:
            buf << "C [";
            break;
        case QtFatalMsg:
            buf << "F [";
            break;
        default:
            buf << "U [";
            break;
    }

    buf << QDateTime::currentDateTimeUtc().toString("yyyy-MM-ddTHH:mm:ss.zzz").toStdString() << "] ";

    if (context.file)
    {
        const std::string filename(context.file);
        size_t lastSlash = filename.find_last_of('\\');
        if (lastSlash == std::string::npos)
            lastSlash = 0;
        else
            lastSlash += 1;
        buf << '(' << filename.substr(lastSlash) << ':' << context.line << ") ";
    }
    else if (context.function)
    {
        buf << '(' << context.function << ") ";
    }

    buf << msg.toStdString() << "\n";

    const std::string data = buf.str();

#ifdef LOG_TO_FILE

    s_logFile.open(QIODevice::WriteOnly | QIODevice::Append);

    s_logFile.write(data.c_str());

    s_logFile.close();

#endif

    std::cerr << data;

    s_mutex.unlock();
}