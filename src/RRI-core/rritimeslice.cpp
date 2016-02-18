#include "rritimeslice.h"

RRITimeSlice::RRITimeSlice():routines(QMap<int, RRIRoutineInfo*>()), objects(QVector<RRIObject*>()), samples(0)
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
    if (objects.size()>1){
        if (object[objects.size()-2].getTsPercentage()<object[objects.size()-1].getTsPercentage())
            samples++;
    }
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
    for (int i=0; i<routines.size(); i++){
        routines[i]->normalizeAverageCallStackLevel(samples);
        routines[i]->normalizePercentageDuration(samples);
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
