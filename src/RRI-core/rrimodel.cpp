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

void RRIModel::parseFile(QString fileName, int timeSlices)
{
    currentFileName=fileName;
    if (timeSlices>2){
        buildWithPreAggregation(timeSlices);
    }else if (timeSlices==-1){
        buildWithoutPreAggregation();
    }
}

RRIObject *RRIModel::buildRRIObject(QStringList fields)
{
    RRIObject* rRIObject=new RRIObject();
    rRIObject->setId(fields[CSV_RRI_ID]);
    rRIObject->setSample(fields[CSV_RRI_SAMPLE]);
    rRIObject->setTsPercentage(fields[CSV_RRI_TS_PERCENTAGE]);
    rRIObject->setTsAbsolute(fields[CSV_RRI_TS_ABSOLUTE]);
    rRIObject->setCallstackLvl(fields[CSV_RRI_CALLSTACK_LVL]);
    rRIObject->setRoutineId(fields[CSV_RRI_ROUTINE_ID]);
    rRIObject->setCodelineId(fields[CSV_RRI_CODELINE_ID]);
    return rRIObject;
}

void RRIModel::buildWithoutPreAggregation()
{
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
            RRIObject* tempObject=buildRRIObject(stringList);
            if (!routineMap.containsValue(tempObject->getRoutineId())){
                routineMap.add(i++,tempObject->getRoutineId());
            }
            objects->append(tempObject);
            addToMicroscopicModel(tempObject);
        }
    }
}

void RRIModel::buildWithPreAggregation(int timeSlices)
{
    QFile file(currentFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        RRIERR("Input file can not be open");
        return;
    }else{
        QVector<int> objectCount=QVector<int>();
        while (matrix.size()<(unsigned int) timeSlices){
            matrix.push_back(vector< vector<double> >());
            objectCount.push_back(0);
        }
        CSV csv(&file);
        QStringList stringList;
        int line=0;
        int i=0;
        for (stringList=csv.parseLine();stringList.size()>1;stringList=csv.parseLine()){
            RRIObject* tempObject=buildRRIObject(stringList);
            if (!routineMap.containsValue(tempObject->getRoutineId())){
                routineMap.add(i++,tempObject->getRoutineId());
            }
            objects->append(tempObject);
            addToPreAggregateMicroscopicModel(tempObject, (int) ((double)tempObject->getTsPercentage()*(double) timeSlices));
            objectCount[(int)((double)tempObject->getTsPercentage()*(double) timeSlices)]+=1;

        }
        for (unsigned int i=0; i<matrix.size(); i++){
            for (unsigned int j=0; j<matrix[i].size(); j++){
                matrix[i][j][0]/=(double) objectCount[i];
            }
        }
    }
}



void RRIModel::addToMicroscopicModel(RRIObject *object)
{
    while (matrix.size()<(unsigned int) object->getSample()+1){
        matrix.push_back(vector< vector<double> >());
    }
    for (unsigned int i=0; i<matrix.size();i++){
        //TODO change sample numeration
        while (matrix[i].size()<(unsigned int)routineMap.getFromValue(object->getRoutineId())+1){
            matrix[i].push_back(vector<double>());
            matrix[i][matrix[i].size()-1].push_back(0.0);
        }
    }
    matrix[object->getSample()][routineMap.getFromValue(object->getRoutineId())][0]+=1.0;
    //TODO change sample numeration
}

void RRIModel::addToPreAggregateMicroscopicModel(RRIObject *object, int timeSlice)
{
    for (unsigned int i=0; i<matrix.size();i++){
        while (matrix[i].size()<(unsigned int)routineMap.getFromValue(object->getRoutineId())+1){
            matrix[i].push_back(vector<double>());
            matrix[i][matrix[i].size()-1].push_back(0.0);
        }
    }
    matrix[timeSlice][routineMap.getFromValue(object->getRoutineId())][0]+=1.0;
}
