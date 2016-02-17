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
    vector<QString> colors;
    colors.push_back("red");
    colors.push_back("blue");
    colors.push_back("green");
    colors.push_back("yellow");
    colors.push_back("black");
    colors.push_back("orange");
    colors.push_back("purple");
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
        std::cout<<"Done"<<std::endl;
        std::cout<<"Creating result directory: "<<path<<std::endl;
        QDir().mkdir(path);
        std::cout<<"Done"<<std::endl;
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
        QTextStream qualitiesStream(&qualitiesFile);
        QTextStream pStream(&pFile);
        std::cout<<"Initializing the core"<<path<<std::endl;
        RRICore core = RRICore();
        std::cout<<"Setting the parameters"<<path<<std::endl;
        core.getParameters()->setCurrentFileName(input);
        core.getParameters()->setTimesliceNumber(TS_NUMBER);
        std::cout<<"Parsing the input file and generating the microscopic model"<<path<<std::endl;
        if (!core.buildMicroscopicModel()){
            return 4;
        }
        std::cout<<"Initializing the macroscopic model"<<path<<std::endl;
        core.initMacroscopicModels();
        std::cout<<"Generating the parameter p list"<<path<<std::endl;
        core.buildMacroscopicModels();
        std::cout<<"Generating the macroscopic models"<<path<<std::endl;
        for (int i=0; i<core.getMacroscopicModel()->getPs().size(); i++){
            if (isnan(getQualities()[i]->getGain())||isnan(getQualities()[i]->getLoss())){
                std::cerr<<"NaN value detected, stopping the rendering and removing the results"<<path<<std::endl;
                QDir().mkdir(path);
                return 5;
            }
            qualitiesStream<<core.getMacroscopicModel()->getPs()[i]<<","
                           <<core.getMacroscopicModel()->getQualities()[i]->getGain()<<","
                           <<core.getMacroscopicModel()->getQualities()[i]->getLoss()
                           <<endl;
            core.getParameters()->setP(core.getMacroscopicModel()->getPs()[i]);
            core.selectMacroscopicModel();
            QVector<Part*> parts=core.getParts();
            for (int j=0; j< parts.size(); j++){
                pStream<<core.getMacroscopicModel()->getPs()[i]<<","<<parts[j]->getFirstRelative()<<","<<parts[j]->getLastRelative()<<","<<colors[j%7]<<endl;
            }
        }
        return 0;
        }
    std::cerr<<"Usage: "<<argv[0]<<" <file.callerdata>"<<std::endl;
    return 1;
}
