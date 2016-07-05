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

QList<QString> RoutineProfile::getRegions() const
{
    return regions;
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
        out.setRealNumberNotation(QTextStream::FixedNotation);
            out<<profile->name<<PROFILING_SEP<<counter<<PROFILING_SEP<<profile->getSlopeAvg(counter)<<PROFILING_SEP<<profile->getCurrentDuration(counter)<<PROFILING_SEP;
            int i;
            for (i=0; i<profile->getRegions().size()-1;i++){
                out<<profile->getRegions()[i]<<PROFILING_SEP2;
            }
            if (profile->getRegions().size()>0){
                out<<profile->getRegions()[i];
            }
            out<<endl;
    }
    return out;
}
