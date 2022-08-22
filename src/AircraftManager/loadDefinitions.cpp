#include "AircraftManager.hpp"

#include <algorithm>
#include <QBuffer>
#include <QDir>
#include <QFile>

void AircraftManager::loadDefinitions()
{
    QDir dataDir(d_dataRoot + "/Definitions", "*.fdc", QDir::Name, QDir::Files | QDir::Readable);

    QFileInfoList files = dataDir.entryInfoList();



    QString firstWorkingKey;

    for (const QFileInfo &fileInfo : files)
    {
        QFile file(fileInfo.canonicalFilePath());

        if (file.open(QFile::ReadOnly))
        {
            QByteArray fileBytes = file.readAll();
            file.close();

            QBuffer fileBuffer(&fileBytes);
            fileBuffer.open(QBuffer::ReadOnly);

            definitions::FileVersion version = definitions::FileVersion::V3;
            fileBuffer.read(reinterpret_cast<char *>(&version), sizeof(version));

            definitions::AircraftDefinition newDefinition =
              definitions::AircraftDefinition::fromBinary(fileBuffer, version);

            fileBuffer.close();

            // select first found and working aircraft
            if (firstWorkingKey.isEmpty())
                firstWorkingKey = fileInfo.completeBaseName();

            d_definitions[fileInfo.completeBaseName()] = newDefinition;

            if (newDefinition.type == AircraftType::JET)
                d_jetKeys.append(fileInfo.completeBaseName());
            else if (newDefinition.type == AircraftType::PROP)
                d_propKeys.append(fileInfo.completeBaseName());
            else if (newDefinition.type == AircraftType::TURBOPROP)
                d_turbopropKeys.append(fileInfo.completeBaseName());
        }
    }

    std::sort(
      d_jetKeys.begin(),
      d_jetKeys.end(),
      [this](const QString &lhs, const QString &rhs)
      { return d_definitions.at(lhs).name.toUpper().localeAwareCompare(d_definitions.at(rhs).name.toUpper()) < 0; });
    std::sort(
      d_propKeys.begin(),
      d_propKeys.end(),
      [this](const QString &lhs, const QString &rhs)
      { return d_definitions.at(lhs).name.toUpper().localeAwareCompare(d_definitions.at(rhs).name.toUpper()) < 0; });
    std::sort(
      d_turbopropKeys.begin(),
      d_turbopropKeys.end(),
      [this](const QString &lhs, const QString &rhs)
      { return d_definitions.at(lhs).name.toUpper().localeAwareCompare(d_definitions.at(rhs).name.toUpper()) < 0; });

    // make sure the current definition key exists and is set
    if (d_currentDefinitionKey.isEmpty() || !d_definitions.contains(d_currentDefinitionKey))
        d_currentDefinitionKey = firstWorkingKey;
}
