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
        i=0;
        for (stringList=csv.parseLine();stringList.size()>0;stringList=csv.parseLine()){
            RRIObject* tempObject=new RRIObject();
            tempObject->setId(QString.toInt(stringList[RRI_CSV_ID]));
            tempObject->setSample(QString.toInt(stringList[RRI_CSV_SAMPLE]));
            tempObject->setTsPercentage(QString.toDouble(stringList[RRI_CSV_TS_PERCENTAGE]));
            tempObject->setTsAbsolute(QString.toInt(stringList[RRI_CSV_TS_ABSOLUTE]));
            tempObject->setCallstackLvl(QString.toInt(stringList[RRI_CSV_CALSTACK_LVL]));
            tempObject->setRoutineId(QString.toInt(stringList[RRI_CSV_ROUTINE_ID]));
            tempObject->setCodelineId(QString.toInt(stringList[RRI_CSV_CODELINE_ID]));
            if (!routineMap.containsValue(tempObject->getRoutineId())){
                routineMap.add(i,tempObject->getRoutineId());
            }
            objects->append(tempObject);
            addToMicroscopicModel(tempObject);
        }
    }
}

void RRIModel::addToMicroscopicModel(RRIObject *object)
{
    if (microscopicModel.size()<object->getSample())
}
