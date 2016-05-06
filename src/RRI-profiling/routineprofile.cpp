#include "routineprofile.h"

RoutineProfile::RoutineProfile():currentSlope(0), currentDuration(0)
{

}

QMap<QString, float> RoutineProfile::getCurrentSlope() const
{
    return currentSlope;
}

QMap<QString, float> RoutineProfile::getCurrentSlope() const
{
    return currentSlope;
}

QMap<QString, float> RoutineProfile::getCurrentDuration() const
{
    return currentDuration;
}


RoutineProfile::RoutineProfile(QString name, int id):name(name), id(id)
{

}

QString routineProfile::getName() const
{
    return name;
}

void routineProfile::setName(const QString &value)
{
    name = value;
}


int routineProfile::getId() const
{
    return id;
}

void routineProfile::setId(int value)
{
    id = value;
}

float routineProfile::getCurrentDuration(QString counter) const
{
    return currentDuration[counter];
}


void RoutineProfile::addToAvg(QString counter, float value, float duration, float ratio, int weight)
{
    if (!currentSlope.contains(counter)){
        currentSlope.insert(counter, 0);
        currentDuration.insert(counter, 0);
    }
    currentSlope[counter]+=(value*duration*ratio*(float)weight);
    currentDuration[counter]+=duration*ratio*(float)weight;
}

float RoutineProfile::getSlopeAvg(QString counter)
{
    return currentSlope[counter]/currentDuration[counter];
}
