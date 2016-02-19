#include "rritimeslice.h"

RRITimeSlice::RRITimeSlice():routines(QMap<int, RRIRoutineInfo*>()), objects(QVector<RRIObject*>())
{

}

RRITimeSlice::~RRITimeSlice()
{
    for (int i=0; i<routines.size(); i++){
        delete routines[i];
    }
}

void RRITimeSlice::addObject(RRIObject *object, int routine)
{
    objects.push_back(object);
    if (!routines.contains(routine)){
        routines.insert(routine, new RRIRoutineInfo());
        routines[routine]->setIndex(routine);
        routines[routine]->setId(object->getRoutineId());
        routines[routine]->setName(object->getRoutineName());
        routines[routine]->setFile(object->getFileName());
        routines[routine]->initPercentageDuration(1);
        routines[routine]->initAverageCallStackLevel(object->getCallstackLvl());
    }else{
        routines[routine]->addToPercentageDuration(1);
        routines[routine]->addToAverageCallStackLevel(object->getCallstackLvl());
    }
}

void RRITimeSlice::finalize()
{
    for (RRIRoutineInfo* routine:routines.values()){
        routine->normalizeAverageCallStackLevel();
        routine->normalizePercentageDuration(getSamples());
    }
    //if (routines.empty()){
    //    routines.insert(-1, new RRIRoutineInfo());
    //}
}

void RRITimeSlice::finalize(int count)
{
    for (RRIRoutineInfo* routine:routines.values()){
        routine->normalizeAverageCallStackLevel();
        routine->normalizePercentageDuration(count);
    }
    //if (routines.empty()){
    //    routines.insert(-1, new RRIRoutineInfo());
    //}
}

int RRITimeSlice::getSamples()
{
    if (objects.size()>=2){
        return objects.last()->getSample()-objects.first()->getSample()+1;
    }else{
        return objects.size();
    }
}

QMap<int, RRIRoutineInfo *> RRITimeSlice::getRoutines() const
{
    return routines;
}

QVector<RRIObject *> RRITimeSlice::getObjects() const
{
    return objects;
}

QVector<RRIObject *> RRITimeSlice::getCompatibleObjects(int routineId) const
{
    QVector<RRIObject *> compatibleObjects = QVector<RRIObject *>();
    for (RRIObject* object:objects){
        if (object->getRoutineId()==routineId){
            compatibleObjects.push_back(object);
        }
    }
    return compatibleObjects;
}
