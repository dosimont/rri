#ifndef ROUTINEPROFILE_H
#define ROUTINEPROFILE_H

#include <QString>
#include <QMap>

class RoutineProfile
{
public:
    RoutineProfile();
    RoutineProfile(QString name);
    void addToAvg(QString counter, float value, float duration, float ratio, int weight);
    float getSlopeAvg(QString counter);
    QString getName() const;
    void setName(const QString &value);

    int getId() const;
    void setId(int value);

    float getCurrentDuration(QString counter) const;

    QMap<QString, float> getCurrentSlope() const;
    QMap<QString, float> getCurrentDuration() const;

private:
    QString name;
    int id;
    QMap<QString, float> currentSlope;
    QMap<QString, float> currentDuration;
};

#endif // ROUTINEPROFILE_H