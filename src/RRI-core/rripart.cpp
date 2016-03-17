#include "rripart.h"


RRIPart::RRIPart(Part *part):Part(part->getTotalTimeSlice())
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

void RRIPart::setRoutines(QVector<RRITimeSlice *> tS)
{
    if (tS.size()<getLastTimeSlice()){
        return;
    }
    for (int i=getFirstTimeSlice(); i<=getLastTimeSlice(); i++){
        timeSlices.push_back(tS[i]);
        QMap<int, RRIRoutineInfo *>currentRoutines=tS[i]->getRoutines();
        for(int currentRoutine : currentRoutines.keys()){
            if (!routines.contains(currentRoutine)){
                routines.insert(currentRoutine, new RRIRoutineInfo(currentRoutines[currentRoutine]));
            }
            else{
                routines[currentRoutine]->addToPercentageDuration(currentRoutines[currentRoutine]->getPercentageDuration());
                //routines[currentRoutine]->addToAverageCallStackLevel(currentRoutines[currentRoutine]->getAverageCallStackLevel());
            }
        }
    }
    for(RRIRoutineInfo* routine : routines.values()){
       routine->normalizePercentageDuration(getSizeTimeSlice());
       //routine->normalizeAverageCallStackLevel();
    }
}



QMap<int, RRIRoutineInfo *> RRIPart::getRoutines() const
{
    return routines;
}

QVector<RRIObject *> RRIPart::getCompatibleObjects(int routine)
{
    QVector<RRIObject*> compatibleObjects;
    for (RRITimeSlice* tS:timeSlices){
        compatibleObjects+=tS->getCompatibleObjects(routine);
    }
    return compatibleObjects;
}


