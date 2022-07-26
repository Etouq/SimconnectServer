#include "FlightplanManager.hpp"
#include <QFile>
#include <QXmlStreamReader>
#include <QFileInfo>
#include <QSettings>

void FlightplanManager::readFromFile(const QString &url)
{
    QSettings settings;
    settings.setValue("lastUsedPlnDir", QFileInfo(url).canonicalPath());
    QFile file(url);

    if (!file.open(QFile::ReadOnly))
    {
        return;
    }

    QXmlStreamReader xml(&file);

    while (!xml.atEnd())
    {
        if (xml.readNextStartElement() && xml.name() == QLatin1String("FlightPlan.FlightPlan"))
        {
            break;
        }
    }

    if (xml.atEnd())
    {
        qDebug() << "error parsing file";
        // error reading file so don't clear the current flightplan
        return; // TODO: raise some kind of error/signal
    }

    d_waypoints.clear();

    while (!xml.atEnd())
    {
        if (xml.readNextStartElement())
        {
            if (xml.name() == QLatin1String("ATCWaypoint"))
            {
                readNextWaypoint(xml);
            }
            else
                xml.skipCurrentElement();
        }
    }

    file.close();


    emit flightplanChanged();
}