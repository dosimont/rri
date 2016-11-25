/*  RRI - Relevant Routine Identifier
*   Copyright (C) 2016  Damien Dosimont
*
*   This file is part of RRI.
*
*   RRI is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
#include <rriprofiling.h>

#include "argumentmanager.h"
#include "filemanager.h"
#include "bin_constants.h"

int main(int argc, char *argv[])
{
    qDebug().nospace()<<"RRI version "<<__BUILD_VERSION__;
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
        return RETURN_ERR_OTHER;
    }
    PrvRegionWriter* regionWriter=new PrvRegionWriter();
    RRIProfiling* rriProfiling;
    if (!argumentManager->getUniqueFile()){
        regionWriter->setInputPrvFile(fileManager->getInputPrvFiles());
        regionWriter->setOutputPrvFile(fileManager->getOutputPrvFiles());
        regionWriter->parseRegions(fileManager->getCallerDataRegionStream());
        regionWriter->setEventTypeBlockItems();
        regionWriter->pushRRIRegionHeader();
        rriProfiling=new RRIProfiling(fileManager->getStatsStream(), fileManager->getSlopeStream(), fileManager->getProfilingStream());
    }
    rriProfiling->parse();
    RRICore* core;
    if (fileManager->getRegions().size()==0){
        qWarning().nospace()<<"No corresponding regions have been found";
    }
    for (int i=0; i<fileManager->getRegions().size(); i++){
        qDebug().nospace()<<"Region: "<<fileManager->getRegions()[i];
        qDebug().nospace()<<"Input file: "<<fileManager->getStreamSets()[i]->getInputFile()->fileName();
        core = new RRICore();
        core->getParameters()->setAnalysisType(rri::RRI);
        core->getParameters()->setStream(fileManager->getStreamSets()[i]->getInputStream());
        core->getParameters()->setTimesliceNumber(argumentManager->getTimeSliceNumber());
        core->getParameters()->setThreshold(argumentManager->getThreshold());
        core->getParameters()->setMinprop(argumentManager->getMinprop());
        if (!core->buildMicroscopicModel()){
            return 4;
        }
        core->buildMacroscopicModels();
        /*int timesliceNumber=argumentManager->getTimeSliceNumber();
        while(argumentManager->getNovoid()&&core->hasVoid()&&timesliceNumber>MIN_TSNUMBER_NOVOID){
            timesliceNumber/=2;
            qDebug().nospace()<<"Empty timeslice has been found. Changing timeslice number to "<<timesliceNumber;
            core->getParameters()->setTimesliceNumber(timesliceNumber);
            if (!core->buildMicroscopicModel()){
                return 4;
            }
            core->buildMacroscopicModels();
        }
        if (argumentManager->getNovoid()&&core->hasVoid()){
            qDebug().nospace()<<"Failed!";
            core->getParameters()->setTimesliceNumber(argumentManager->getTimeSliceNumber());
            if (!core->buildMicroscopicModel()){
                return 4;
            }
            core->buildMacroscopicModels();
        }else{
            qDebug().nospace()<<"Success!";
        }*/
        QTextStream* qualityStream=fileManager->getStreamSets()[i]->getQualityStream();
        QTextStream* partitionStream=fileManager->getStreamSets()[i]->getPartitionStream();
        QTextStream* detailStream=fileManager->getStreamSets()[i]->getDetailStream();
        QTextStream* routineStream=fileManager->getStreamSets()[i]->getRoutineStream();
        QTextStream* infoStream=fileManager->getStreamSets()[i]->getInfoStream();
        for (int j=0; j<core->getMacroscopicModel()->getPs().size(); j++){
            if (std::isnan(core->getMacroscopicModel()->getQualities()[j]->getGain())||std::isnan(core->getMacroscopicModel()->getQualities()[j]->getLoss())){
                std::cerr<<"NaN value detected, stopping the rendering"<<std::endl;
                return 5;
            }
            *qualityStream<<core->getMacroscopicModel()->getPs()[j]<<SEP
                           <<core->getMacroscopicModel()->getQualities()[j]->getGain()<<SEP
                           <<core->getMacroscopicModel()->getQualities()[j]->getLoss()
                           <<endl;
            core->getParameters()->setP(core->getMacroscopicModel()->getPs()[j]);
            core->selectMacroscopicModel();
            core->buildRedistributedModel();
            QVector<Part*> parts=core->getParts();
            for (int k=0; k< parts.size(); k++){
                *partitionStream<<core->getMacroscopicModel()->getPs()[j]<<SEP<<parts[k]->getFirstRelative()<<SEP<<parts[k]->getLastRelative()<<SEP<<core->getRedistributedModel()->getPartsAsString()[k]<<endl;
                RRIPart* rriPart=dynamic_cast<RRIRedistributedModel*>(core->getRedistributedModel())->getRRIParts()[k];
                if (rriPart->getRoutines().size()==0){
                    *detailStream<<core->getMacroscopicModel()->getPs()[j]<<SEP<<parts[k]->getFirstRelative()<<SEP<<
                                    parts[k]->getLastRelative()<<SEP<<"void"<<SEP<<0<<SEP<<
                                    0<<SEP<<0<<endl;
                }else{
                    QList<RRIRoutineInfo*> routines=rriPart->getRoutines().values();
                    for (RRIRoutineInfo* routine:routines){
                            *detailStream<<core->getMacroscopicModel()->getPs()[j]<<SEP<<parts[k]->getFirstRelative()<<SEP<<
                                            parts[k]->getLastRelative()<<SEP<<routine->toString()<<SEP<<routine->getPercentageDuration()<<SEP<<
                                            routine->getAverageCallStackLevel()<<SEP<<(routine->getIndex()==core->getRedistributedModel()->getPartsAsIndex()[k])<<endl;
                    }
                }
            }
            QVector<RRIObject*> codelines=dynamic_cast<RRIRedistributedModel*>(core->getRedistributedModel())->generateCodelines();
            for (int k=0; k< codelines.size(); k++){
                *routineStream<<core->getMacroscopicModel()->getPs()[j]<<SEP
                      <<codelines[k]->getTsPercentage()<<SEP
                      <<codelines[k]->getCodeline()
                      <<endl;
            }

        }
        //*infoStream<<"#Score, Global_inflex_point, Local_inflex_point, Best_point, Timeslice_number"<<endl;
        *infoStream<<core->getMacroscopicModel()->getAggregationScore()<<",";
        core->setP(rri::NORM_INFLECT);
        core->selectMacroscopicModel();
        core->buildRedistributedModel();
        *infoStream<<core->getCurrentP()<<",";
        core->setP(rri::NORM_INFLECT2);
        core->selectMacroscopicModel();
        core->buildRedistributedModel();
        *infoStream<<core->getCurrentP()<<",";
        core->setP(rri::NORM_BEST);
        core->selectMacroscopicModel();
        core->buildRedistributedModel();
        *infoStream<<core->getCurrentP()<<",";
        *infoStream<<core->getParameters()->getTimesliceNumber()<<endl;
        if (!argumentManager->getUniqueFile()){
            regionWriter->pushRRIRegion(fileManager->getRegions()[i], core);
            core->setP(rri::MIN);
            core->selectMacroscopicModel();
            core->buildRedistributedModel();
            rriProfiling->computeRoutines(fileManager->getRegions()[i], core);
        }
        fileManager->getStreamSets()[i]->close();
        delete core;
    }
    if (!argumentManager->getUniqueFile()){
        regionWriter->pushRRIEventTypeBlock();
        rriProfiling->writeStream();
        delete rriProfiling;
    }
    delete fileManager;
    delete regionWriter;
    delete argumentManager;
    qDebug().nospace()<<"Exiting";
    return RETURN_OK;
}
