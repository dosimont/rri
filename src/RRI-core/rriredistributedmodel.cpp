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

QMap<RRIPart*, int> RRIRedistributedModel::generateRoutines(float minPercentage)
{
    for (int i=0; i<oMacroscopicModel->getParts().size(); i++){
        rRIParts.push_back(new RRIPart(oMacroscopicModel->getParts().at(i)));
        rRIParts[i]->setRoutinesFromMicroscopicModel(microscopicModel->getMatrix());
        float mainRoutineValue=0.0;
        int mainRoutineIndex=-1;
        for (int j=0; j<rRIParts[i]->getRoutineNumber(); j++){
            float currentRoutineValue=rRIParts[i]->getRoutines().at(j);
            if (currentRoutineValue<minPercentage){
                if (currentRoutineValue>mainRoutineValue){
                    mainRoutineValue=currentRoutineValue;
                    mainRoutineIndex=j;
                }
            }
            if (currentRoutineValue>minPercentage){
                if (currentRoutineValue<mainRoutineValue){
                    mainRoutineValue=currentRoutineValue;
                    mainRoutineIndex=j;
                }
                else if (mainRoutineValue<minPercentage){
                mainRoutineValue=currentRoutineValue;
                mainRoutineIndex=j;
                }
            }
        }
        mainRoutineMap.insert(rRIParts[i], mainRoutineIndex);
    }
    return mainRoutineMap;
}

QMap<Part*, QString> RRIRedistributedModel::getParts(){
    for (int i=0; i<rRIParts.size(); i++){
        partMap.insert(rRIParts[i], rRIMicroscopicModel->getRoutineIdToFileRoutineName().getFromKey(mainRoutineMap[rRIParts[i]]));
    }
    return partMap;
}
