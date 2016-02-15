#ifndef RRIOBJECT_H
#define RRIOBJECT_H

#include <QString>

class RRIObject
{
public:
    RRIObject();

    int getId() const;
    void setId(int value);
    void setId(QString value);

    int getSample() const;
    void setSample(int value);
    void setSample(QString value);

    double getTsPercentage() const;
    void setTsPercentage(double value);
    void setTsPercentage(QString value);

    int getTsAbsolute() const;
    void setTsAbsolute(int value);
    void setTsAbsolute(QString value);

    int getCallstackLvl() const;
    void setCallstackLvl(int value);
    void setCallstackLvl(QString value);

    int getRoutineId() const;
    void setRoutineId(int value);
    void setRoutineId(QString value);

    QString getRoutineName() const;
    void setRoutineName(QString value);

    int getCodelineId() const;
    void setCodelineId(int value);
    void setCodelineId(QString value);

    int getCodeline() const;
    void setCodeline(int value);
    void setCodeline(QString value);

    QString getFileName() const;
    void setFileName(const QString &value);

private:
    int id;
    int sample;
    double tsPercentage;
    int tsAbsolute;
    int callstackLvl;
    int routineId;
    QString routineName;
    QString fileName;
    int codelineId;
    int codeline;
};

#endif // RRIOBJECT_H
