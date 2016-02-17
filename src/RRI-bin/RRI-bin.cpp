#include <iostream>

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
        std::cout<<"Input file: "<<input.toStdString()<<std::endl;
        QFileInfo fileInfo(input);
        QString path=fileInfo.absolutePath() + "/" + fileInfo.baseName();
        QDir dir(path);
        dir.setNameFilters(QStringList() << "*.*");
        dir.setFilter(QDir::Files);
        foreach(QString dirFile, dir.entryList())
        {
            dir.remove(dirFile);
        }
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
        QTextStream qualitiesStream(&qualitiesFile);
        QTextStream pStream(&pFile);
        RRICore core = RRICore();
        core.getParameters()->setCurrentFileName(input);
        core.getParameters()->setTimesliceNumber(TS_NUMBER);
        if (!core.buildMicroscopicModel()){
            return 4;
        }
        core.initMacroscopicModels();
        core.buildMacroscopicModels();
        for (int i=0; i<core.getMacroscopicModel()->getPs().size(); i++){
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
