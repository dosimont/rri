#include <iostream>
#include <math.h>

#include <QString>
#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QVector>

#include <rricore.h>
#include <part.h>


#define TS_NUMBER 200
#define THRESHOLD_FACTOR 1000

int main(int argc, char *argv[])
{
    if (argc==2){
        QString input = QString(argv[1]);
        std::cout<<"Executing Relevant Routine Identifier"<<std::endl;
        std::cout<<"Input file: "<<input.toStdString()<<std::endl;
        QFileInfo fileInfo(input);
        QString path=fileInfo.absolutePath() + "/" + fileInfo.completeBaseName();
        QDir dir(path);
        dir.setNameFilters(QStringList() << "*.*");
        dir.setFilter(QDir::Files);
        std::cout<<"Removing previously generated files"<<std::endl;
        foreach(QString dirFile, dir.entryList())
        {
            dir.remove(dirFile);
        }
        std::cout<<"Creating the result directory: "<<path.toStdString()<<std::endl;
        QDir().mkdir(path);
        QString qualities = path +"/qualities.csv";
        QFile qualitiesFile(qualities);
        if (!qualitiesFile.open(QIODevice::ReadWrite | QIODevice::Text)){
           return 2;
        }
        QString p = path +"/partitions.csv";
        QFile pFile(p);
        if (!pFile.open(QIODevice::ReadWrite | QIODevice::Text)){
           return 3;
        }
        QString codelines = path +"/codelines.csv";
        QFile codelinesFile(codelines);
        if (!codelinesFile.open(QIODevice::ReadWrite | QIODevice::Text)){
           return 4;
        }
        QTextStream qualitiesStream(&qualitiesFile);
        QTextStream pStream(&pFile);
        QTextStream codelinesStream(&codelinesFile);
        std::cout<<"Initializing the core"<<std::endl;
        RRICore core = RRICore();
        std::cout<<"Setting the parameters"<<std::endl;
        core.getParameters()->setCurrentFileName(input);
        core.getParameters()->setTimesliceNumber(TS_NUMBER);
        std::cout<<"Parsing the input file and generating the microscopic model"<<std::endl;
        if (!core.buildMicroscopicModel()){
            return 4;
        }
        std::cout<<"Initializing the macroscopic model"<<std::endl;
        core.initMacroscopicModels();
        std::cout<<"Generating the parameter p list"<<std::endl;
        core.buildMacroscopicModels();
        std::cout<<"Generating the macroscopic models"<<std::endl;
        for (int i=0; i<core.getMacroscopicModel()->getPs().size(); i++){
            if (std::isnan(core.getMacroscopicModel()->getQualities()[i]->getGain())||std::isnan(core.getMacroscopicModel()->getQualities()[i]->getLoss())){
                std::cerr<<"NaN value detected, stopping the rendering"<<std::endl;
                return 5;
            }
            qualitiesStream<<core.getMacroscopicModel()->getPs()[i]<<","
                           <<core.getMacroscopicModel()->getQualities()[i]->getGain()<<","
                           <<core.getMacroscopicModel()->getQualities()[i]->getLoss()
                           <<endl;
            core.getParameters()->setP(core.getMacroscopicModel()->getPs()[i]);
            core.selectMacroscopicModel();
            core.buildRedistributedModel();
            QVector<Part*> parts=core.getParts();
            for (int j=0; j< parts.size(); j++){
                pStream<<core.getMacroscopicModel()->getPs()[i]<<","<<parts[j]->getFirstRelative()<<","<<parts[j]->getLastRelative()<<","<<core.getRedistributedModel()->getPartsAsStrings()[j]<<endl;
            }
            QVector<RRIObject*> codelines=dynamic_cast<RRIRedistributedModel*>(core.getRedistributedModel())->generateCodelines();
            for (int j=0; j< codelines.size(); j++){
                codelinesStream<<core.getMacroscopicModel()->getPs()[i]<<","
                      <<codelines[j]->getTsPercentage()<<","
                      <<codelines[j]->getCodeline()
                      <<endl;
            }

        }
        std::cout<<"Exiting"<<std::endl;
        return 0;
    }
    std::cerr<<"Usage: "<<argv[0]<<" <file.callerdata>"<<std::endl;
    return 1;
}
