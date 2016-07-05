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

#include "rritimeslice.h"

RRITimeSlice::RRITimeSlice()
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

void RRITimeSlice::addObject(RRIObject *object)
{
    objects.push_back(object);
    if (!routines.contains(object->getIndex())){
        routines.insert(object->getIndex(), new RRIRoutineInfo());
        routines[object->getIndex()]->setIndex(object->getIndex());
        routines[object->getIndex()]->setId(object->getRoutineId());
        routines[object->getIndex()]->setName(object->getRoutineName());
        routines[object->getIndex()]->setFile(object->getFileName());
        routines[object->getIndex()]->initPercentageDuration(1);
        routines[object->getIndex()]->initAverageCallStackLevel(object->getCallstackLvl());
    }else{
        routines[object->getIndex()]->addToPercentageDuration(1);
        routines[object->getIndex()]->addToAverageCallStackLevel(object->getCallstackLvl());
    }
}

void RRITimeSlice::finalize()
{
    for (RRIRoutineInfo* routine:routines.values()){
        routine->normalizeAverageCallStackLevel();
        routine->normalizePercentageDuration(getSampleNumber());
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

int RRITimeSlice::getSampleNumber()
{
    if (objects.size()>=2){
        int max=objects[0]->getSample();
        int min=objects[0]->getSample();
        for (RRIObject* object: objects){
            if (object->getSample()>max){
                max=object->getSample();
            }
            if (object->getSample()<min)
                min=object->getSample();
        }
        return max-min+1;
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

QVector<RRIObject *> RRITimeSlice::getCompatibleObjects(int index) const
{
    QVector<RRIObject *> compatibleObjects = QVector<RRIObject *>();
    for (RRIObject* object:objects){
        if (object->getIndex()==index){
            compatibleObjects.push_back(object);
        }
    }
    return compatibleObjects;
}
