/*  RRI - Relevant Routine Identifier
*  Copyright (C) 2016  Damien Dosimont
*  
*  This file is part of RRI.
*  
*  RRI is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*  
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
                routines[currentRoutine]->addToAverageCallStackLevel(currentRoutines[currentRoutine]->getAverageCallStackLevel());
            }
        }
    }
    for(RRIRoutineInfo* routine : routines.values()){
       routine->normalizePercentageDuration(getSizeTimeSlice());
       routine->normalizeAverageCallStackLevel();
    }
}



QMap<int, RRIRoutineInfo *> RRIPart::getRoutines() const
{
    return routines;
}

QVector<RRIObject *> RRIPart::getCompatibleObjects(int index)
{
    QVector<RRIObject*> compatibleObjects;
    for (RRITimeSlice* tS:timeSlices){
        compatibleObjects+=tS->getCompatibleObjects(index);
    }
    return compatibleObjects;
}


