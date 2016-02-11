#include <iostream>

#include <QString>
#include <QTextStream>
#include <QFile>

#include <rricore.h>

int main(int argc, char *argv[])
{
    if (argc==2){
        QString input = QString(argv[1]);
        std::cout<<"Input file: "<<input.toStdString()<<std::endl;
        QString qualities = "qualities.csv";
        QFile qualitiesFile(qualities);
        if (!qualitiesFile.open(QIODevice::WriteOnly | QIODevice::Text)){
           return 2;
        }
        QTextStream qualitiesStream(&qualitiesFile);
        std::cout<<"Output file qualities.csv has been sucessfully created"<<std::endl;
        RRICore core = RRICore();
        std::cout<<"Core has been instancied"<<std::endl;
        core.getParameters()->setCurrentFileName(input);
        std::cout<<"Input file has been transmitted"<<std::endl;
        if (!core.buildMicroscopicModel()){
            return 3;
        }
        std::cout<<"Microscopic model has been built"<<std::endl;
        core.initMacroscopicModels();
        std::cout<<"Macroscopic model has been initialized"<<std::endl;
        core.buildMacroscopicModels();
        std::cout<<"Macroscopic model has been built"<<std::endl;
        for (int i=0; i<core.getMacroscopicModel()->getParameters().size(); i++){
            qualitiesStream<<core.getMacroscopicModel()->getParameters()[i]<<","<<core.getMacroscopicModel()->getQualities()[i]->getGain()<<","<<core.getMacroscopicModel()->getQualities()[i]->getLoss();
        }
        //core.selectMacroscopicModel();
        return 0;
        }
    std::cerr<<"Not enough arguments"<<std::endl;
    return 1;
}
