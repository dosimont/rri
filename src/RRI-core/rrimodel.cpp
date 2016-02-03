#include "rrimodel.h"

RRIModel::RRIModel():objects(new QVector<RRIObject*>()),
                             microscopicModel(vector< vector<double> >()),
                             routineMap(BiQMap<int, int>())
{

}

void RRIModel::parseFile(QString fileName)
{
    currentFileName=fileName;
    QFile file(currentFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        //TODO exception
        return;
    }else{
        CSV csv(&file);
        QStringList stringList;
        int i=0;
        for (stringList=csv.parseLine();stringList.size()>0;stringList=csv.parseLine()){
            RRIObject* tempObject=new RRIObject();
            tempObject->setId(stringList[RRI_CSV_ID]);
            tempObject->setSample(stringList[RRI_CSV_SAMPLE]);
            tempObject->setTsPercentage(stringList[RRI_CSV_TS_PERCENTAGE]);
            tempObject->setTsAbsolute(stringList[RRI_CSV_TS_ABSOLUTE]);
            tempObject->setCallstackLvl(stringList[RRI_CSV_CALLSTACK_LVL]);
            tempObject->setRoutineId(stringList[RRI_CSV_ROUTINE_ID]);
            tempObject->setCodelineId(stringList[RRI_CSV_CODELINE_ID]);
            if (!routineMap.containsValue(tempObject->getRoutineId())){
                routineMap.add(i++,tempObject->getRoutineId());
            }
            objects->append(tempObject);
            addToMicroscopicModel(tempObject);
        }
    }
}

void RRIModel::addToMicroscopicModel(RRIObject *object)
{
    while (microscopicModel.size()<(unsigned int) object->getSample()){
        microscopicModel.push_back(vector<double>());
    }
    for (unsigned int i=0; i<microscopicModel.size();i++){
        while (microscopicModel[i].size()<(unsigned int)routineMap.getFromValue(object->getRoutineId())){
            microscopicModel[i].push_back(0.0);
        }
    }
    microscopicModel[object->getSample()][routineMap.getFromValue(object->getRoutineId())]+=1.0;
}
