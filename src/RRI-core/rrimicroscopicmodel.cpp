#include "rrimicroscopicmodel.h"

RRIMicroscopicModel::RRIMicroscopicModel():MicroscopicModel(),objects(new QVector<RRIObject*>()),
                             routineMap(BiQMap<int, QString>())
{

}

RRIMicroscopicModel::RRIMicroscopicModel(MicroscopicModel microscopicModel):MicroscopicModel(microscopicModel),objects(new QVector<RRIObject*>()),
    routineMap(BiQMap<int, QString>())
{

}

RRIMicroscopicModel::~RRIMicroscopicModel()
{
    for (int i=0; i<objects->size(); i++){
        delete objects->at(i);
    }
    delete objects;
}

void RRIMicroscopicModel::parseFile(QString fileName, int timeSlices)
{
    currentFileName=fileName;
    if (timeSlices>2){
        buildWithPreAggregation(timeSlices);
    }else if (timeSlices==0){
        buildWithoutPreAggregation();
    }
}

RRIObject *RRIMicroscopicModel::buildRRIObject(QStringList fields)
{
    RRIObject* rRIObject=new RRIObject();
    rRIObject->setId(fields[CSV_RRI_ID]);
    rRIObject->setSample(fields[CSV_RRI_SAMPLE]);
    rRIObject->setTsPercentage(fields[CSV_RRI_TS_PERCENTAGE]);
    rRIObject->setTsAbsolute(fields[CSV_RRI_TS_ABSOLUTE]);
    rRIObject->setCallstackLvl(fields[CSV_RRI_CALLSTACK_LVL]);
    rRIObject->setRoutineId(fields[CSV_RRI_ROUTINE_ID]);
    rRIObject->setRoutineName(fields[CSV_RRI_ROUTINE_NAME]);
    rRIObject->setCodelineId(fields[CSV_RRI_CODELINE_ID]);
    rRIObject->setFileName(fields[CSV_RRI_FILE_NAME]);
    rRIObject->setCodeline(fields[CSV_RRI_CODELINE]);
    return rRIObject;
}

void RRIMicroscopicModel::buildWithoutPreAggregation()
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
        //header
        csv.parseLine();
        for (stringList=csv.parseLine();stringList.size()>1;stringList=csv.parseLine()){
            RRIObject* tempObject=buildRRIObject(stringList);
            if (!routineMap.containsValue(tempObject->getRoutineName())){
                routineMap.add(i++,tempObject->getRoutineName());
            }
            objects->append(tempObject);
            addToMicroscopicModel(tempObject);
        }
    }
}

void RRIMicroscopicModel::buildWithPreAggregation(int timeSlices)
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
        int i=0;
        //header
        csv.parseLine();
        for (stringList=csv.parseLine();stringList.size()>1;stringList=csv.parseLine()){
            RRIObject* tempObject=buildRRIObject(stringList);
            if (!routineMap.containsValue(tempObject->getRoutineName())){
                routineMap.add(i++,tempObject->getRoutineName());
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



void RRIMicroscopicModel::addToMicroscopicModel(RRIObject *object)
{
    while (matrix.size()<(unsigned int) object->getSample()+1){
        matrix.push_back(vector< vector<double> >());
    }
    for (unsigned int i=0; i<matrix.size();i++){
        while (matrix[i].size()<(unsigned int)routineMap.getFromValue(object->getRoutineName())+1){
            matrix[i].push_back(vector<double>());
            matrix[i][matrix[i].size()-1].push_back(0.0);
        }
    }
    matrix[object->getSample()][routineMap.getFromValue(object->getRoutineName())][0]+=1.0;
}

void RRIMicroscopicModel::addToPreAggregateMicroscopicModel(RRIObject *object, int timeSlice)
{
    for (unsigned int i=0; i<matrix.size();i++){
        while (matrix[i].size()<(unsigned int)routineMap.getFromValue(object->getRoutineName())+1){
            matrix[i].push_back(vector<double>());
            matrix[i][matrix[i].size()-1].push_back(0.0);
        }
    }
    matrix[timeSlice][routineMap.getFromValue(object->getRoutineName())][0]+=1.0;
}
