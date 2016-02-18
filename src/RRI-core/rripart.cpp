#include "rripart.h"


RRIPart::RRIPart(Part *part):Part(part->getTotalTimeSlice()),
                            routines(QMap<int, RRIRoutineInfo*>())
{
    setFirstTimeSlice(part->getFirstTimeSlice());
    setLastTimeSlice(part->getLastTimeSlice());
}

RRIPart::~RRIPart()
{
    for(int routine : routines.keys()){
        delete routines[routine];
    }
}

void RRIPart::setRoutines(QVector<RRITimeSlice *> timeSlices)
{
    if (timeSlices.size()<getLastTimeSlice()){
        return;
    }
    for (int i=getFirstTimeSlice(); i<getLastTimeSlice(); i++){
        QMap<int, RRIRoutineInfo *>currentRoutines=timeSlices[i]->getRoutines();
        for(int currentRoutine : currentRoutines.keys()){
            if (!routines.contains(currentRoutine)){
                routines.insert(currentRoutine, new RRIRoutineInfo(currentRoutines[currentRoutine]));
            }
            else{
                routines[currentRoutine]->addToPercentageDuration(currentRoutines[currentRoutine]->getPercentageDuration());
                routines[currentRoutine]->addToAverageCallStackLevel(currentRoutines[currentRoutine]->getAverageCallStackLevel());
            }
        }
    }
    for(RRIRoutineInfo* routine : routines.values()){
       routine->normalizePercentageDuration(getSizeTimeSlice());
       routine->normalizeAverageCallStackLevel(getSizeTimeSlice());
    }
}



QMap<int, RRIRoutineInfo *> RRIPart::getRoutines() const
{
    return routines;
}


