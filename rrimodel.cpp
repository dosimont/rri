#include "rrimodel.h"

RRIModel::RRIModel()
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
        stringList=csv.parseLine();
        do{

            stringList=csv.parseLine();
        }while(stringList.size()>0);


        }


}
