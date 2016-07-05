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

#include "rriredistributedmodel.h"

RRIRedistributedModel::RRIRedistributedModel():RedistributedModel()
{

}

RRIRedistributedModel::RRIRedistributedModel(MicroscopicModel *microscopicModel, MacroscopicModel *macroscopicModel):
    RedistributedModel(microscopicModel, macroscopicModel)
{
    rRIMicroscopicModel=dynamic_cast<RRIMicroscopicModel*>(microscopicModel);
    oMacroscopicModel=dynamic_cast<OMacroscopicModel*>(macroscopicModel);
}

RRIRedistributedModel::~RRIRedistributedModel()
{
    for (int i=0; i<rRIParts.size(); i++){
        delete rRIParts[i];
    }
}

void RRIRedistributedModel::setMicroscopicModel(MicroscopicModel *value)
{
    rRIMicroscopicModel=dynamic_cast<RRIMicroscopicModel*>(value);
}

void RRIRedistributedModel::setMacroscopicModel(MacroscopicModel *value)
{
    oMacroscopicModel=dynamic_cast<OMacroscopicModel*>(value);
}

QMap<RRIPart*, RRIRoutineInfo*> RRIRedistributedModel::generateRoutines(double minPercentage)
{
    hv=false;
    for (int i=0; i<oMacroscopicModel->getParts().size(); i++){
        rRIParts.push_back(new RRIPart(oMacroscopicModel->getParts().at(i)));
        rRIParts[i]->setRoutines(rRIMicroscopicModel->getTimeSlices());
        if (rRIParts[i]->getRoutines().size()==0){
            partsAsString.push_back("void");
            partsAsInteger.push_back(-1);
            partsAsIndex.push_back(-1);
            hv=true;
        }else{
            RRIRoutineInfo* mainRoutine=rRIParts[i]->getRoutines().values()[0];
            for (RRIRoutineInfo* currentRoutine:rRIParts[i]->getRoutines().values()){
                if (currentRoutine->getPercentageDuration()>=minPercentage){
                    if (currentRoutine->getAverageCallStackLevel()<mainRoutine->getAverageCallStackLevel()){
                        mainRoutine=currentRoutine;
                    }
                    else if (currentRoutine->getAverageCallStackLevel()==mainRoutine->getAverageCallStackLevel()&&currentRoutine->getPercentageDuration()>mainRoutine->getPercentageDuration()){
                        mainRoutine=currentRoutine;
                    }
                }else{
                    if (currentRoutine->getPercentageDuration()>mainRoutine->getPercentageDuration()){
                        mainRoutine=currentRoutine;
                    }else if(currentRoutine->getPercentageDuration()==mainRoutine->getPercentageDuration()&&currentRoutine->getAverageCallStackLevel()<mainRoutine->getAverageCallStackLevel()){
                        mainRoutine=currentRoutine;
                    }
                }
            }
        mainRoutineMap.insert(rRIParts[i], mainRoutine);
        partsAsString.push_back(mainRoutineMap[rRIParts[i]]->toString());
        partsAsInteger.push_back(mainRoutineMap[rRIParts[i]]->getId());
        partsAsIndex.push_back(mainRoutineMap[rRIParts[i]]->getIndex());
        }
    }
    return mainRoutineMap;
}


QVector<RRIObject *> RRIRedistributedModel::generateCodelines()
{
    QVector<RRIObject*> objects;
    for (RRIPart* part:mainRoutineMap.keys()){
        objects+=part->getCompatibleObjects(mainRoutineMap[part]->getIndex());
    }
    return objects;
}

QVector<QString> RRIRedistributedModel::getPartsAsString(){
    return partsAsString;
}

QVector<int> RRIRedistributedModel::getPartsAsInteger(){
    return partsAsInteger;
}

QVector<int> RRIRedistributedModel::getPartsAsIndex(){
    return partsAsIndex;
}

bool RRIRedistributedModel::hasVoid()
{
    return hv;
}

QVector<RRIPart *> RRIRedistributedModel::getRRIParts() const
{
    return rRIParts;
}
