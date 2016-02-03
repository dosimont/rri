#include "rriobject.h"

RRIObject::RRIObject()
                     :id(0), sample(0), tsPercentage(0),
                     tsAbsolute(0), callstackLvl(0),
                     routineId(0), routineName(""),
                     codelineId(0), codelineNumber(0)
{

}


RRIObject::RRIObject(int id, int sample, double tsPercentage,
                     int tsAbsolute, int callstackLvl, int routineId,
                     QString routineName, int codelineId, int codelineNumber)
                     :id(id), sample(sample), tsPercentage(tsPercentage),
                     tsAbsolute(tsAbsolute), callstackLvl(callstackLvl),
                     routineId(routineId), routineName(routineName),
                     codelineId(codelineId), codelineNumber(codelineNumber)
{

}

int RRIObject::getId() const
{
    return id;
}

void RRIObject::setId(int value)
{
    id = value;
}

void RRIObject::setId(QString value)
{
    setId(value.toInt());
}

int RRIObject::getSample() const
{
    return sample;
}

void RRIObject::setSample(int value)
{
    sample = value;
}

void RRIObject::setSample(QString value)
{
    setSample(value.toInt());
}

double RRIObject::getTsPercentage() const
{
    return tsPercentage;
}

void RRIObject::setTsPercentage(double value)
{
    tsPercentage = value;
}

void RRIObject::setTsPercentage(QString value)
{
    setTsPercentage(value.toDouble());
}

int RRIObject::getTsAbsolute() const
{
    return tsAbsolute;
}

void RRIObject::setTsAbsolute(int value)
{
    tsAbsolute = value;
}

void RRIObject::setTsAbsolute(QString value)
{
    setTsAbsolute(value.toInt());
}

int RRIObject::getCallstackLvl() const
{
    return callstackLvl;
}

void RRIObject::setCallstackLvl(int value)
{
    callstackLvl = value;
}

void RRIObject::setCallstackLvl(QString value)
{
    setCallstackLvl(value.toInt());
}

int RRIObject::getRoutineId() const
{
    return routineId;
}

void RRIObject::setRoutineId(int value)
{
    routineId = value;
}

void RRIObject::setRoutineId(QString value)
{
    setRoutineId(value.toInt());
}

QString RRIObject::getRoutineName() const
{
    return routineName;
}

void RRIObject::setRoutineName(QString value)
{
    routineName = value;
}

int RRIObject::getCodelineId() const
{
    return codelineId;
}

void RRIObject::setCodelineId(int value)
{
    codelineId = value;
}

void RRIObject::setCodelineId(QString value)
{
    setCodelineId(value.toInt());
}

int RRIObject::getCodelineNumber() const
{
    return codelineNumber;
}

void RRIObject::setCodelineNumber(int value)
{
    codelineNumber = value;
}

void RRIObject::setCodelineNumber(QString value)
{
    setCodelineNumber(value.toInt());
}
