#include "rripart.h"


RRIPart::RRIPart(Part *part):Part(part->getTotalTimeSlice()), routineNumber(0), routines(QVector<float>())
{
    setFirstTimeSlice(part->getFirstTimeSlice());
    setLastTimeSlice(part->getLastTimeSlice());
}

int RRIPart::getRoutineNumber() const
{
    return routineNumber;
}

void RRIPart::setRoutinesFromMicroscopicModel(vector< vector <vector <double> > > matrix)
{
    routineNumber = matrix.at(0).at(0).size();
    for (int i=0; i<routineNumber; i++){
        routines.push_back(0.0);
    }
    for (int i=getFirstTimeSlice(); i<=getLastTimeSlice(); i++){
        for (int j=0; j<routineNumber; j++){
            routines[j]++;
        }
    }
    for (int i=0; i<routineNumber; i++){
        routines[i]/=getTotalTimeSlice();
    }
}


