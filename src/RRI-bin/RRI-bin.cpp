#include <iostream>
#include <math.h>

#include <QString>
#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QVector>
#include <QDebug>

#include <rricore.h>
#include <part.h>
#include <prvregionwriter.h>

#include "argumentmanager.h"
#include "filemanager.h"
#include "bin_constants.h"

int main(int argc, char *argv[])
{
    int error;
    ArgumentManager* argumentManager = new ArgumentManager(argc, argv);
    if (!argumentManager->getConform()||argumentManager->getHelp()){
        argumentManager->printUsage();
        return RETURN_ERR_CMD;
    }
    FileManager* fileManager = new FileManager(argumentManager);
    error=fileManager->init();
    if (error!=RETURN_OK){
        delete fileManager;
        delete argumentManager;
        qCritical()<<"Exiting";
    }
    PrvRegionWriter* regionWriter=new PrvRegionWriter();
    if (!argumentManager->getUniqueFile()){
        regionWriter->setInputPrvFile(fileManager->getInputPrvFiles());
        regionWriter->setOutputPrvFile(fileManager->getOutputPrvFiles());
        regionWriter->parseRegions(fileManager->getRegionStream());
        regionWriter->setEventTypeBlockItems();
        regionWriter->pushRRIRegionHeader();
    }
    RRICore* core;
    for (int i=0; i<fileManager->getIterationNames().size(); i++){
        qDebug().nospace()<<"Iteration "<<i+1<<", session: "<<fileManager->getIterationNames()[i];
        qDebug().nospace()<<"Input file: "<<fileManager->getStreamSets()[i]->getInputFile()->fileName();
        core = new RRICore();
        core->getParameters()->setAnalysisType(rri::RRI);
        core->getParameters()->setStream(fileManager->getStreamSets()[i]->getInputStream());
        core->getParameters()->setTimesliceNumber(argumentManager->getTimeSliceNumber());
        qDebug().nospace()<<"Time slice number: "<<core->getParameters()->getTimesliceNumber();
        if (!core->buildMicroscopicModel()){
            return 4;
        }
        core->initMacroscopicModels();
        core->buildMacroscopicModels();
        QTextStream* qualityStream=fileManager->getStreamSets()[i]->getQualityStream();
        QTextStream* partitionStream=fileManager->getStreamSets()[i]->getPartitionStream();
        QTextStream* routineStream=fileManager->getStreamSets()[i]->getRoutineStream();
        QTextStream* infoStream=fileManager->getStreamSets()[i]->getInfoStream();
        for (int i=0; i<core->getMacroscopicModel()->getPs().size(); i++){
            if (std::isnan(core->getMacroscopicModel()->getQualities()[i]->getGain())||std::isnan(core->getMacroscopicModel()->getQualities()[i]->getLoss())){
                std::cerr<<"NaN value detected, stopping the rendering"<<std::endl;
                return 5;
            }
            *qualityStream<<core->getMacroscopicModel()->getPs()[i]<<","
                           <<core->getMacroscopicModel()->getQualities()[i]->getGain()<<","
                           <<core->getMacroscopicModel()->getQualities()[i]->getLoss()
                           <<endl;
            core->getParameters()->setP(core->getMacroscopicModel()->getPs()[i]);
            core->selectMacroscopicModel();
            core->buildRedistributedModel();           
            QVector<Part*> parts=core->getParts();
            for (int j=0; j< parts.size(); j++){
                //if (!core->getRedistributedModel()->getPartsAsStrings()[j].compare("void")==0){
                *partitionStream<<core->getMacroscopicModel()->getPs()[i]<<","<<parts[j]->getFirstRelative()<<","<<parts[j]->getLastRelative()<<","<<core->getRedistributedModel()->getPartsAsStrings()[j]<<endl;
                //}
            }
            QVector<RRIObject*> codelines=dynamic_cast<RRIRedistributedModel*>(core->getRedistributedModel())->generateCodelines();
            for (int j=0; j< codelines.size(); j++){
                *routineStream<<core->getMacroscopicModel()->getPs()[i]<<","
                      <<codelines[j]->getTsPercentage()<<","
                      <<codelines[j]->getCodeline()
                      <<endl;
            }

        }
        core->setP(rri::NORM_INFLECT);
        core->selectMacroscopicModel();
        core->buildRedistributedModel();
        *infoStream<<"Overall aggregation score (negative: possible issue, 0: bad, 100: good) = "<<core->getMacroscopicModel()->getAggregationScore()<<endl;
        *infoStream<<"Gain normalized inflection point: p = "<<core->getCurrentP()<<endl;
        *infoStream<<"Time slice number = "<<core->getParameters()->getTimesliceNumber()<<endl;
        if (!argumentManager->getUniqueFile()){
            regionWriter->pushRRIRegion(fileManager->getIterationNames()[i], core);
        }
        fileManager->getStreamSets()[i]->close();
        delete core;
    }
    if (!argumentManager->getUniqueFile()){
        regionWriter->pushRRIEventTypeBlock();
    }
    delete fileManager;
    delete regionWriter;
    delete argumentManager;
    qDebug().nospace()<<"Exiting";
    return RETURN_OK;
}
