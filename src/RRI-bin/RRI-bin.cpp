#include <iostream>

#include <QString>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QVector>

#include <rricore.h>
#include <part.h>

#define TS_NUMBER 200
#define THRESHOLD_FACTOR 10

int main(int argc, char *argv[])
{
    if (argc==2){
        QString input = QString(argv[1]);
        std::cout<<"Input file: "<<input.toStdString()<<std::endl;
        QString path = "rri";
        QDir dir(path);
        dir.setNameFilters(QStringList() << "*.*");
        dir.setFilter(QDir::Files);
        foreach(QString dirFile, dir.entryList())
        {
            dir.remove(dirFile);
        }
        QDir().mkdir("rri");
        QString qualities = "rri/qualities.csv";
        QFile qualitiesFile(qualities);
        if (!qualitiesFile.open(QIODevice::ReadWrite | QIODevice::Text)){
           return 2;
        }
        QTextStream qualitiesStream(&qualitiesFile);
        RRICore core = RRICore();
        core.getParameters()->setCurrentFileName(input);
        core.getParameters()->setTimesliceNumber(TS_NUMBER);
        if (!core.buildMicroscopicModel()){
            return 3;
        }
        core.initMacroscopicModels();
        core.buildMacroscopicModels();
        for (int i=0; i<core.getMacroscopicModel()->getPs().size(); i++){
            float nextPs=1;
            if (i<core.getMacroscopicModel()->getPs().size()-1){
                nextPs=core.getMacroscopicModel()->getPs()[i+1]-core.getParameters()->getThreshold()/THRESHOLD_FACTOR;
            }
            qualitiesStream<<core.getMacroscopicModel()->getPs()[i]<<","
                           <<core.getMacroscopicModel()->getQualities()[i]->getGain()
                           <<","<<core.getMacroscopicModel()->getQualities()[i]->getLoss()
                           <<endl;
            qualitiesStream<<nextPs<<","
                           <<core.getMacroscopicModel()->getQualities()[i]->getGain()
                           <<","<<core.getMacroscopicModel()->getQualities()[i]->getLoss()
                           <<endl;
            QString p = QString("rri/p_%1.csv").arg(i);
            QFile pFile(p);
            if (!pFile.open(QIODevice::ReadWrite | QIODevice::Text)){
               return 2;
            }
            QTextStream pStream(&pFile);
            core.getParameters()->setP(core.getMacroscopicModel()->getPs()[i]);
            core.selectMacroscopicModel();
            QVector<Part*> parts=core.getParts();
            for (int j=0; j< parts.size(); j++){
                pStream<<parts[j]->getFirstRelative()<<","<<parts[j]->getLastRelative()<<endl;
            }
        }
        return 0;
        }
    std::cerr<<"Usage: "<<argv[0]<<" <file.callerdata>"<<std::endl;
    return 1;
}
