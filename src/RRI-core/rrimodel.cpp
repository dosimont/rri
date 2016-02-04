#include "rrimodel.h"

RRIModel::RRIModel():MicroscopicModel(),objects(new QVector<RRIObject*>()),
                             routineMap(BiQMap<int, int>())
{

}

RRIModel::~RRIModel()
{
    for (int i=0; i<objects->size(); i++){
        delete objects->at(i);
    }
    delete objects;
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
            tempObject->setId(stringList[CSV_RRI_ID]);
            tempObject->setSample(stringList[CSV_RRI_SAMPLE]);
            tempObject->setTsPercentage(stringList[CSV_RRI_TS_PERCENTAGE]);
            tempObject->setTsAbsolute(stringList[CSV_RRI_TS_ABSOLUTE]);
            tempObject->setCallstackLvl(stringList[CSV_RRI_CALLSTACK_LVL]);
            tempObject->setRoutineId(stringList[CSV_RRI_ROUTINE_ID]);
            tempObject->setCodelineId(stringList[CSV_RRI_CODELINE_ID]);
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
        microscopicModel.push_back(vector< vector<double> >());
    }
    for (unsigned int i=0; i<microscopicModel.size();i++){
        while (microscopicModel[i].size()<(unsigned int)routineMap.getFromValue(object->getRoutineId())){
            microscopicModel[i].push_back(vector<double>());
            microscopicModel[i][microscopicModel[i].size()-1][0]=0.0;
        }
    }
    microscopicModel[object->getSample()][routineMap.getFromValue(object->getRoutineId())][0]+=1.0;
}
