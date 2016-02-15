#include "rricore.h"

RRICore::RRICore():parameters(new Parameters())
{

}

bool RRICore::buildMicroscopicModel()
{
    QFileInfo fileInfo(parameters->getCurrentFileName());
    if (fileInfo.suffix().compare(FILE_EXT_RRI)==0){
        parameters->setAnalysisType(rri::RRI);
        microscopicModel=new RRIModel();
        RRIModel *castModel=dynamic_cast<RRIModel*>(microscopicModel);
        castModel->parseFile(parameters->getCurrentFileName(), parameters->getTimesliceNumber());
        return true;
    }else{
        return false;
    }
}

void RRICore::initMacroscopicModels()
{
    switch (parameters->getAnalysisType()){
       case rri::RRI:macroscopicModel=new OMacroscopicModel(microscopicModel);
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

}

float RRICore::nextP()
{

}

float RRICore::previousP()
{

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
    currentPIndex = value;
}

void RRICore::setP(rri::PDefaultValue defaultValue)
{

}

void RRICore::setP(float value)
{
    parameters->setP(value);
    p
}

QVector<float> RRICore::getPs() const
{
    return macroscopicModel->getPs();
}
