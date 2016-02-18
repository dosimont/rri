#include "rriredistributedmodel.h"

RRIRedistributedModel::RRIRedistributedModel():RedistributedModel()
{

}

RRIRedistributedModel::RRIRedistributedModel(MicroscopicModel *microscopicModel, MacroscopicModel *macroscopicModel):
    RedistributedModel(microscopicModel, macroscopicModel),
    rRIParts(QVector<RRIPart*>()),
    mainRoutineMap(QMap<RRIPart*, RRIRoutineInfo*>())
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
        RRIRoutineInfo* mainRoutine=rRIParts[i]->getRoutines().first();
        for (RRIRoutineInfo* currentRoutine:rRIParts[i]->getRoutines().values()){
            RRIERR(currentRoutine->getId()<<" "<<currentRoutine->getName().toStdString()<<" "<<currentRoutine->getPercentageDuration()<<" "<<currentRoutine->getAverageCallStackLevel());
            if (currentRoutine->getPercentageDuration()>=minPercentage){
                if (currentRoutine->getAverageCallStackLevel()<mainRoutine->getAverageCallStackLevel()){
                    mainRoutine=currentRoutine;
                }
            }else{
                if (currentRoutine->getPercentageDuration()>mainRoutine->getPercentageDuration()){
                    mainRoutine=currentRoutine;
                }else if(currentRoutine->getPercentageDuration()>=mainRoutine->getPercentageDuration()&&currentRoutine->getAverageCallStackLevel()<mainRoutine->getAverageCallStackLevel()){
                    mainRoutine=currentRoutine;
                }
            }
        }
        mainRoutineMap.insert(rRIParts[i], mainRoutine);
    }
    for (int i=0; i<rRIParts.size(); i++){
        partsAsStrings.insert(i, mainRoutineMap[rRIParts[i]]->getFile()+":"+mainRoutineMap[rRIParts[i]]->getName());
    }
    return mainRoutineMap;
}

QVector<QString> RRIRedistributedModel::getPartsAsStrings(){
    return partsAsStrings;
}
