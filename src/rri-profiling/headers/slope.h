#ifndef SLOPE_H
#define SLOPE_H

#include <QString>
#include <QVector>

class Slope
{
public:
    Slope();
    Slope(QString region, QString counter);

    QString getRegion() const;
    void setRegion(const QString &value);

    QString getCounter() const;
    void setCounter(const QString &value);

    void addPoint(float timeStamp, float value, float unknown);

    QVector<int> indicesInTimeRegion(float minTimeStamp, float maxTimeStamp);
    float mean(float minTimeStamp, float maxTimeStamp);

private:
    QString region;
    QString counter;
    QVector<float> timeStamps;
    QVector<float> values;
    QVector<float> unknowns;
};

#endif // SLOPE_H
