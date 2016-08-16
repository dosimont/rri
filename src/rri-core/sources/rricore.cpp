/*  RRI - Relevant Routine Identifier
*  Copyright (C) 2016  Damien Dosimont
*  
*  This file is part of RRI.
*  
*  RRI is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*  
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "rricore.h"

RRICore::RRICore():parameters(new Parameters()),
    microscopicModel(NULL),
    macroscopicModel(NULL),
    redistributedModel(NULL)
{

}

RRICore::~RRICore()
{
    delete parameters;
    delete microscopicModel;
    delete macroscopicModel;
    delete redistributedModel;
}

bool RRICore::buildMicroscopicModel()
{
    RRIMicroscopicModel *castModel;
    switch (parameters->getAnalysisType()){
        case rri::RRI:
            delete microscopicModel;
            delete macroscopicModel;
            delete redistributedModel;
            macroscopicModel=NULL;
            redistributedModel=NULL;
            microscopicModel=new RRIMicroscopicModel();
            castModel=dynamic_cast<RRIMicroscopicModel*>(microscopicModel);
            castModel->generate(parameters->getStream(), parameters->getTimesliceNumber());
            macroscopicModel=new OMacroscopicModel(microscopicModel);
            return true;
        case rri::DEFAULT:;
    }
    return false;
}

void RRICore::initMacroscopicModels()
{
    switch (parameters->getAnalysisType()){
        case rri::RRI:
            delete macroscopicModel;
            macroscopicModel=new OMacroscopicModel(microscopicModel);
            break;
        case rri::DEFAULT:;
    }
}

void RRICore::buildMacroscopicModels()
{
    macroscopicModel->computeQualities(parameters->getNormalize());
    macroscopicModel->computeBestPartitions(parameters->getThreshold());
}

void RRICore::selectMacroscopicModel()
{
    macroscopicModel->computeBestPartition(parameters->getP());
}

void RRICore::buildRedistributedModel()
{
    RRIRedistributedModel *rRIRedistributedModel;
    switch (parameters->getAnalysisType()){
        case rri::RRI:
            delete redistributedModel;
            redistributedModel=new RRIRedistributedModel(microscopicModel, macroscopicModel);
            rRIRedistributedModel=dynamic_cast<RRIRedistributedModel*>(redistributedModel);
            rRIRedistributedModel->generateRoutines(parameters->getMinprop());
            rRIRedistributedModel->generateCodelines();
            break;
        case rri::DEFAULT:;
    }
}

float RRICore::getCurrentP()
{
    return parameters->getP();
}

float RRICore::nextP()
{
    if (currentPIndex!=-1){
        if (currentPIndex<getPs().size()-1){
            setCurrentPIndex(currentPIndex+1);
        }
    }else{
        int i;
        for (i=0; i<getPs().size()&&getPs()[i]<=getCurrentP();i++){
        }
        setCurrentPIndex(i);
    }
    return getCurrentP();
}

float RRICore::previousP()
{
    if (currentPIndex!=-1){
        if (currentPIndex>1){
            setCurrentPIndex(currentPIndex-1);
        }
    }else{
        int i;
        for (i=getPs().size()-1; i>=0&&getPs()[i]>=getCurrentP();i--){
        }
        setCurrentPIndex(i);
    }
    return getCurrentP();
}

Parameters* RRICore::getParameters() const
{
    return parameters;
}

QVector<Part*> RRICore::getParts()
{
    return dynamic_cast<OMacroscopicModel*>(macroscopicModel)->getParts();
}

MacroscopicModel *RRICore::getMacroscopicModel() const
{
    return macroscopicModel;
}

MicroscopicModel *RRICore::getMicroscopicModel() const
{
    return microscopicModel;
}

int RRICore::getCurrentPIndex() const
{
    return currentPIndex;
}

void RRICore::setCurrentPIndex(int value)
{
    if (value > 0 && value <getPs().size()){
        currentPIndex = value;
        parameters->setP(getPs()[currentPIndex]);
    }
}

void RRICore::setP(rri::PDefaultValue defaultValue)
{
    switch (defaultValue) {
    case rri::MAX:setP(1.0);
        break;
    case rri::MIN:setP(0.0);
        break;
    case rri::NORM_INFLECT:setNormInflect();
        break;
    case rri::NORM_INFLECT2:setNormInflect2();
        break;
    case rri::NORM_BEST:setNormBest();
        break;
    default:setP(1.0);
        break;
    }
}

void RRICore::setP(float value)
{
    parameters->setP(value);
    currentPIndex=-1;
    for (int i=0; i<getPs().size(); i++){
        if (getPs()[i]==value){
            currentPIndex=i;
            break;
        }
    }
}

QVector<float> RRICore::getPs() const
{
    return macroscopicModel->getPs();
}

bool RRICore::hasVoid()
{
    return dynamic_cast<RRIMicroscopicModel*>(microscopicModel)->hasVoid();
}

void RRICore::setNormInflect()
{
    double score=getMacroscopicModel()->getQualities()[0]->getLoss()-getMacroscopicModel()->getQualities()[0]->getGain();
    int index=0;
    for (int i=1; i<getPs().size();i++){
        double currentScore=getMacroscopicModel()->getQualities()[i]->getLoss()-getMacroscopicModel()->getQualities()[i]->getGain();
        if (currentScore<=score){
            score=currentScore;
            index=i;
        }
    }
    setCurrentPIndex(index);
}

void RRICore::setNormBest()
{
   setNormInflect2();
   //float pInflex=getCurrentP();
   double gainInflex=getMacroscopicModel()->getQualities()[getCurrentPIndex()]->getGain();
   //double lossInflex=getMacroscopicModel()->getQualities()[getCurrentPIndex()]->getLoss();
   if (gainInflex<NORM_BEST_MIN_GAIN){
       setNormInflect();
   }

}

void RRICore::setNormInflect2()
{
    setNormInflect();
    //float pInflex=getCurrentP();
    double gainInflex=getMacroscopicModel()->getQualities()[getCurrentPIndex()]->getGain();
    double lossInflex=getMacroscopicModel()->getQualities()[getCurrentPIndex()]->getLoss();
    if (gainInflex==0||lossInflex==0){
        return;
    }
    double score=getMacroscopicModel()->getQualities()[0]->getLoss()/lossInflex-getMacroscopicModel()->getQualities()[0]->getGain()/gainInflex;
    int index=0;
    for (int i=1; i<=getCurrentPIndex();i++){
        double currentScore=getMacroscopicModel()->getQualities()[i]->getLoss()/lossInflex-getMacroscopicModel()->getQualities()[i]->getGain()/gainInflex;
        if (currentScore<=score){
            score=currentScore;
            index=i;
        }
    }
    setCurrentPIndex(index);
}

RedistributedModel *RRICore::getRedistributedModel() const
{
    return redistributedModel;
}
