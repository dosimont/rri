#ifndef ROUTINEPROFILE_H
#define ROUTINEPROFILE_H

#include <QString>
#include <QMap>
#include <QTextStream>
#include <QList>
#include "profiling_constants.h"

class RoutineProfile
{
public:
    RoutineProfile();
    RoutineProfile(QString name);
    void addToAvg(QString region, QString counter, float value, float duration, float ratio, int weight);
    float getSlopeAvg(QString counter);
    QString getName() const;
    void setName(const QString &value);

    int getId() const;
    void setId(int value);

    float getCurrentDuration(QString counter) const;

    QMap<QString, float> getCurrentSlope() const;
    QMap<QString, float> getCurrentDuration() const;

    friend QTextStream& operator<<(QTextStream& out, RoutineProfile profile);
    friend QTextStream& operator<<(QTextStream& out, RoutineProfile* profile);

    QList<QString> getRegions() const;

private:
    QString name;
    QMap<QString, float> currentSlope;
    QMap<QString, float> currentDuration;
    QList<QString> regions;
};

#endif // ROUTINEPROFILE_H
