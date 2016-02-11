#include <QString>
#include <QTextStream>
#include <QFile>

#include <rricore.h>


int main(int argc, char *argv[])
{
    if (argc==2){
        QString input = QString(argv[1]);
        QString qualities = "qualities.csv";
        QFile qualitiesFile(qualities);
        if (!qualitiesFile.open(QIODevice::WriteOnly | QIODevice::Text)){
           return 2;
        }
        QTextStream qualitiesStream(&qualitiesFile);
        RRICore core = RRICore();
        core.getParameters()->setCurrentFileName(input);
        core.buildMicroscopicModel();
        core.initMacroscopicModels();
        core.buildMacroscopicModels();
        for (int i=0; i<core.getMacroscopicModel()->getParameters().size(); i++){
            qualitiesStream<<core.getMacroscopicModel()->getParameters()[i]<<","<<core.getMacroscopicModel()->getQualities()[i]->getGain()<<","<<core.getMacroscopicModel()->getQualities()[i]->getLoss();
        }
        //core.selectMacroscopicModel();
        return 0;
        }
    return 1;
}
