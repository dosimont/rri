#ifndef RRIROUTINEINFO_H
#define RRIROUTINEINFO_H

#include <QString>

class RRIRoutineInfo
{
public:
    RRIRoutineInfo();
    //constructor by copy
    RRIRoutineInfo(RRIRoutineInfo* rRIRoutineInfo);
    int getIndex() const;
    void setIndex(int value);

    int getId() const;
    void setId(int value);

    QString getFile() const;
    void setFile(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    double getPercentageDuration() const;
    void initPercentageDuration(double value);
    void addToPercentageDuration(double value);
    void normalizePercentageDuration(double value);
    void setPercentageDuration(double value);

    double getAverageCallStackLevel() const;
    void initAverageCallStackLevel(double value);
    void addToAverageCallStackLevel(double value);
    void normalizeAverageCallStackLevel(double value);
    void setAverageCallStackLevel(double value);

private:
    int index;
    int id;
    QString file;
    QString name;
    double percentageDuration;
    double averageCallStackLevel;
};

#endif // RRIROUTINEINFO_H
