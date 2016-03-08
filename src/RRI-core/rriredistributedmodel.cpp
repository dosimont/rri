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
    for (int i=0; i<oMacroscopicModel->getParts().size(); i++){
        rRIParts.push_back(new RRIPart(oMacroscopicModel->getParts().at(i)));
        rRIParts[i]->setRoutines(rRIMicroscopicModel->getTimeSlices());
        if (rRIParts[i]->getRoutines().size()==0){
            partsAsStrings.insert(i, "void");
        }else{
        RRIRoutineInfo* mainRoutine=rRIParts[i]->getRoutines().first();
        for (RRIRoutineInfo* currentRoutine:rRIParts[i]->getRoutines().values()){
            if (currentRoutine->getPercentageDuration()>=minPercentage){
                if (currentRoutine->getAverageCallStackLevel()<mainRoutine->getAverageCallStackLevel()){
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
        partsAsStrings.insert(i, mainRoutineMap[rRIParts[i]]->getFile()+":"+mainRoutineMap[rRIParts[i]]->getName());
        }
    }
    return mainRoutineMap;
}

QVector<RRIObject *> RRIRedistributedModel::generateCodelines()
{
    QVector<RRIObject*> objects;
    for (RRIPart* part:mainRoutineMap.keys()){
        objects+=part->getCompatibleObjects(mainRoutineMap[part]->getId());
    }
    return objects;
}

QVector<QString> RRIRedistributedModel::getPartsAsStrings(){
    return partsAsStrings;
}
