#include "rrimodel.h"

RRIModel::RRIModel():MicroscopicModel(),objects(new QVector<RRIObject*>()),
                             routineMap(BiQMap<int, int>())
{

}

RRIModel::RRIModel(MicroscopicModel microscopicModel):MicroscopicModel(microscopicModel),objects(new QVector<RRIObject*>()),
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
        RRIERR("Input file can not be open");
        return;
    }else{
        CSV csv(&file);
        RRILOG("CSV object has been initalized");
        QStringList stringList;
        int i=0;
        for (stringList=csv.parseLine();stringList.size()>1;stringList=csv.parseLine()){
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
    while (matrix.size()<(unsigned int) object->getSample()){
        matrix.push_back(vector< vector<double> >());
    }
    for (unsigned int i=0; i<matrix.size();i++){
        //TODO change sample numeration
        while (matrix[i].size()<(unsigned int)routineMap.getFromValue(object->getRoutineId())+1){
            matrix[i].push_back(vector<double>());
            matrix[i][matrix[i].size()-1].push_back(0.0);
        }
    }
    matrix[object->getSample()-1][routineMap.getFromValue(object->getRoutineId())][0]+=1.0;
    //TODO change sample numeration
}
