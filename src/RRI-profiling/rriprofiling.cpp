﻿#include "rriprofiling.h"


RRIProfiling::RRIProfiling(QTextStream* statsStream, QTextStream* slopeStream, QTextStream* profilingStream):slopeParser(new slopeParser()), statsParser(new statsParser()),
    statsStream(statsStream), slopeStream(slopeStream), profilingStream(profilingStream)
{

}

RRIProfiling::~RRIProfiling()
{
    for (RoutineProfile *routineProfile:routineProfiles.values()){
        delete routineProfile;
    }
    delete slopeParser;
    delete statsParser;
}

void RRIProfiling::parse()
{
    parseStats();
    parseSlope();
}

void RRIProfiling::parseSlope()
{
    slopeParser->buildSlopes(slopeStream);
}

void RRIProfiling::parseStats()
{
    statsParser->buildStats(statsStream);
}

void RRIProfiling::writeStream()
{
    for (RoutineProfile *routineProfile:routineProfiles.values()){
        profilingStream<<routineProfile;
    }
}

void RRIProfiling::computeRoutines(QString region, RRICore *core)
{
    int weight=statsParser->getStatsMap()[region]->getTotalInstanceNumber();
    float duration=statsParser->getStatsMap()[region]->getSelectedInstanceMedian();
    QVector<Part*> parts=core->getParts();
    for (int i=0; i< parts.size(); i++){
        RRIPart* rriPart=dynamic_cast<RRIRedistributedModel*>(core->getRedistributedModel())->getRRIParts()[i];
        if (rriPart->getRoutines().size()>0){
            QList<RRIRoutineInfo*> routines=rriPart->getRoutines().values();
            qSort(routines.begin(), routines.end(), RRIRoutineInfo.CompareByStackLvlAsc());
            QMap<RoutineProfile, float> ratio;
            QMap<float, float> callStackLvlTotal;
            for (RRIRoutineInfo* routine:routines){
                ratio.insert(routine, routine->getPercentageDuration());
                if (!callStackLvlTotal.contains(routine->getAverageCallStackLevel())){
                    callStackLvl.insert(routine->getAverageCallStackLevel(),0);
                }
                callStackLvlTotal[routine->getAverageCallStackLevel()]+=routine->getPercentageDuration();
            }
            for (RRIRoutineInfo* routine:routines){
                float previousRatio=0;
                for (int i=0; i<routine->getAverageCallStackLevel();i++)
                    if (callStackLvlTotal.contains(i)){
                        previousRatio=callStackLvlTotal[i];
                    }
                ratio[routine]=(callStackLvlTotal[routine->getAverageCallStackLevel()]-previousRatio)*(ratio[routine]/callStackLvlTotal[routine->getAverageCallStackLevel()]);
                if (ratio[routine]!=0){
                    if (!routineProfile.contains(routine->toString())){
                        routineProfiles.insert(routine->toString(),new RoutineProfile(routine->toString()));
                        for (QString counter:slopeParser->getSlopes()[region].keys()){
                            routineProfiles.at(routine->toString()).addToAvg(region, counter,
                                    slopeParser->getSlopes()[region][counter]->mean(rriPart->getFirstRelative(), rriPart->getLastRelative()),
                                    rriPart->getSizeRelative()*duration, ratio[routine], weight);
                        }
                    }
                }
            }

        }
    }
