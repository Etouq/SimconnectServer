#include "AircraftManager.hpp"

#include <QBuffer>
#include <QDir>
#include <QFile>


void AircraftManager::loadDefinitions()
{
    QDir dataDir(d_dataRoot + "/Definitions", "*.def", QDir::Unsorted, QDir::Files | QDir::Readable);

    QFileInfoList files = dataDir.entryInfoList();


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


            d_definitions[fileInfo.completeBaseName()] = newDefinition;

            if (newDefinition.type == AircraftType::JET)
                d_jetKeys.append(fileInfo.completeBaseName());
            else if (newDefinition.type == AircraftType::PROP)
                d_propKeys.append(fileInfo.completeBaseName());
            else if (newDefinition.type == AircraftType::TURBOPROP)
                d_turbopropKeys.append(fileInfo.completeBaseName());
        }
    }
}
