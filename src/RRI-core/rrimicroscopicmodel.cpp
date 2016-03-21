#include "rrimicroscopicmodel.h"

RRIMicroscopicModel::RRIMicroscopicModel():
                            MicroscopicModel()
{

}

RRIMicroscopicModel::RRIMicroscopicModel(MicroscopicModel microscopicModel):
                            MicroscopicModel(microscopicModel)
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

void RRIMicroscopicModel::generate(QTextStream *textStream, int timeSlices)
{
    stream=textStream;
    build(timeSlices);
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
    qDebug()<<rRIObject;
    return rRIObject;
}

RRIObject *RRIMicroscopicModel::buildRRIObject(QStringList fields, int line)
{
    if (fields.size()!=CSV_RRI_SIZE){
        RRIERR("Error while parsing the file: line "<<line<< ", expected "<< CSV_RRI_SIZE<< " fields, has found "<< fields.size());
        return new RRIObject();
    }else{
        return buildRRIObject(fields);
    }
}

void RRIMicroscopicModel::build(int timeSliceNumber)
{
    hv=false;
    while (matrix->size()<(unsigned int) timeSliceNumber){
        matrix->push_back(vector< vector<double> >());
        timeSlices.push_back(new RRITimeSlice());
    }
    DummyStreamReader streamReader(stream);
    QStringList stringList;
    int i=0;
    int line=0;
    double currentTimeStamp=-1;
    //header
    line++;
    streamReader.readline();
    for (stringList=streamReader.readline();!streamReader.isEnd();stringList=streamReader.readline()){
        line++;
        RRIObject* tempObject=buildRRIObject(stringList, line);
        if (tempObject->getId()==-1){
            return;
        }
        if (tempObject->getTsPercentage()>currentTimeStamp){
            currentTimeStamp=tempObject->getTsPercentage();
        }else if(tempObject->getTsPercentage()<currentTimeStamp){
            RRIERR("Input file is not ordered");
            return;
        }
        if (!matrixIndexToRoutineId.containsValue(tempObject->getRoutineIdAndCallStack())){
            matrixIndexToRoutineId.add(i++,tempObject->getRoutineIdAndCallStack());
        }
        tempObject->setIndex(matrixIndexToRoutineId.getFromValue(tempObject->getRoutineIdAndCallStack()));
        objects.push_back(tempObject);
        addToMicroscopicModel(tempObject, (int) (tempObject->getTsPercentage()*(double) timeSliceNumber));
        qDebug()<<matrixIndexToRoutineId.getFromValue(tempObject->getRoutineIdAndCallStack())<<"/"<<tempObject->toString();
    }
    for (int i=0; i<timeSlices.size(); i++){
        timeSlices[i]->finalize();
    }
    for (unsigned int i=0; i<matrix->size(); i++){
        for (unsigned int j=0; j<matrix->at(i).size(); j++){
            double samples=(double)timeSlices[i]->getSampleNumber();
            if (samples!=0.0){
                matrix->at(i)[j][0]/=samples;
            }else{
                hv=true;
            }
        }
    }
}



void RRIMicroscopicModel::addToMicroscopicModel(RRIObject *object, int timeSlice)
{
    for (unsigned int i=0; i<matrix->size();i++){
        while (matrix->at(i).size()<(unsigned int)object->getIndex()+1){
            matrix->at(i).push_back(vector<double>());
            matrix->at(i)[matrix->at(i).size()-1].push_back(0.0);
        }
    }
    matrix->at(timeSlice)[matrixIndexToRoutineId.getFromValue(object->getRoutineIdAndCallStack())][0]+=1.0;
    timeSlices[timeSlice]->addObject(object);
}

bool RRIMicroscopicModel::hasVoid() const
{
    return hv;
}

QVector<RRITimeSlice *> RRIMicroscopicModel::getTimeSlices() const
{
    return timeSlices;
}

BiQMap<int, QString> RRIMicroscopicModel::getMatrixIndexToRoutineId() const
{
    return matrixIndexToRoutineId;
}
