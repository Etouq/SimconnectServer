#include "FlightplanManager.hpp"
#include <QProcessEnvironment>
#include <QDir>
#include <QStringBuilder>
#include <QSettings>

QString FlightplanManager::getFileBasePath() const
{
    const QChar sep = QDir::separator();

    QSettings settings;

    if (settings.contains("lastUsedPlnDir")) {
        return settings.value("lastUsedPlnDir").toString();
    }

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    QDir dir(env.value("APPDATA") % sep % "Microsoft Flight Simulator");

    if (dir.exists())
        return dir.canonicalPath();

    dir.setPath(env.value("LOCALAPPDATA") % sep % "Packages" % sep % "Microsoft.FlightSimulator_8wekyb3d8bbwe");

    if (dir.exists())
        return dir.canonicalPath();

    dir.setPath(env.value("LOCALAPPDATA") % sep % "MSFSPackages");

    if (dir.exists())
        return dir.canonicalPath();


    return QDir::homePath();
}