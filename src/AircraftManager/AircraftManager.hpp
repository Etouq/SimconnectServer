#ifndef __AIRCRAFT_MANAGER_HPP__
#define __AIRCRAFT_MANAGER_HPP__

#include <QObject>
#include <QHash>

#include "common/definitions/AircraftDefinition/AircraftDefinition.hpp"

class AircraftManager : public QObject
{
    Q_OBJECT

public:

    AircraftManager();

    Q_INVOKABLE int getNumJets() const
    {
        return d_jetKeys.size();
    }

    Q_INVOKABLE int getNumProp() const
    {
        return d_propKeys.size();
    }

    Q_INVOKABLE int getNumTurboprop() const
    {
        return d_turbopropKeys.size();
    }

    Q_INVOKABLE QString getJetName(int idx) const
    {
        return d_definitions.value(d_jetKeys.at(idx)).name;
    }

    Q_INVOKABLE QString getPropName(int idx) const
    {
        return d_definitions.value(d_propKeys.at(idx)).name;
    }

    Q_INVOKABLE QString getTurbopropName(int idx) const
    {
        return d_definitions.value(d_turbopropKeys.at(idx)).name;
    }

    Q_INVOKABLE QString getJetImagePath(int idx) const
    {
        return d_dataRoot + "/Thumbnails/" + d_jetKeys.at(idx) + ".png";
    }

    Q_INVOKABLE QString getPropImagePath(int idx) const
    {
        return d_dataRoot + "/Thumbnails/" + d_propKeys.at(idx) + ".png";
    }

    Q_INVOKABLE QString getTurbopropImagePath(int idx) const
    {
        return d_dataRoot + "/Thumbnails/" + d_turbopropKeys.at(idx) + ".png";
    }

    Q_INVOKABLE void selectJet(int idx)
    {
        emit aircraftSelected(d_definitions.value(d_jetKeys.at(idx)));
    }
    Q_INVOKABLE void selectProp(int idx)
    {
        emit aircraftSelected(d_definitions.value(d_propKeys.at(idx)));
    }
    Q_INVOKABLE void selectTurboprop(int idx)
    {
        emit aircraftSelected(d_definitions.value(d_turbopropKeys.at(idx)));
    }

signals:

    void aircraftSelected(const definitions::AircraftDefinition &definition);

private:

    void loadDefinitions();

    QString d_dataRoot;

    QHash<QString, definitions::AircraftDefinition> d_definitions;

    QStringList d_jetKeys;
    QStringList d_propKeys;
    QStringList d_turbopropKeys;

};

#endif // __AIRCRAFT_MANAGER_HPP__