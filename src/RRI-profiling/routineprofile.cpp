#include "routineprofile.h"

RoutineProfile::RoutineProfile()
{

}

QMap<QString, float> RoutineProfile::getCurrentSlope() const
{
    return currentSlope;
}

QMap<QString, float> RoutineProfile::getCurrentDuration() const
{
    return currentDuration;
}


RoutineProfile::RoutineProfile(QString name):name(name)
{

}

QString RoutineProfile::getName() const
{
    return name;
}

void RoutineProfile::setName(const QString &value)
{
    name = value;
}

float RoutineProfile::getCurrentDuration(QString counter) const
{
    return currentDuration[counter];
}


void RoutineProfile::addToAvg(QString region, QString counter, float value, float duration, float ratio, int weight)
{
    if (!currentSlope.contains(counter)){
        currentSlope.insert(counter, 0);
        currentDuration.insert(counter, 0);
    }
    currentSlope[counter]+=(value*duration*ratio*(float)weight);
    currentDuration[counter]+=duration*ratio*(float)weight;
    if (!regions.contains(region)){
        regions.push_back(region);
    }
}

float RoutineProfile::getSlopeAvg(QString counter)
{
    return currentSlope[counter]/currentDuration[counter];
}

QTextStream& operator<<(QTextStream& out, RoutineProfile profile)
{
    out<<&profile;
    return out;
}

QTextStream& operator<<(QTextStream& out, RoutineProfile* profile)
{
    for (QString counter:profile->currentSlope.keys()){
            out<<profile->name<<","<<counter<<","<<profile->getSlopeAvg(counter)<<","<<profile->getCurrentDuration(counter)<<endl;
    }
    return out;
}
