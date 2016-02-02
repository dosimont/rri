#ifndef RRIOBJECT_H
#define RRIOBJECT_H


class RRIObject
{
public:
    RRIObject();
    RRIObject(int id, int sample, double tsPercentage, int tsAbsolute,
              int callstackLvl, int routineId, int routineName, int codelineId, int codelineNumber);

    int getId() const;
    void setId(int value);

    int getSample() const;
    void setSample(int value);

    double getTsPercentage() const;
    void setTsPercentage(double value);

    int getTsAbsolute() const;
    void setTsAbsolute(int value);

    int getCallstackLvl() const;
    void setCallstackLvl(int value);

    int getRoutineId() const;
    void setRoutineId(int value);

    int getRoutineName() const;
    void setRoutineName(int value);

    int getCodelineId() const;
    void setCodelineId(int value);

    int getCodelineNumber() const;
    void setCodelineNumber(int value);

private:
    int id;
    int sample;
    double tsPercentage;
    int tsAbsolute;
    int callstackLvl;
    int routineId;
    //TODO add this field in csv
    int routineName;
    int codelineId;
    //TODO add this field in csv
    int codelineNumber;
};

#endif // RRIOBJECT_H
