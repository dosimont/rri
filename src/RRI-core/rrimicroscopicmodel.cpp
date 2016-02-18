#include "rrimicroscopicmodel.h"

RRIMicroscopicModel::RRIMicroscopicModel():
                            MicroscopicModel(),
                            objects(QVector<RRIObject*>()),
                            timeSlices(QVector<RRITimeSlice*>()),
                            matrixIndexToRoutineId(BiQMap<int, int>())
{

}

RRIMicroscopicModel::RRIMicroscopicModel(MicroscopicModel microscopicModel):
                            MicroscopicModel(microscopicModel),
                            objects(QVector<RRIObject*>()),
                            timeSlices(QVector<RRITimeSlice*>()),
                            matrixIndexToRoutineId(BiQMap<int, int>())
{

}

RRIMicroscopicModel::~RRIMicroscopicModel()
{
    for (int i=0; i<objects.size(); i++){
        delete objects.at(i);
    }
    for (int i=0; i<timeSlices.size(); i++){
        delete timeSlices.at(i);
    }
}

void RRIMicroscopicModel::parseFile(QString fileName, int timeSlices)
{
    currentFileName=fileName;
    buildWithPreAggregation(timeSlices);

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

//deprecated
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
            if (!matrixIndexToRoutineId.containsValue(tempObject->getRoutineId())){
                matrixIndexToRoutineId.add(i++,tempObject->getRoutineId());
            }
            objects.push_back(tempObject);
            addToMicroscopicModel(tempObject);
        }
    }
}

void RRIMicroscopicModel::buildWithPreAggregation(int timeSliceNumber)
{
    QFile file(currentFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        RRIERR("Input file can not be open");
        return;
    }else{
        while (matrix.size()<(unsigned int) timeSliceNumber){
            matrix.push_back(vector< vector<double> >());
            timeSlices.push_back(new RRITimeSlice());
        }
        CSV csv(&file);
        QStringList stringList;
        int i=0;
        double currentTimeStamp=-1;
        //header
        csv.parseLine();
        for (stringList=csv.parseLine();stringList.size()>1;stringList=csv.parseLine()){
            RRIObject* tempObject=buildRRIObject(stringList);
            if (!matrixIndexToRoutineId.containsValue(tempObject->getRoutineId())){
                matrixIndexToRoutineId.add(i++,tempObject->getRoutineId());
            }
            objects.push_back(tempObject);
            addToPreAggregateMicroscopicModel(tempObject, (int) (tempObject->getTsPercentage()*(double) timeSliceNumber));
            if (tempObject->getTsPercentage()>currentTimeStamp){
                currentTimeStamp=tempObject->getTsPercentage();
            }else if(tempObject->getTsPercentage()<currentTimeStamp){
                RRIERR("Input file is not ordered");
                return;
            }
        }
        for (int i=0; i<timeSlices.size(); i++){
            timeSlices[i]->finalize();
        }
        for (unsigned int i=0; i<matrix.size(); i++){
            for (unsigned int j=0; j<matrix[i].size(); j++){
                matrix[i][j][0]/=(double)timeSlices[i]->getSamples();
            }
        }

    }
}


//deprecated
void RRIMicroscopicModel::addToMicroscopicModel(RRIObject *object)
{
    while (matrix.size()<(unsigned int) object->getSample()+1){
        matrix.push_back(vector< vector<double> >());
    }
    for (unsigned int i=0; i<matrix.size();i++){
        while (matrix[i].size()<(unsigned int)matrixIndexToRoutineId.getFromValue(object->getRoutineId())+1){
            matrix[i].push_back(vector<double>());
            matrix[i][matrix[i].size()-1].push_back(0.0);
        }
    }
    matrix[object->getSample()][matrixIndexToRoutineId.getFromValue(object->getRoutineId())][0]+=1.0;
}

void RRIMicroscopicModel::addToPreAggregateMicroscopicModel(RRIObject *object, int timeSlice)
{
    for (unsigned int i=0; i<matrix.size();i++){
        while (matrix[i].size()<(unsigned int)matrixIndexToRoutineId.getFromValue(object->getRoutineId())+1){
            matrix[i].push_back(vector<double>());
            matrix[i][matrix[i].size()-1].push_back(0.0);
        }
    }
    matrix[timeSlice][matrixIndexToRoutineId.getFromValue(object->getRoutineId())][0]+=1.0;
    timeSlices[timeSlice]->addObject(object, matrixIndexToRoutineId.getFromValue(object->getRoutineId()));
}

QVector<RRITimeSlice *> RRIMicroscopicModel::getTimeSlices() const
{
    return timeSlices;
}

BiQMap<int, int> RRIMicroscopicModel::getMatrixIndexToRoutineId() const
{
    return matrixIndexToRoutineId;
}
