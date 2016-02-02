#include "rriobject.h"

RRIObject::RRIObject()
                     :id(0), sample(0), tsPercentage(0),
                     tsAbsolute(0), callstackLvl(0),
                     routineId(0), routineName(0),
                     codelineId(0), codelineNumber(0)
{

}


RRIObject::RRIObject(int id, int sample, double tsPercentage,
                     int tsAbsolute, int callstackLvl, int routineId,
                     int routineName, int codelineId, int codelineNumber)
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

int RRIObject::getSample() const
{
    return sample;
}

void RRIObject::setSample(int value)
{
    sample = value;
}

double RRIObject::getTsPercentage() const
{
    return tsPercentage;
}

void RRIObject::setTsPercentage(double value)
{
    tsPercentage = value;
}

int RRIObject::getTsAbsolute() const
{
    return tsAbsolute;
}

void RRIObject::setTsAbsolute(int value)
{
    tsAbsolute = value;
}

int RRIObject::getCallstackLvl() const
{
    return callstackLvl;
}

void RRIObject::setCallstackLvl(int value)
{
    callstackLvl = value;
}

int RRIObject::getRoutineId() const
{
    return routineId;
}

void RRIObject::setRoutineId(int value)
{
    routineId = value;
}

int RRIObject::getRoutineName() const
{
    return routineName;
}

void RRIObject::setRoutineName(int value)
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

int RRIObject::getCodelineNumber() const
{
    return codelineNumber;
}

void RRIObject::setCodelineNumber(int value)
{
    codelineNumber = value;
}
