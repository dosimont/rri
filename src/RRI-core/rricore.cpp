#include "rricore.h"

RRICore::RRICore():parameters(new Parameters()), microscopicModelAllocated(false), macroscopicModelAllocated(false)
{

}

RRICore::~RRICore()
{
    delete parameters;
    if (microscopicModelAllocated){
        delete microscopicModel;
    }
    if (macroscopicModelAllocated){
        delete macroscopicModel;
    }
}

bool RRICore::buildMicroscopicModel()
{
    QFileInfo fileInfo(parameters->getCurrentFileName());
    if (fileInfo.suffix().compare(FILE_EXT_RRI)==0){
        parameters->setAnalysisType(rri::RRI);
        if (microscopicModelAllocated){
            delete microscopicModel;
        }
        microscopicModel=new RRIMicroscopicModel();
        microscopicModelAllocated=true;
        RRIMicroscopicModel *castModel=dynamic_cast<RRIMicroscopicModel*>(microscopicModel);
        castModel->parseFile(parameters->getCurrentFileName(), parameters->getTimesliceNumber());
        return true;
    }else{
        return false;
    }
}

void RRICore::initMacroscopicModels()
{
    switch (parameters->getAnalysisType()){
       case rri::RRI:
        if (macroscopicModelAllocated){
            delete macroscopicModel;
        }
        macroscopicModelAllocated=true;
        macroscopicModel=new OMacroscopicModel(microscopicModel);
        macroscopicModel->initializeAggregator();
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
