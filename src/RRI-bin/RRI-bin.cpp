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
#include <argumentmanager.h>
#include <filemanager.h>

#define RETURN_OK 0
#define RETURN_ERR_CMD 1


int main(int argc, char *argv[])
{
    ArgumentManager argumentManager(argc, argv);
    if (!argumentManager.getConform()||argumentManager.getHelp()){
        argumentManager.printUsage();
        return RETURN_ERR_CMD;
    }
    FileManager fileManager(argumentManager);
    fileManager.init();
    RRICore core;
    for (int i=0; i<fileManager.iterationNames.size(); i++){
        core = RRICore();
        core.getParameters()->setAnalysisType(rri::RRI);
        core.getParameters()->setStream(fileManager.streamSets[i].getInputStream());
        core.getParameters()->setTimesliceNumber(argumentManager.getTimeSliceNumber());
    }
    if (!core.buildMicroscopicModel()){
        return 4;
    }
    core.initMacroscopicModels();
    core.buildMacroscopicModels();
    QTextStream* qualityStream=fileManager.streamSets[i].getQualityStream();
    QTextStream* partitionStream=fileManager.streamSets[i].getPartitionStream();
    QTextStream* routineStream=fileManager.streamSets[i].getRoutineStream();
    QTextStream* infoStream=fileManager.streamSets[i].getInfoStream();
    for (int i=0; i<core.getMacroscopicModel()->getPs().size(); i++){
        if (std::isnan(core.getMacroscopicModel()->getQualities()[i]->getGain())||std::isnan(core.getMacroscopicModel()->getQualities()[i]->getLoss())){
            std::cerr<<"NaN value detected, stopping the rendering"<<std::endl;
            return 5;
        }
        qualityStream<<core.getMacroscopicModel()->getPs()[i]<<","
                       <<core.getMacroscopicModel()->getQualities()[i]->getGain()<<","
                       <<core.getMacroscopicModel()->getQualities()[i]->getLoss()
                       <<endl;
        core.getParameters()->setP(core.getMacroscopicModel()->getPs()[i]);
        core.selectMacroscopicModel();
        core.buildRedistributedModel();
        QVector<Part*> parts=core.getParts();
        for (int j=0; j< parts.size(); j++){
            partitionStream<<core.getMacroscopicModel()->getPs()[i]<<","<<parts[j]->getFirstRelative()<<","<<parts[j]->getLastRelative()<<","<<core.getRedistributedModel()->getPartsAsStrings()[j]<<endl;
        }
        QVector<RRIObject*> codelines=dynamic_cast<RRIRedistributedModel*>(core.getRedistributedModel())->generateCodelines();
        for (int j=0; j< codelines.size(); j++){
            routineStream<<core.getMacroscopicModel()->getPs()[i]<<","
                  <<codelines[j]->getTsPercentage()<<","
                  <<codelines[j]->getCodeline()
                  <<endl;
        }

    }
    core.setP(rri::NORM_INFLECT);
    core.selectMacroscopicModel();
    core.buildRedistributedModel();
    infoStream<<"Overall aggregation score (negative: possible issue, 0: bad, 100: good) = "<<core.getMacroscopicModel()->getAggregationScore()<<endl;
    infoStream<<"Gain normalized inflection point: p = "<<core.getCurrentP()<<endl;
    infoStream<<"Time slice number = "<<core.getParameters()->getTimesliceNumber()<<endl;
    return RETURN_OK;
}
