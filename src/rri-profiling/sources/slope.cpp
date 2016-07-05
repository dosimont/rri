#include "slope.h"

Slope::Slope()
{

}

Slope::Slope(QString region, QString counter):region(region), counter(counter)
{

}

QString Slope::getRegion() const
{
    return region;
}

void Slope::setRegion(const QString &value)
{
    region = value;
}

QString Slope::getCounter() const
{
    return counter;
}

void Slope::setCounter(const QString &value)
{
    counter = value;
}

void Slope::addPoint(float timeStamp, float value, float unknown)
{
    timeStamps.push_back(timeStamp);
    values.push_back(value);
    unknowns.push_back(unknown);
}

QVector<int> Slope::indicesInTimeRegion(float minTimeStamp, float maxTimeStamp)
{
    QVector<int> indices;
    for (int i=0; i<timeStamps.size(); i++){
        if (timeStamps[i]>=minTimeStamp&&timeStamps[i]<=maxTimeStamp){
            indices.push_back(i);
        }
    }
    return indices;
}

float Slope::mean(float minTimeStamp, float maxTimeStamp)
{
    QVector<int> indices=indicesInTimeRegion(minTimeStamp, maxTimeStamp);
    float mean=0;
    for (int i:indices){
        mean+=values[i];
    }
    mean/=indices.size();
    return mean;
}
